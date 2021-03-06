// vim: set ts=4 sw=4 tw=99 noet:
//
// AMX Mod X, based on AMX Mod by Aleksander Naszko ("OLO").
// Copyright (C) The AMX Mod X Development Team.
//
// This software is licensed under the GNU General Public License, version 3 or higher.
// Additional exceptions apply. For full license details, see LICENSE.txt or visit:
//     https://alliedmods.net/amxmodx-license

//
// Fakemeta Functions
//

#if defined _fakemeta_included
	#endinput
#endif
#define _fakemeta_included

#include <fakemeta_const> 

#pragma reqlib fakemeta
#if !defined AMXMODX_NOAUTOLOAD
	#pragma loadlib fakemeta
#endif

/**
 * Returns entvar data from an entity.  Use the pev_* enum (in fakemeta_const.inc) to specify which data you want retrieved.
 *
 * @note	This function uses "read_data" style data syntax.  It returns integer values,
 *				by-references float data, and sets a buffer for string data.
 *
 * @note	If retrieving strings, you may optionally get a pointer into the global string table. Depending on
 * 			your situation, there are two ways to do this.
 * 			1: This simply gets the pointer.
 * 			   new ptr = pev(entid, pev_classname)
 * 			2: The pointer will be stored in ptr AND the actual string is retrieved.
 * 			   new ptr, classname[32]
 * 			   pev(entid, pev_classname, ptr, classname, 31)
 *
 * @param	_index		The entity index to lookup.
 * @param	_value		The pev field to lookup (look in fakemeta_const.inc)
 */
native pev(_index,_value,any:...);

/**
 * Sets entvar data for an entity.  Use the pev_* enum from fakemeta_const.inc for reference.
 *
 * @note	Setting string data will automatically allocate a new string (via AllocString)
 *			If you have a string already allocated with your own call to AllocString, use
 *			set_pev_string_ptr instead.
 *
 * @param	_index		The entity index to set the value on.
 * @param	_value		The pev field to set, (look in fakemeta_const.inc)
 */
native set_pev(_index,_value,any:...);

/**
 * Use this native to set a pev field to a string that is already allocated (via a function such
 * as EngFunc_AllocString).
 *
 * @note	If you specify _value as anything other than string fields, an error will be thrown.
 * @note	Pass 0 as the _string field to set it to an empty string.
 *
 * @param	_index		The entity index to set the value on.
 * @param	_value		The pev field to set - MUST be a string field.
 * @param	_string		The string handle, retrieved from places like AllocString.
 */
native set_pev_string(_index, _value, _string);


/**
 * Checks the validity of an entity.
 *
 * @param entindex		The entity id to check.
 *
 * @return 			0 on invalid entity
 *						1 on entity is valid
 *						2 on entity is valid and it has private data (safe to use pdata natives on).
 */
native pev_valid(entindex);

/**
 * Returns the serial number for each entity.  The serial number is a unique identity 
 * generated when an entity is created.
 * 
 * @param	entindex	The entity id.
 *
 * @return				The serial number for the entity.
 */
native pev_serial(entindex);

/* Returns any global variable inside globalvars_t structure. Use the glb_* enum.
 *
 * When returning data from glb_pStringBase (the global string table), you may give a pointer into that table
 * in order to get different strings.
 * Example:
 * new model[128]
 * new ptr = pev(id, pev_viewmodel)
 * global_get(glb_pStringBase, ptr, model, 127)
 */
native global_get(_value, any:...);

/**
 * Returns a integer from an entity's private data.
 *
 * _linuxdiff value is what to add to the _Offset for linux servers.
 * _macdiff value is what to add to the _Offset for os x servers.
 * 
 * A log error is thrown on invalid _index and _Offset.
 * 
 * @param _index        Entity index.
 * @param _Offset       Offset to search.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              An integer value is returned.
 */
native get_pdata_int(_index, _Offset, _linuxdiff = 5, _macdiff = 5);

/**
 * Sets an integer to an entity's private data.
 *
 * _linuxdiff value is what to add to the _Offset for linux servers.
 * _macdiff value is what to add to the _Offset for os x servers.
 * 
 * A log error is thrown on invalid _index and _Offset.
 * 
 * @param _index        Entity index.
 * @param _Offset       Offset to search.
 * @param _Value        Value to set.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              1 on success.
 */
native set_pdata_int(_index, _Offset, _Value, _linuxdiff = 5, _macdiff = 5);

/**
 * Returns a float from an entity's private data.
 *
 * _linuxdiff value is what to add to the _Offset for linux servers.
 * _macdiff value is what to add to the _Offset for os x servers.
 * 
 * A log error is thrown on invalid _index and _Offset.
 * 
 * @param _index        Entity index.
 * @param _Offset       Offset to search.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              An float value is returned.
 */
native Float:get_pdata_float(_index, _Offset, _linuxdiff = 5, _macdiff = 5);

/**
 * Sets a float to an entity's private data.
 *
 * _linuxdiff value is what to add to the _Offset for linux servers.
 * _macdiff value is what to add to the _Offset for os x servers.
 * 
 * A log error is thrown on invalid _index and _Offset.
 * 
 * @param _index        Entity index.
 * @param _Offset       Offset to search.
 * @param _Value        Value to set.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              1 on success.
 */
native set_pdata_float(_index, _Offset, Float:_Value, _linuxdiff = 5, _macdiff = 5);

/**
 * Tries to retrieve an edict pointer from an entity's private data.
 *
 * This function is byte-addressable.  Unlike get_pdata_int() which searches in byte increments of 4, 
 * get_pdata_ent searches in increments of 1.
 *
 * _linuxdiff value is what to add to the _offset for linux servers.
 * _macdiff value is what to add to the _offset for os x servers.
 *
 * A log error is thrown on invalid _index and _Offset.
 * 
 * @param _index		Entity index.
 * @param _offset		Offset to search.
 * @param _linuxdiff	Linux difference.
 * @param _macdiff		Mac OS X difference.
 * @return				-2 if an invalid entity was found.
 *						-1 if an empty entity was found.
 * 						Otherwise, an entity index is returned.
 */
native get_pdata_ent(_index, _offset, _linuxdiff = 20, _macdiff = 20);

/**
 * Sets an edict pointer to an entity's private data.
 *
 * This function is byte-addressable.  Unlike set_pdata_int() which searches in byte increments of 4, 
 * set_pdata_ent searches in increments of 1.
 *
 * _linuxdiff value is what to add to the _offset for linux servers.
 * _macdiff value is what to add to the _offset for os x servers.
 * 
 * A log error is thrown on invalid _index and _offset.
 * 
 * @param _index        Entity index.
 * @param _offset       Offset to search.
 * @param _value        Value to set.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              1 on success.           
 */
native set_pdata_ent(_index, _offset, _value, _linuxdiff = 20, _macdiff = 20);

/**
 * Returns a boolean from an entity's private data.
 *
 * This function is byte-addressable. Unlike get_pdata_int() which searches in byte increments of 4, 
 * get_pdata_bool searches in increments of 1.
 *
 * _linuxdiff value is what to add to the _offset for linux servers.
 * _macdiff value is what to add to the _offset for os x servers.
 * 
 * A log error is thrown on invalid _index and _offset.
 * 
 * @param _index        Entity index.
 * @param _offset       Offset to search.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              An boolean value is returned.
 */
native bool:get_pdata_bool(_index, _offset, _linuxdiff = 20, _macdiff = 20);

/**
 * Sets a boolean to an entity's private data.
 *
 * This function is byte-addressable. Unlike set_pdata_int() which searches in byte increments of 4, 
 * set_pdata_bool searches in increments of 1.
 * 
 * _linuxdiff value is what to add to the _offset for linux servers.
 * _macdiff value is what to add to the _offset for os x servers.
 *
 * A log error is thrown on invalid _index and _offset.
 * 
 * @param _index        Entity index.
 * @param _offset       Offset to search.
 * @param _value        Value to set.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              1 on success.
 */
native set_pdata_bool(_index, _offset, bool:_value, _linuxdiff = 20, _macdiff = 20);

/**
 * Returns a byte value from an entity's private data.
 *
 * This function is byte-addressable. Unlike get_pdata_int() which searches in byte increments of 4, 
 * get_pdata_byte searches in increments of 1.
 * 
 * _linuxdiff value is what to add to the _offset for linux servers.
 * _macdiff value is what to add to the _offset for os x servers.
 *
 * A log error is thrown on invalid _index and _offset.
 * 
 * @param _index        Entity index.
 * @param _offset       Offset to search.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              A byte value is returned.
 */
native get_pdata_byte(_index, _offset, _linuxdiff = 20, _macdiff = 20);

/**
 * Sets a byte value to an entity's private data.
 *
 * This function is byte-addressable. Unlike set_pdata_int() which searches in byte increments of 4, 
 * set_pdata_byte searches in increments of 1.
 *
 * _linuxdiff value is what to add to the _offset for linux servers.
 * _macdiff value is what to add to the _offset for os x servers.
 * 
 * A log error is thrown on invalid _index and _offset.
 * 
 * @param _index        Entity index.
 * @param _offset       Offset to search.
 * @param _value        Value to set.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              1 on success.
 */
native set_pdata_byte(_index, _offset, _value, _linuxdiff = 20, _macdiff = 20);

/**
 * Returns a short value from an entity's private data.
 *
 * This function is byte-addressable. Unlike get_pdata_int() which searches in byte increments of 4, 
 * get_pdata_short searches in increments of 1.
 * 
 * _linuxdiff value is what to add to the _offset for linux servers.
 * _macdiff value is what to add to the _offset for os x servers.
 *
 * A log error is thrown on invalid _index and _offset.
 * 
 * @param _index        Entity index.
 * @param _offset       Offset to search.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              A short value is returned.
 */
native get_pdata_short(_index, _offset, _linuxdiff = 20, _macdiff = 20);

/**
 * Sets a short value to an entity's private data.
 *
 * This function is byte-addressable.  Unlike set_pdata_int() which searches in byte increments of 4, 
 * set_pdata_short searches in increments of 1.
 *
 * _linuxdiff value is what to add to the _offset for linux servers.
 * _macdiff value is what to add to the _offset for os x servers.
 * 
 * A log error is thrown on invalid _index and _offset.
 * 
 * @param _index        Entity index.
 * @param _offset       Offset to search.
 * @param _value        Value to set.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              1 on success.  
 */
native set_pdata_short(_index, _offset, _value, _linuxdiff = 20, _macdiff = 20);

/**
 * Returns a vector from an entity's private data.
 *
 * This function is byte-addressable. Unlike get_pdata_int() which searches in byte increments of 4, 
 * get_pdata_vector searches in increments of 1.
 * 
 * _linuxdiff value is what to add to the _offset for linux servers.
 * _macdiff value is what to add to the _offset for os x servers.
 *
 * A log error is thrown on invalid _index and _offset.
 * 
 * @param _index        Entity index.
 * @param _offset       Offset to search.
 * @param _output       Vector returned by reference.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              1 on success.     
 */
native get_pdata_vector(_index, _offset, Float:_output[3], _linuxdiff = 20, _macdiff = 20);

/**
 * Sets a vector to an entity's private data.
 *
 * This function is byte-addressable.  Unlike set_pdata_int() which searches in byte increments of 4, 
 * set_pdata_vector searches in increments of 1.
 *
 * _linuxdiff value is what to add to the _offset for linux servers.
 * _macdiff value is what to add to the _offset for os x servers.
 * 
 * A log error is thrown on invalid _index and _Offset.
 * 
 * @param _index        Entity index.
 * @param _offset       Offset to search.
 * @param _origin       Value to set.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              1 on success.   
 */
native set_pdata_vector(_index, _offset, Float:_origin[3], _linuxdiff = 20, _macdiff = 20);

/**
 * Tries to retrieve an edict (entity encapsulation) pointer from an entity's private data.
 *
 * This function is byte-addressable.  Unlike get_pdata_int() which searches in byte increments of 4, 
 * get_pdata_ehandle searches in increments of 1.
 *
 * _linuxdiff value is what to add to the _offset for linux servers.
 * _macdiff value is what to add to the _offset for os x servers.
 * 
 * A log error is thrown on invalid _index and _offset.
 * 
 * @param _index        Entity index.
 * @param _offset       Offset to search.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              -2 if an invalid entity was found.
 *                      -1 if an empty entity was found.
 *                      0 if serialnumber is not matching.
 *                      Otherwise, an entity index is returned.
 */
native get_pdata_ehandle(_index, _offset, _linuxdiff = 20, _macdiff = 20);

/**
 * Sets an edict (entity encapsulation) pointer to an entity's private data.
 *
 * This function is byte-addressable.  Unlike set_pdata_int() which searches in byte increments of 4, 
 * set_pdata_ehandle searches in increments of 1.
 *
 * _linuxdiff value is what to add to the _offset for linux servers.
 * _macdiff value is what to add to the _offset for os x servers.
 * 
 * A log error is thrown on invalid _index and _Offset.
 * 
 * @param _index        Entity index.
 * @param _offset       Offset to search.
 * @param _value        Value to set.
 * @param _linuxdiff    Linux difference.
 * @param _macdiff      Mac OS X difference.
 * @return              1 on success.          
 */
native set_pdata_ehandle(_index, _offset, _value, _linuxdiff = 20, _macdiff = 20);

/* Registers a forward.
 * Returns an id you can pass to unregister_forward
 */
native register_forward(_forwardType,const _function[],_post=0);

/* Unregisters a forward.
 * The registerId must be from register_forward, and
 * post/forwardtype must match what you registered the forward as.
 */
native unregister_forward(_forwardType, registerId, post=0);

/* Returns data for metamod */
native forward_return(type,any:...);

/* Returns the original return value of an engine function. 
 * This is only valid in forwards that were registered as post.
 *
 * get_orig_retval() - no params, retrieves integer return value
 * get_orig_retval(&Float:value) - retrieves float return value by reference
 * get_orig_retval(value[], len) - retrives string return value
 */
native get_orig_retval(any:...);

native engfunc(type,any:...);
native dllfunc(type,any:...);

//only use this with functions that pass a Trace
// get: zero extra params - return int, one extra param = byref float or vector
// set: use anything
native get_tr(TraceResult:tr_member, any:...);
native set_tr(TraceResult:tr_member, any:...);

//Upgraded version takes in a TraceResult handle, optionally passed in as the last parameter to the
//TraceResult forward.  Use 0 to specify the global traceresult handle set from calling 
// some of the Engfucs.
native get_tr2(tr_handle, any:tr_member, any:...);
native set_tr2(tr_handle, any:tr_member, any:...);

/**
 * Creates a traceresult handle.  This value should never be altered.
 * The handle can be used in get/set_tr2 and various traceresult engine functions.
 *
 * NOTE: You must call free_tr2() on every handle made with create_tr2().
 *
 * @return		A new TraceResult handle.
 */
native create_tr2();

/** 
 * Frees a traceresult handle created with free_tr2().  Do not call
 * this more than once per handle, or on handles not created through
 * create_tr2().
 *
 * @param tr_handle	TraceResult handle created via create_tr2().
 * @noreturn
 */
native free_tr2(tr_handle);

//Same as above, use either a kvd_handle or 0 for global reserved kvd data
//kvd_handle is passed by the kvd hook, last param
native get_kvd(kvd_handle, KeyValueData:member, any:...);

//Using set_kvd with the handle from the hook for anything under KV_fHandled
// is considered an undefined operation (it could crash).  You should fire a new
// keyvalues structure rather than changing the internal engine strings.
native set_kvd(kvd_handle, KeyValueData:member, any:...);

/**
 * Creates a KeyValueData handle.
 *
 * @note Handles should be freed using free_kvd().
 *
 * @return		New KeyValueData handle
 */
native create_kvd();

/**
 * Frees a KeyValueData handle.
 *
 * @param kvd_handle	KeyValueData handle
 *
 * @noreturn
 */
native free_kvd(kvd_handle);

// These functions are used with the clientdata data structure (FM_UpdateClientData)
// Get: 0 extra params - Return integer; 1 extra param - by ref float or vector; 2 extra params - string and length
// Set: Use anything
// Use 0 for cd_handle to specify the global clientdata handle
native get_cd(cd_handle, ClientData:member, any:...);
native set_cd(cd_handle, ClientData:member, any:...);

// These functions are used with the entity_state data structure (FM_AddToFullPack)
// Get: 0 extra params - Return integer; 1 extra param - by ref float or vector or array
// Set: Use anything
// Use 0 for es_handle to specify the global entity_state handle
native get_es(es_handle, EntityState:member, any:...);
native set_es(es_handle, EntityState:member, any:...);

// These functions are used with the usercmd data structure (FM_CmdStart)
// Get: 0 extra params - Return integer; 1 extra param - by ref float or vector
// Set: Use anything
// Use 0 for uc_handle to specify the global usercmd handle
native get_uc(uc_handle, UserCmd:member, any:...);
native set_uc(uc_handle, UserCmd:member, any:...);

//NOTE that for the string offsets below, on AMD64, a byref (char **) offset is NOT the same as an int offset
//In fact it's QWORD aligned rather than DWORD aligned, so the offset will be exactly half.
//Gets a string from a private offset.  If byref is false, the string is treated as static rather than dynamic.
//linux value is what to add to the offset for linux servers.
//mac value is what to add to the offset for os x servers. Default (cellmin) means that linux value will be used.
//this cannot use a default value due to older version using an awkward default value.
native get_pdata_string(entity, offset, dest[], maxlength, byref=1, linux, mac=cellmin);

//Sets a string in a private offset.
//realloc = -1 - nonbyref copy (static
//realloc = 0 - copy byref, no realloc *(char **)
//realloc = 1 - reallocate new string with free+malloc
//realloc = 2 - reallocate new string with delete[]+new[]
//linux value is what to add to the offset for linux servers.
//mac value iswhat to add to the offset for os x servers.
//this cannot use a default value due to older version using an awkward default value.
native set_pdata_string(entity, offset, const source[], realloc=2, linux, mac=cellmin);

// Copies the given infoBuffer pointer into out[]
// An infoBuffer pointer is returned by EngFunc_GetInfoKeyBuffer
native copy_infokey_buffer(infoBuffer, out[], maxlen);


/**
 * Looks up the sequence for the entity.
 *
 * @param entity		The entity id to lookup.
 * @param name			The sequence name to lookup, case insensitive. ("JUMP" would match "jump")
 * @param framerate		The framerate of the sequence, if found.
 * @param loops			Whether or not the sequence loops.
 * @param groundspeed	The groundspeed setting of the sequence.
 * @return				-1 on failed lookup, the sequence number on successful lookup.
 */
native lookup_sequence(entity, const name[], &Float:framerate = 0.0, &bool:loops = false, &Float:groundspeed = 0.0);

/**
 * Looks up the sequence for the entity by its activity id.
 *
 * @param entity		The entity id to lookup.
 * @param name			The sequence activity id
 * @param framerate		The framerate of the sequence, if found.
 * @param loops			Whether or not the sequence loops.
 * @param groundspeed	The groundspeed setting of the sequence.
 * @return				-1 on failed lookup, the sequence number on successful lookup.
 */
native lookup_activity(entid, activity_id, &Float:framerate = 0.0, &bool:loops = false, &Float:groundspeed = 0.0);

/**
 * Looks up the sequence for the entity by its id.
 *
 * @param entity		The entity id to lookup.
 * @param name			The sequence id
 * @param framerate		The framerate of the sequence, if found.
 * @param loops			Whether or not the sequence loops.
 * @param groundspeed	The groundspeed setting of the sequence.
 * @return				-1 on failed lookup, the sequence number on successful lookup.
 */
native lookup_sequence_by_id(entid, sequence_id, &Float:framerate = 0.0, &bool:loops = false, &Float:groundspeed = 0.0);


/**
 * Sets a bone controller with the specified value.
 *
 * @param entity		The entity id to set the value on.
 * @param controller	Which controller to set (0 through 3).
 * @param value			The value to set it to.
 * @return				The percentage that the controller is extended (0.0 through 1.0)
 */
native Float:set_controller(entity, controller, Float:value);


enum
{
    Model_DefaultSize     = -2,
    Model_CurrentSequence = -1,
};

/**
 * Gets size of the entity models collision box.
 *
 * @param entity        The entity index to use.
 * @param mins          The local negative collision box distance.    
 * @param maxs          The local positive collision box distance.    
 * 
 * @return              1 on success, 0 on faillure.
 * 
 * @error               Invalid entity.
 *                      Invalid model pointer.
 */
native GetModelCollisionBox(entity, Float:mins[3], Float:maxs[3]);

/**
 * Sets entity size to the models collision box.
 *
 * @param entity        The entity index to set the value on.
 * 
 * @return              1 on success, 0 on faillure.
 * 
 * @error               Invalid entity.
 *                      Invalid model pointer.
 */
native SetModelCollisionBox(entity);

/**
 * Gets size of a model bounding box.
 *
 * @param entity        The entity index to use.
 * @param mins          The local negative bounding box distance.    
 * @param maxs          The local positive bounding box distance.     
 * @param sequence      The animation sequence to retrieve.
 *                      Model_DefaultSize retrieves ideal moevement hull size.
 *                      Model_CurrentSequence retrieves hull size of the current sequence.
 *                      Values >= 0 will specify which sequence to retrieve size from.
 * 
 * @return              1 on success, 0 on faillure.
 * 
 * @error               Invalid entity.
 *                      Invalid model pointer.
 */
native GetModelBoundingBox(entity, Float:mins[3], Float:maxs[3], sequence = Model_DefaultSize);

/**
 * Sets size to a model bounding box.
 *
 * @param entity        The entity index to set the value on. 
 * @param sequence      The sequence to apply.
 *                      Model_DefaultSize sets size of ideal movement hull.
 *                      Model_CurrentSequence sets size of the current sequence.
 *                      Values >= 0 will specify which sequence to use.
 * 
 * @return              1 on success, 0 on faillure.
 * 
 * @error               Invalid entity.
 *                      Invalid model pointer.
 */
native SetModelBoundingBox(index, sequence = Model_DefaultSize);
