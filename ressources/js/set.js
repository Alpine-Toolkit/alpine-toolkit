/**
 * Creates a new set instance and initializes the underlying data structure
 *
 * @constructor
 * @param {object|string|number} args variable number of arguments to
 *        initialize the set, can be an array or individual arguments
 */
function Set(args) {
    var set = [];
    if (args) {
        for (var i = 0; i < arguments.length; i++) {
	    var item = arguments[i];
            if (item instanceof Array) {
                for (var j = 0; j < item.length; j++)
                    set_add(item[j]);
            } else {
                set_add(item);
            }
        }
    }
    return set;
}

/**
 * Adds an item to the set
 * If the set already contains the item, it is not added
 *
 * @param {object|string|number} value the data of the item to add to the set
 * @returns {boolean} true if the item is added to the set; false otherwise
 */
function set_add (set, value) {
    if (!set_has(set, value)) {
        set.push(value);
        return true;
    }
    return false;
}

/**
 * Removes an item from the set
 *
 * @param {object|string|number} value the data of the item to remove from the set
 * @returns {object|string|number} the item that was removed from the
 *          set.  If the item is not in the set, returns null
 */
function set_remove (set, value) {
    var index = set.indexOf(value);
    if (index === -1)
        return null;
    else
        return set.splice(index, 1)[0];
}

/**
 * Determines of the set contains, or has, the value
 *
 * @param {object|string|number} value the value of the item to find in the set
 * @returns {boolean} true if the set has the value; false otherwise
 */
function set_has (set, value) {
    return set.indexOf(value) > -1;
}

/**
 * Clears all the items from the set
 */
function set_clear (set) {
    set = [];
}

/**
 * Returns the size, or number of items in the set
 *
 * @returns {number} the number of items in the set
 */
function set_size (set) {
    return set.length;
}

/**
 * Determines if the set is empty
 *
 * @returns {boolean} true if the set is empty, false otherwise
 */
function set_is_empty (set) {
    return set.length === 0;
}

/**
 * Returns a Set that is the union of the sets.  The returned set will
 * contain all the elements from both sets, and by definition, will
 * not contain any duplicates.
 *
 * @param {object} otherSet the set to union with this
 * @returns {object} a set which is a union of this and the 'otherSet'
 */
function set_union (set1, set2) {
    var union_set = Set(set1);

    set2.forEach(function(value) {
	set_add(union_set, value);
    });

    return union_set;
}

/**
 * Returns a Set that is the intersection of the sets, the returned
 * set will have only those items that both sets have in common.
 *
 * @param {object} otherSet the set to intersect with this
 * @returns {object} a set which is an intersection of this and the 'otherSet'
 */
function set_intersection (set1, set2) {
    var intersection_set = Set();

    set1.forEach(function(value) {
        if (set_has(set2, value))
	    intersection_set.push(value);
    });

    return intersection_set;
}

/**
 * Returns a Set that is the difference of the sets. The returned set
 * will have those items that are contained in set1, but not contained
 * in set2.
 *
 * @param {object} otherSet the set to use to determine the difference
 * @returns {object} a set which is an difference of this and the 'otherSet'
 */
function set_difference (set1, set2) {
    var difference_set = Set();

    set1.forEach(function(value) {
        if (!set_has(set2, value))
	    difference_set.push(value);
    });

    return difference_set;
}

// /**
//  * Returns whether or not this set is a subset of the 'otherSet'.  If all
//  * items of this set are contained in the otherSet, this function returns
//  * true; false otherwise.
//  *
//  * @param {object} otherSet the set to use to determine if this set is a subset
//  * @returns {boolean} true if this set is a subset of the 'otherSet', false
//  *          otherwise
//  *
//  * @throws {TypeError} if 'otherSet' is not a Set
//  */
// subset: function (otherSet) {
//     // if the 'otherSet' is not a Set, throw TypeError
//     if (!(otherSet instanceof Set)) {
//         throw new TypeError('invalid parameter type; a Set is required');
//     }
// 
//     // if the size of this set is greater than the size of the otherSet,
//     // we know this cannot be a subset of the otherSet
//     if (this.size() > otherSet.size()) {
//         return false;
//     } else {
//         var values = this.values();
//         for (var i = 0; i < values.length; i++) {
//             if (!otherSet.has(values[i])) {
//                 return false;
//             }
//         }
//         return true;
//     }
// }
