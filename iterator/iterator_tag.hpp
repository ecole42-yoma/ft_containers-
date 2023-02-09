#pragma once
#ifndef __ITERATOR_TAG_HPP__
#define __ITERATOR_TAG_HPP__

namespace ft {

/**
 * * [ iterator tag ] ------------------------------------------------------------------------------
 */
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

}
#endif
