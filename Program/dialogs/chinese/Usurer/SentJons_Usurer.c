// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你做什么? "), "你不久前刚问过我这个问题... ", "没错, 让我猜猜... 又在绕圈子了? ",
                          "听着, 我在这里管财务, 不回答问题... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "嗯, 我的记性哪去了... ",
                      "你猜对了, 抱歉... ", "我明白了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Sinistra 旧日罪孽的漫长阴影	
			if (CheckAttribute(pchar, "questTemp.DTSG_KnippelDolg"))
			{
				link.l1 = "我想和你谈谈你的一个债务人。 ";
				link.l1.go = "DTSG_KnippelDolg";
			}
			// <—— 旧日罪孽的漫长阴影
		break;
		
		// --> Sinistra 旧日罪孽的漫长阴影	
		case "DTSG_KnippelDolg":
			DeleteAttribute(pchar, "questTemp.DTSG_KnippelDolg");
			dialog.text = "哪一个? ";
			if (sti(pchar.reputation.nobility) > 50)
			{
				link.l1 = "(声望) 肯定是查理.尼普尔。 ";
				link.l1.go = "DTSG_KnippelDolg_VD_2";
			}
			else
			{
				link.l2 = "(声望) 你竟敢如此冷静地跟我说话。 你派赏金猎人追捕我的人。 ";
				link.l2.go = "DTSG_KnippelDolg_2";
			}
		break;
		
		case "DTSG_KnippelDolg_VD_2":
			dialog.text = "查理? 但他不再是我的债务人了。 他的债务早就还清了, 先生。 ";
			link.l1 = "真的吗? 如果不是秘密的话, 是谁还的? ";
			link.l1.go = "DTSG_KnippelDolg_VD_3";
		break;
		
		case "DTSG_KnippelDolg_VD_3":
			dialog.text = "不是秘密。 是他的船长理查德.弗利特伍德还的。 一位真正的绅士, 每个人都应该有这样的朋友。 ";
			link.l1 = "你看, 我现在是查理的船长了。 弗利特伍德先生... 把他转到我这儿服务了。 很高兴知道他遵守了承诺, 把钱还给你了。 ";
			link.l1.go = "DTSG_KnippelDolg_VD_4";
		break;
		
		case "DTSG_KnippelDolg_VD_4":
			dialog.text = "所以你才问这个。 ";
			link.l1 = "不止如此。 你很了解查理, 对吧? 他被捕了, 早些时候还派了雇佣兵去追捕他。 知道为什么吗? 毕竟你和非常... 多样化的人群有生意往来。 ";
			link.l1.go = "DTSG_KnippelDolg_VD_5";
		break;
		
		case "DTSG_KnippelDolg_VD_5":
			dialog.text = "查理被捕了? 你让我很惊讶, 先生, 我对此一无所知。 也不知道他的... 敌人。 像他这样一个敬畏上帝的好人... ";
			link.l1 = "这一点无可争辩。 好吧, 不管怎样还是谢谢你。 我希望指挥官会接受我保释他。 ";
			link.l1.go = "DTSG_KnippelDolg_VD_6";
		break;
		
		case "DTSG_KnippelDolg_VD_6":
			dialog.text = "如果你需要资金保释, 随时再来找我 --我会给你优惠条件。 ";
			link.l1 = "哈哈, 你是认真的吗? 放债人终究是放债人。 我自己付得起保释金。 再见。 ";
			link.l1.go = "DTSG_KnippelDolg_VD_7";
		break;
		
		case "DTSG_KnippelDolg_VD_7":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			AddQuestRecord("DTSG", "11");
			pchar.questTemp.DTSG_AntiguaZalog = true;
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		
		case "DTSG_KnippelDolg_2":
			dialog.text = "赏金猎人? 追捕你的人? 你在说什么? ..";
			link.l1 = "别否认。 最好坦白, 我们像绅士一样解决。 但如果你装傻, 我就得用强硬手段对付你了。 ";
			link.l1.go = "DTSG_KnippelDolg_3";
		break;
		
		case "DTSG_KnippelDolg_3":
			dialog.text = "你... 你一定是弄错了! ..卫兵!! 他威胁要杀我! ";
			link.l1 = "哦, 真该死... ";
			link.l1.go = "DTSG_KnippelDolg_4";
		break;
		
		case "DTSG_KnippelDolg_4":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaStrazhBank_1", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false, "soldier"));
			GiveItem2Character(sld, "blade_10");
			EquipCharacterByItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterByItem(sld, "pistol1");
			ChangeCharacterAddressGroup(sld, "SentJons_bank", "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_AntiguaStrazhBank";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			LAi_SetHP(sld, 140+MOD_SKILL_ENEMY_RATE*10, 140+MOD_SKILL_ENEMY_RATE*10);
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		// <-- 旧日罪孽的漫长阴影
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 不要忘记卸载
}