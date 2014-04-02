package com.ford.syncV4.protocol;

/**
 * Created with Android Studio.
 * Author: Chernyshov Yuriy - Mobile Development
 * Date: 02.04.14
 * Time: 13:07
 */

import com.ford.syncV4.proxy.constants.ProtocolConstants;

/**
 * This class handle protocol version and version negotiation
 */
public class ProtocolVersion {

    /**
     * Current actual version for the SDK to operate with SDL
     */
    private byte mCurrentVersion;

    /**
     * Constructor
     */
    public ProtocolVersion() {
        // Set up default value
        mCurrentVersion = ProtocolConstants.PROTOCOL_VERSION_MIN;
    }

    /**
     * @return current actual protocol version,
     * see {@link com.ford.syncV4.proxy.constants.ProtocolConstants} for more information
     */
    public byte getCurrentVersion() {
        return mCurrentVersion;
    }

    /**
     * Set up current actual protocol version,
     * see {@link com.ford.syncV4.proxy.constants.ProtocolConstants} for more information
     * @param value version of protocol
     */
    public void setCurrentVersion(byte value) {
        mCurrentVersion = negotiateVersion(value);
    }

    private byte negotiateVersion(byte value) {
        // Check if the value in the byte is numerical
        if ((int) value <= 0 || (int) value > 100) {
            return mCurrentVersion;
        }
        if (value < ProtocolConstants.PROTOCOL_VERSION_MIN) {
            return value;
        }
        if (value >= ProtocolConstants.PROTOCOL_VERSION_MAX) {
            return ProtocolConstants.PROTOCOL_VERSION_MAX;
        }
        return mCurrentVersion;
    }
}