#include "stdafx.h"
#include "Request.h"


Request::Request(int header, char* full_message) : header(header), full_message(full_message)
{

}

Request::~Request() {


}
