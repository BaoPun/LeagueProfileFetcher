#include "./Champion.h"

Champion::Champion(){
    this->id = -1;
    this->name = this->image_url = this->spell_url = "";
    this->title = this->lore = "";
    this->resource_type = "";
}

// Accessors
int Champion::get_id(){
    return this->id;
}

QString Champion::get_name(){
    return this->name;
}

QString Champion::get_image_url(){
    return this->image_url;
}

QString Champion::get_spell_url(){
    return this->spell_url;
}

QString Champion::get_title(){
    return this->title;
}

QString Champion::get_lore(){
    return this->lore;
}

QString Champion::get_resource_type(){
    return this->resource_type;
}

// Mutators
void Champion::set_id(int id){
    this->id = id;
}

void Champion::set_name(QString name){
    this->name = name;
}

void Champion::set_image_url(QString image_url){
    this->image_url = image_url;
}

void Champion::set_spell_url(QString spell_url){
    this->spell_url = spell_url;
}

void Champion::set_title(QString title){
    this->title = title;
}

void Champion::set_resource_type(QString resource_type){
    this->resource_type = resource_type;
}

void Champion::set_lore(QString lore){
    this->lore = lore;
}
