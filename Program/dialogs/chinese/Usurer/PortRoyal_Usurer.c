// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你做什么? "), "你不久前刚问过我这个问题... ", "没错, 让我猜猜... 又在绕圈子了? ",
                          "听着, 我在这里管财务, 不回答问题... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "唔, 我的记性哪去了... ",
                      "你猜对了, 抱歉... ", "我明白了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// --> Sinistra 旧日罪孽的漫长阴影	
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				link.l1 = "告诉我, 上校来找过你吗? 他说你有份奖赏给我。 ";
				link.l1.go = "DTSG_depozit_1";
			}
			// <—— 旧日罪孽的漫长阴影
		break;
		
		// --> Sinistra 旧日罪孽的漫长阴影	
		case "DTSG_depozit_1":
			dialog.text = "哪个上校? ";
			link.l1 = "托马斯.林奇。 ";
			link.l1.go = "DTSG_depozit_2";
		break;
		
		case "DTSG_depozit_2":
			dialog.text = "小声点! 我认识那个人。 没错, 他来过。 你的奖赏在等着你, 船长。 ";
			link.l1 = "有多少? ";
			link.l1.go = "DTSG_depozit_3";
		break;
		
		case "DTSG_depozit_3":
			dialog.text = "整整一万金币。 一个比索都没有 --全是金币。 ";
			link.l1 = "至少不是三十块银币... ";
			link.l1.go = "DTSG_depozit_4";
			AddItems(pchar, "chest", 70);
			Log_Info("你获得了70个宝箱");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_depozit_4":
			dialog.text = "你说什么? ";
			link.l1 = "哦, 没什么... 谢谢。 再见。 ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.DTSG_depozit");
		break;
		// <-- 旧日罪孽的漫长阴影
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 不要忘记卸载
}