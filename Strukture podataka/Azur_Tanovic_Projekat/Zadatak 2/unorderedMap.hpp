#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>

int hash(std::string s){
    size_t sum = 5381;
    for(char c : s){
        sum += (sum << 4) + c;
    }
    return sum;
}

template <typename K, typename M>
class UnorderedMap{
    public:
    using key_type = K;
    using mapped_type = M;
    using value_type = std::pair<key_type, mapped_type>;
    using bucket_type = std::list<value_type>;
    UnorderedMap();
    class Iterator;
    Iterator begin();
    Iterator end();
    Iterator find(const key_type&);
    void emplace(key_type, mapped_type); //done
    mapped_type& operator[](const key_type&); //done
    bool erase(const key_type&);

    private:
    std::vector<bucket_type> storage_;
    const static int storageSize_ = 100;
    int size_;
};

template <typename K, typename M>
UnorderedMap<K, M>::UnorderedMap() : size_{0} { storage_.resize(100); }

template <typename K, typename M>
void UnorderedMap<K, M>::emplace(key_type key, mapped_type value){
    auto index = hash(key) % storageSize_;
    auto& bucket = storage_[index];
    for(auto& [k, v] : bucket){
        if(k == key)
            throw std::invalid_argument("Key already exists");
    }
    bucket.push_back(value_type(key, value));
    ++size_;
}

template <typename K, typename M> 
M& UnorderedMap<K, M>::operator[](const key_type& key){
    auto index = hash(key) % storageSize_;
    auto& bucket = storage_[index];
    for(auto& [k, v] : bucket){
        if(k == key)
            return v;
    }
    bucket.push_back(value_type(key, mapped_type{}));
    ++size_;
    return bucket.back().second;
}

template <typename K, typename M>
typename UnorderedMap<K, M>::Iterator UnorderedMap<K, M>::find(const key_type& key){
    auto index = hash(key) % storageSize_;
    auto* bucket = &storage_[index];
    for(auto it = bucket->begin(); it != bucket->end(); it++){
        if(it->first == key)
            return Iterator(it, bucket);
    }
    return Iterator(bucket->end(), bucket);
}

template <typename K, typename M>
bool UnorderedMap<K, M>::erase(const key_type& key){
    auto index = hash(key) % storageSize_;
    auto& bucket = storage_[index];
    auto it = bucket.begin();
    for(auto& [k, v] : bucket){
        if(k == key){
            it = bucket.erase(it);
            return true;
        } else
            it++;
    }
    return false;
}


template <typename K, typename M>
class UnorderedMap<K, M>::Iterator : public std::iterator<std::bidirectional_iterator_tag, value_type> {
    public:
    Iterator(typename std::list<value_type>::iterator it, bucket_type* pos) : it_{it}, pos_{pos} {};
    value_type& operator*() const { return *it_; };
    value_type* operator->(){ return &(*it_); };
    Iterator operator++();
    Iterator operator++(int);
    Iterator operator--();
    Iterator operator--(int);
    friend bool operator==(const Iterator& a, const Iterator& b) { return a.it_ == b.it_; };
    friend bool operator!=(const Iterator& a, const Iterator& b) { return a.it_ != b.it_; };
    
    private:
    typename std::list<value_type>::iterator it_;
    bucket_type* pos_;
    size_t posCounter_ = 0;
};

template <typename K, typename M>
typename UnorderedMap<K, M>::Iterator UnorderedMap<K, M>::begin(){
    bucket_type* bucket = &storage_[0];
    return Iterator(bucket->begin(), bucket);
}

template <typename K, typename M>
typename UnorderedMap<K, M>::Iterator UnorderedMap<K, M>::end(){
    bucket_type* bucket = &storage_[storageSize_ - 1];
    return Iterator(bucket->end(), bucket);
}

template <typename K, typename M>
typename UnorderedMap<K, M>::Iterator UnorderedMap<K, M>::Iterator::operator++(){
    if(++it_ == pos_->end()){
        if(posCounter_ < storageSize_ - 1){
            pos_++;
            posCounter_++;
            it_ = pos_->begin();
        } else{
            posCounter_ = 0;
            *this = Iterator(it_, pos_);
            return *this;
        }
    }
    while(pos_->empty() && posCounter_ < storageSize_ - 1){
        pos_++;
        posCounter_++;
        it_ = pos_->begin();
    } 
    return *this; 
}

// template <typename K, typename M>
// typename UnorderedMap<K, M>::Iterator UnorderedMap<K, M>::Iterator::operator--(){
//     if(--it_ == pos_->begin()){
//         if(posCounter_ < storageSize_ - 1){
//             pos_--;
//             posCounter_++;
//             it_ = pos_->end();
//         } else{
//             posCounter_ = 0;
//             *this = Iterator(it_, pos_);
//             return *this;
//         }
//     }
//     while(pos_->empty() && posCounter_ < storageSize_ - 1){
//         pos_--;
//         posCounter_++;
//         it_ = pos_->end();
//     } 
//     return *this; 
// }

// template <typename K, typename M>
// typename UnorderedMap<K, M>::Iterator UnorderedMap<K, M>::Iterator::operator--(int){
//     auto tmp = *this;
//     if(--it_ == pos_->begin()){
//         if(posCounter_ < storageSize_ - 1){
//             pos_--;
//             posCounter_++;
//             it_ = pos_->end();
//         } else{
//             posCounter_ = 0;
//             *this = Iterator(it_, pos_);
//             return tmp;
//         }
//     }
//     while(pos_->empty() && posCounter_ < storageSize_ - 1){
//         pos_--;
//         posCounter_++;
//         it_ = pos_->end();
//     } 
//     return tmp; 
// }

template <typename K, typename M>
typename UnorderedMap<K, M>::Iterator UnorderedMap<K, M>::Iterator::operator++(int){
    auto tmp = *this;    
    if(++it_ == pos_->end()){
        if(posCounter_ < storageSize_ - 1){
            pos_++;
            posCounter_++;
            it_ = pos_->begin();
        } else {
            posCounter_ = 0;
            *this = Iterator(it_, pos_);
            return tmp;
        }
    }
    while(pos_->empty() && posCounter_ < storageSize_ - 1){
        pos_++;
        posCounter_++;
        it_ = pos_->begin();
    };
    return tmp;
}