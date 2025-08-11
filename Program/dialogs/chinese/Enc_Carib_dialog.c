void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "恭喜! 这是一个漏洞。 联系杰森并告诉他你是如何以及在哪里遇到这个漏洞的。 祝好! ";
			link.l1 = "我会立即这么做! ";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(1.00);
		break;
		
		// 武装印第安人 - 加勒比人
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase("向你致敬, 海洋之子! 我听说过你。 你可以在我们的土地上安心行走。 ", "" + npchar.name+ "向你问候, 白脸兄弟。 我们很高兴见到你这位客人。 ", "我问候你, 勇敢的白脸战士! " + npchar.name+ "很高兴见到印第安人的朋友。 平安前行! ");
				link.l1 = RandPhraseSimple("也向你致敬, 红皮肤的兄弟! 祝你狩猎顺利! ", "问候你, 勇敢的战士! 愿神灵保佑你和你的家人! ");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple("我有一些可能让你感兴趣的东西, 红皮肤的兄弟。 想交易吗? ", "我可以提供一些有趣的东西给你买, 勇敢的战士。 想交易吗? ");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("停下, 白脸! 你有什么权利在我的土地上行走? ", "停下, 白人! 你在我祖先的土地和我的土地上! ", "停下, 白脸! 你不属于我的土地");
				link.l1 = RandPhraseSimple("你的土地? 滚开, 你这红皮肤的混蛋! ", "看看他 - 会说话的猿猴! 现在滚开! ");
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple("我是和平而来, 红皮肤的战士。 我们不该无缘无故地战斗。 ", "我不是你和你土地的敌人, 战士。 我是和平而来。 ");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > hrand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple("我是来和你交易的, 不是来战斗的。 ", "我不与印第安人战斗。 我与他们交易。 ");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > hrand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple("你会为出生感到遗憾, 白脸狗... 我会挖出你的心在火上烤! ", "我会让你吃石头, 白脸狗! 我们会嘲笑你跪在地上求死, 白杂种! ");
			link.l1 = RandPhraseSimple("你还不能闭上你那臭嘴吗, 涂漆的稻草人? 我会把你赶回你来自的丛林! ", "你敢威胁我, 混蛋? ! 好吧, 现在你得爬回你刚下来的那棵树! ");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple("我听到你的声音是真诚的。 我们今天不向你亮出斧头。 平安前行, 白脸。 ", "白脸很少带来和平, 但我在你眼中看到你说的是实话。 现在走吧。 ");
			link.l1 = RandPhraseSimple("明智的决定, 战士。 祝你好运。 ", "我很高兴我们达成了共识, 战士。 ");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple("你在撒谎, 白脸杂种! 你来到这里是为了杀印第安人! 准备战斗吧, 白脸? ! ", "你杀印第安人。 白人的舌头是说谎的舌头。 我会把它割下来放在火上烤! ");
			link.l1 = RandPhraseSimple("好吧, 伙计, 那就别怪我了。 天知道, 我试过避免这样... ", "好吧, 这是你自找的, 战士。 ");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = "交易? 我们需要白人的武器。 白脸的一种火器! 用它我们可以交易我们的商品! 你有可以交易的火器吗? ";
				link.l1 = "嗯。 我有。 你会给我什么作为交换? ";
				link.l1.go = "war_indian_trade";
				link.l2 = "你这无赖! 然后你会用我的手枪射击殖民者吗? 不, 那不会发生! 至于你们这些豺狼, 我现在就把你们都砍倒... ";
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = "你没有我们想要的东西, 白脸... 你将成为我们的战利品! ";
				link.l1 = "如果你敢, 就试试... ";
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple("我们不与白脸狗交易。 我们杀人并夺取! ", "我们不是肮脏的米斯基托人或阿拉瓦克人, 我们不与白脸交易! 我们杀了他们并获得战利品! ");
			link.l1 = RandPhraseSimple("好吧, 那试试抢劫我吧, 无赖! ", "首先, 你需要从我这里夺走我的军刀, 你们这些垃圾! ");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = "你展示你有的东西, 我们会说我们为此给你什么。 ";
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "提供" + XI_ConvertString("pistol" + i) + "。 ";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (hrand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(1)+1;
				sText = "" + FindRussianQtyString(iTotalTemp) + " 瓶优质治疗药水";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(9)+14);
				iTotalTemp = hrand(2)+1;
				sText = "" + FindRussianQtyString(iTotalTemp) + " 颗这颗美丽的宝石";
			}
			dialog.text = "嘿嗬! 我们用" + sText + "来换它。 ";
			link.l1 = "成交! ";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "不。 没门。 ";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (hrand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(2)+2;
				sText = "" + FindRussianQtyString(iTotalTemp) + " 瓶优质治疗药水";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(3)+1);
				iTotalTemp = hrand(2)+2;
				sText = "" + FindRussianQtyString(iTotalTemp) + " 颗这颗美丽的宝石";
			}
			dialog.text = "嘿嗬! 狡猾的武器... 我们用" + sText + "来换它。 ";
			link.l1 = "成交! ";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "不。 没门。 ";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (hrand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = hrand(6)+qty*15;
				sText = "" + FindRussianQtyString(iTotalTemp) + " 颗这颗美丽的珍珠";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(2)+2);
				iTotalTemp = hrand(2)+5;
				sText = "" + FindRussianQtyString(iTotalTemp) + " 颗这颗美丽的宝石";
			}
			dialog.text = "嘿嗬! 强大的武器! 能杀死很多敌人! 我们用" + sText + "来换它。 ";
			link.l1 = "成交! ";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "不。 没门。 ";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+" 白人视若生命的金属块";
			}
			else
			{
				npchar.quest.item = "obereg_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "这个护身符";
			}
			dialog.text = "嘿嗬! 可怕的武器... 我们用"+sText+"来换它。 ";
			link.l1 = "成交! ";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "不, 没门。 ";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (hrand(7) < 7)
			{
				if (hrand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+hrand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = hrand(4)+10;
				}
				qty = hrand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = hrand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" 块美丽而珍贵的石化焦油";
			}
			else
			{
				npchar.quest.item = "indian_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "这个护身符";
			}
			dialog.text = "嘿嗬! 美丽而强大的武器! 能杀死很多敌人! 我们用"+sText+"来换它。 ";
			link.l1 = "成交! ";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No。 No way.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+" 白人视若生命的金属块";
			}
			else
			{
				npchar.quest.item = "amulet_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "这个护身符";
			}
			dialog.text = "嘿嗬! 实用的武器... 我们用"+sText+"来换它。 ";
			link.l1 = "成交! ";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "不, 没门。 ";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(1.00);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info("你已交出"+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info("你已收到"+XI_ConvertString(npchar.quest.item)+", 数量为"+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+hrand(2));
			{
				dialog.text = "好。 这是你的货物。 我们不再交易了。 以后再来。 更好的火器我们会给更多。 现在走吧! ";
				link.l1 = "再见, 红皮肤的战士。 ";
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = "很好。 这是你的货物。 你还有更多火器要交易吗? ";
				if (CheckCaribGuns())
				{
					link.l1 = "我有。 你要买吗? ";
					link.l1.go = "war_indian_trade";
				}
				link.l2 = "不。 下次我会带更多来。 ";
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = "带来吧。 更好的火器我们会给更多。 现在走吧! ";
			link.l1 = "再见, 战士... ";
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = "那么我们就免费拿走一切, 白脸! ";
				link.l1 = "你可以试试... ";
				link.l1.go = "exit_fight";
			}
		break;
		
		// 和平的印第安人 - 米斯基托人
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(" hail, 白人。 你在我们的丛林里需要什么? ","我们的丛林非常危险。 你在这里做什么? ","是什么把你带到这里来的, 勇敢的白脸? ");
			link.l1 = RandPhraseSimple("我只是路过, 我的红皮肤朋友。 我相信这条路上有足够的空间供我们两人通行? ","问候你, 丛林之子! 我是来这里办事的, 我不与印第安人作战。 ");
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple("你为什么需要知道? 走你自己的路, 远离麻烦! ","走你自己的路, 红皮肤的人。 我没有时间和你说话。 ");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple("我们是和平的人民。 我们不是白人的敌人。 走吧, 但在我们的土地上要小心! ","我很高兴见到印第安人的白脸朋友。 平安地走吧, 海洋之子! ");
			link.l1 = RandPhraseSimple("也祝你好运, 丛林之子... ","再见, 红皮肤的朋友。 ");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple("我们是和平的猎人。 但是当白脸在我们的土地上这样说话时, 我们不会容忍! ","我们不与白人作战, 但如果白人冒犯我们, 我们会按照我们祖先教导的方式回应! ");
			link.l1 = RandPhraseSimple("你还不能闭上你那臭嘴吗, 涂漆的稻草人? 我会把你赶回你来自的丛林! ","你敢威胁我,人渣? ! 现在你得爬回你刚下来的那棵树! ");
			link.l1.go = "exit_fight";
		break;
	}
}
