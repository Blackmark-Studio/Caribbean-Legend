// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你做什么? "), "你不久前就想问我问题... ", "在托尔图加的商店里, 很久没人问过那样的问题了... ",
                          "问题, 问题, 还是问题... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "嗯, 我的记性哪儿去了... ",
                      "好吧, 确实有段时间了。 ", "更多的问题, 是的... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga2")
			{
				link.l1 = "听着, 我需要找盖乌斯.马沙。 有人告诉我, 他从事私掠活动, 成了一个不错的谈判者, 从西班牙人那里搞到了一艘极好的大帆船。 他有没有碰巧从你这里购买过任何用于交易的商品? ";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "盖乌斯.马沙? 哦, 是的, 我当然记得他! 但他什么也没买。 他提出用他的船来运货。 我刚好需要一艘货舱宽敞的船 --一大批生皮。 ";
			link.l1 = "卸货点在哪里? ";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "圣马丁的菲利普斯堡。 ";
			link.l1 = "好的。 谢谢你, 你帮了我大忙! ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "随时为你服务, 船长。 欢迎随时来我的商店! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "10");
			pchar.questTemp.Guardoftruth = "maarten";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}