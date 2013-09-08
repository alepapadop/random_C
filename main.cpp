#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef enum DataType {
    UNKNOWN = 0,
    SHAPE = 1,
    COORDINATE,
    INDEXED_LINE_SET,
    INDEXED_FACE_SET,
    TRANSFORM,
    MATERIAL,
    POINT_SET,
    GROUP,
    APPEARANCE,
    ROTATION,
    TRANSLATION,
    SCALE,
    POINT
} DataType;


typedef struct Shape {
    struct Info *info;
    double point[3];

} Shape;

typedef struct Transform {
    struct Info *info;
    double translation[3];
    double rotation[4];
    double scale[3];
    vector<void *> *children;
} Transform;

typedef struct Group {
    struct Info *info;
    double b_boc_center[3];
    double b_box_size[3];
    //void *children;
    vector<void *> *children;
} Group;

typedef struct Info {
    int id;
    DataType type;
} Id;

/*************************************************************************************/

/*************************************************************************************/



void set_node_id(void *node, int id)
{
    Info **info = NULL;

    info = (Info **)node;
    if (info) {
        (*info)->id = id;
    }
}


/*************************************************************************************/

/*************************************************************************************/


void set_node_type(void *node, DataType type)
{

    Info **info = NULL;

    info = (Info **)node;
    if (info) {
        (*info)->type = type;
    }
}


/*************************************************************************************/

/*************************************************************************************/


int get_node_id(void *node)
{
    Info **info = NULL;
    int value = -1;

    info = (Info **)node;
    if (info) {
        value = (*info)->id;
    }
    return value;
}


/*************************************************************************************/

/*************************************************************************************/


DataType get_node_type(void *node)
{
    Info **info = NULL;
    DataType value = UNKNOWN;

    info = (Info **)node;
    if (info) {
        if (*info) {
            value = (*info)->type;
        }
    }
    return value;
}


/*************************************************************************************/

/* Shape */

/*************************************************************************************/

Shape *new_shape()
{
    Shape *shape = NULL;

    shape = new Shape;
    if (shape) {
        shape->info = new Info;
        set_node_type(shape, SHAPE);
        shape->point[0] = 0;
        shape->point[1] = 0;
        shape->point[2] = 0;
    }
    return shape;
}

/*************************************************************************************/

/* Transform */

/*************************************************************************************/

Transform *new_transform()
{
    Transform *transform = NULL;

    transform = new Transform;
    if (transform) {
        transform->info = new Info;
        set_node_type(transform, TRANSFORM);
        transform->children = NULL;
    }
    return transform;
}
/*************************************************************************************/

/* Group */

/*************************************************************************************/

Group *new_group()
{
    Group *group = NULL;

    group = new Group;
    if (group) {
        group->info = new Info;
        set_node_type(group, GROUP);
        group->children = NULL;
    }
    return group;
}

void set_transform_translation(Transform *transform, double x, double y, double z)
{
    if (transform) {
        transform->translation[0] = x;
        transform->translation[1] = y;
        transform->translation[2] = z;
    }
}


vector<void *> *get_children(void *data)
{
    DataType type = UNKNOWN;

    type = get_node_type(data);

    if (type == TRANSFORM) {
        cout << "\tTransform" << endl;
        return ((Transform *)data)->children;
    }else if (type == GROUP) {
        cout << "\tGroup" << endl;
        return ((Group *)data)->children;
    }else if (type == SHAPE) {
        cout << "\tShape" << endl;
        return NULL;
    }

}

void print_transform(Transform *transform)
{
    cout << "\t Transform translation:" << "  x:" << transform->translation[0] << "  y:" << transform->translation[1] << "  z:" << transform->translation[2] << endl;
}

void copy_transform_data(Transform *destination, Transform *source)
{


    if (destination && source) {
        destination->translation[0] = source->translation[0];
        destination->translation[1] = source->translation[1];
        destination->translation[2] = source->translation[2];
    }
}

void get_transform_data(void *data, Transform *transform)
{
    DataType type = UNKNOWN;
    Transform *transform_tmp = NULL;

    type = get_node_type(data);
    if (type == TRANSFORM) {
        transform_tmp = (Transform *)data;

        if (transform_tmp) {
            //cout << "SSSSSSSSS" << endl;
            transform->translation[0] = transform_tmp->translation[0];
            transform->translation[1] = transform_tmp->translation[1];
            transform->translation[2] = transform_tmp->translation[2];
        }

    }
}

void print_shape(Shape *shape)
{
    if (shape) {
        cout << "\t Shape "<< "  x:" << shape->point[0] << "  y:" << shape->point[1] << "  z:" << shape->point[2] << endl;
    }
}

void add_to_shape(void *data, Transform *transform)
{
    DataType type = UNKNOWN;
    Shape *shape = NULL;

    type = get_node_type(data);

    if (type == SHAPE) {

        shape = (Shape *)data;
        if (shape && transform) {

            shape->point[0] += transform->translation[0];
            shape->point[1] += transform->translation[1];
            shape->point[2] += transform->translation[2];

            print_shape(shape);

        }
    }
}

void calc(void *data, Transform *transform, vector<void *> *transform_stack, vector<void *> *prev_children, int *deep)
{

    vector<void *> *p_children = NULL;
    vector<void *>::iterator it;
    Transform transform_local;
    static int count = 0;

    (*deep)++;
    cout << "DEEP  " << *deep << endl;

    count++;

    get_transform_data(data, transform);

    copy_transform_data(&transform_local, transform);

    p_children = get_children(data);

    //print_transform(&transform_local);

    if (get_node_type(data) == TRANSFORM) {
        transform_stack->push_back(data);
    }

    if (p_children) {


        for (it = p_children->begin(); it != p_children->end(); ++it) {


            calc(*it, transform, transform_stack, p_children, deep);

        }



    }

    if (get_node_type(data) == SHAPE) {
        int i = 0;
        int len = 0;
        Transform *tmp = NULL;



        len = transform_stack->size();

        for ( i = len - 1; i >= 0; --i) {

            tmp = (Transform *)transform_stack->at(i);
            print_transform(tmp);
            add_to_shape(data, tmp);
        }
    }

    //add_to_shape(data, &transform_local);


    (*deep)--;

}

void vrml_calc(vector<void *> *node_stack)
{
   vector<void *>::iterator it;
   int deep = -1;
   Transform *transform = new_transform();
   vector<void *> *transform_stack = new vector<void *>;
   for (it = node_stack->begin(); it != node_stack->end(); ++it) {
       calc(*it, transform, transform_stack, NULL, &deep);
   }

}

int main()
{
    vector<void *> *node_stack = new vector<void *>;

    vector<void *> *p_children1 = new vector<void *>;
    vector<void *> *p_children2 = new vector<void *>;

    Transform *transform1 = new_transform();
    Transform *transform2 = new_transform();

    Shape *shape1 = new_shape();
    Shape *shape2 = new_shape();

    set_transform_translation(transform1, 1, 1, 1);
    set_transform_translation(transform2, 2, 2, 2);

    p_children1->push_back(shape1);
    p_children1->push_back(transform2);


    p_children2->push_back(shape2);

    transform1->children = p_children1;
    transform2->children = p_children2;

    node_stack->push_back(transform1);

    vrml_calc(node_stack);

}

