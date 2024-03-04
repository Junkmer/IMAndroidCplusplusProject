package com.tencent.cloud.tuikit.roomkit.view.component;

import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.text.TextUtils;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;

import com.tencent.cloud.tuikit.roomkit.R;
import com.tencent.cloud.tuikit.roomkit.model.RoomStore;
import com.tencent.cloud.tuikit.roomkit.model.manager.RoomEngineManager;
import com.tencent.cloud.tuikit.roomkit.view.base.BaseBottomDialog;
import com.tencent.qcloud.tuicore.util.ToastUtil;

public class MemberInviteView extends BaseBottomDialog {
    private static final String URL_ROOM_KIT_WEB = "https://web.sdk.qcloud.com/component/tuiroom/index.html";
    private static final String LABEL            = "Label";

    private Context         mContext;
    private RoomStore       mRoomStore;
    private TextView        mTextRoomId;
    private TextView        mTextroomLink;
    private LinearLayout    mButtonCopyRoomId;
    private LinearLayout    mButtonCopyRoomLink;
    private RelativeLayout  mRootCopyRoomLink;

    public MemberInviteView(@NonNull Context context) {
        super(context);
    }

    @Override
    protected int getLayoutId() {
        return R.layout.tuiroomkit_dialog_invite;
    }

    @Override
    protected void initView() {
        mContext = getContext();
        mRoomStore = RoomEngineManager.sharedInstance(mContext).getRoomStore();
        mTextRoomId = findViewById(R.id.invite_room_id);
        mRootCopyRoomLink = findViewById(R.id.tuiroomkit_root_room_link);
        mTextroomLink = findViewById(R.id.invite_room_link);
        mButtonCopyRoomId = findViewById(R.id.btn_invite_copy_room_id);
        mButtonCopyRoomLink = findViewById(R.id.btn_invite_copy_room_link);

        mTextRoomId.setText(mRoomStore.roomInfo.roomId);
        mTextroomLink.setText(getRoomURL());
        mRootCopyRoomLink.setVisibility(needShowRoomLink() ? View.VISIBLE : View.GONE);

        mButtonCopyRoomId.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                copyContentToClipboard(mTextRoomId.getText().toString(),
                        mContext.getString(R.string.tuiroomkit_copy_room_id_success));
            }
        });

        mButtonCopyRoomLink.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                copyContentToClipboard(mTextroomLink.getText().toString(),
                        mContext.getString(R.string.tuiroomkit_copy_room_line_success));
            }
        });
    }

    public String getRoomURL() {
        String packageName = mContext.getPackageName();
        if (TextUtils.equals(packageName, "com.tencent.liteav.tuiroom")) {
            return "https://web.sdk.qcloud.com/trtc/webrtc/test/tuiroom-inner/index.html#/room?roomId="
                    + mRoomStore.roomInfo.roomId;
        } else if (TextUtils.equals(packageName, "com.tencent.trtc")) {
            return "https://web.sdk.qcloud.com/component/tuiroom/index.html#/room?roomId=" + mRoomStore.roomInfo.roomId;
        } else {
            return null;
        }
    }

    public boolean needShowRoomLink() {
        String packageName = mContext.getPackageName();
        return TextUtils.equals(packageName, "com.tencent.liteav.tuiroom") || TextUtils.equals(packageName,
                "com.tencent.trtc");
    }

    private void copyContentToClipboard(String content, String msg) {
        ClipboardManager cm =  (ClipboardManager) mContext.getSystemService(Context.CLIPBOARD_SERVICE);
        ClipData mClipData = ClipData.newPlainText(LABEL, content);
        cm.setPrimaryClip(mClipData);
        ToastUtil.toastShortMessageCenter(msg);
    }
}
