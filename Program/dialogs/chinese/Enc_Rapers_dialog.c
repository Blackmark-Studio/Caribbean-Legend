void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;
		
		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase("走吧, " + GetSexPhrase("伙计","姑娘") + "。 她最终会感谢我们的, 你知道的。 ",
											 "滚开! 让先生们找点乐子。 ",
											 "这不关你的事, " + GetSexPhrase("陌生人","姑娘") + "。 我们只是找点乐子, 就这样! ");
				link.l1 = LinkRandPhrase("我不允许这样! ","立即放弃你们的邪恶计划! ","我不容忍任何暴力行为! ");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("我知道了, 这就走。 抱歉打扰。 ","我不敢再打扰你们了。 抱歉打扰。 ");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
					dialog.text = LinkRandPhrase("走吧, " + GetSexPhrase("伙计","姑娘") + "。 她最终会感谢我们的, 你知道的。 ",
											 "滚开! 让先生们找点乐子。 ",
											 "这不关你的事, " + GetSexPhrase("陌生人","姑娘") + "。 我们只是找点乐子, 就这样!! ");
					link.l1 = LinkRandPhrase("我不允许这样! ","立即放弃你们的邪恶计划! ","我不容忍任何暴力行为! ");
					link.l1.go = "Node_Fight";
					link.l2 = RandPhraseSimple("我知道了, 这就走。 抱歉打扰。 ","我不敢再打扰你们了。 抱歉打扰。 ");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple("嘿, " + GetSexPhrase("陌生人","年轻女士") + ", 你为什么要自找麻烦? 这个女孩在我们定居点是个'名人'。 我们已经付了钱, 但她看到你后决定带着我们的钱逃跑。 ",
												   "嘿, " + GetSexPhrase("伙计","姑娘") + ", 走你自己的路, 别干涉我们的事。 我们在掷骰子游戏中赢了这个女孩, 但她动作太快跑了, 我们在丛林里追了她一个小时。 ");
					link.l1 = "我不在乎, 我不会让你们伤害她! ";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("哦, 我明白了! 我差点就相信她了! 真是个荡妇... ","啊, 好吧, 那就是另一回事了。 好吧, 伙计们玩得开心! ");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{	
					dialog.text = "走吧, " + GetSexPhrase("好人","年轻女士") + "。 没有你我们也能解决。 ";
					link.l1 = "我不容忍任何暴力行为! ";
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple("嘿, " + GetSexPhrase("陌生人","年轻女士") + ", 你为什么要自找麻烦? 这个女孩在我们定居点是个'名人'。 我们已经付了钱, 但她看到你后决定带着我们的钱逃跑。 ",
												   "嘿, " + GetSexPhrase("伙计","姑娘") + ", 走你自己的路, 别干涉我们的事。 我们在掷骰子游戏中赢了这个女孩, 但她动作太快跑了, 我们追了她一个小时。 ");
					link.l1 = "我不在乎 - 我不会让你们伤害她! ";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("哦, 我明白了! 我差点就相信她了! 真是个荡妇... ","啊, 好吧, 那就是另一回事了。 好吧, 伙计们玩得开心! ");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = RandPhraseSimple("" + GetSexPhrase("好吧, 你确实选对了散步的时间... ","所以, 你决定当英雄了? ") + " 对付他" + GetSexPhrase("们","她") + ", 伙计们! ","你这" + GetSexPhrase("卑鄙小人","败类") + "! 你敢挡我们的路? ! 砍了他" + GetSexPhrase("们","她") + "! ");
			link.l1 = "我见过更有威胁的人! ";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = "你应该知道她花了我们不少钱! 如果你这么高尚, 可以用" + sti(pchar.GenQuest.EncGirl.price) + "比索带走她。 " + GetSexPhrase(" 你会和她玩得很开心的, 嘿嘿... ","") + "";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple("给你钱。 我带她走。 ","别咧嘴笑了。 我要带这个女孩走。 给你钱。 ");
				link.l1.go = "Node_4";
			}	
			link.l2 = LinkRandPhrase("所以, 你想要钱? 冷钢怎么样? ",
									"这应该很有趣吧, 你这个傻瓜! 看看这个女孩, 她吓坏了! ",
									"你想骗谁呢, 你这个堕落的家伙! ");
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": // 强盗离开, 女孩留下 - 主角从强盗手中赎回了她
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price))); 
			ChangeCharacterComplexReputation(pchar,"nobility", 7);
			//pchar.quest.LandEnc_RapersBadExit.over = "yes";
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = "你为什么首先相信她? 什么暴力? 她离家出走了, 我们是被老板派来找她的。 ";
			link.l1 = RandPhraseSimple("好吧, 那就是另一回事了。 去吧, 追你们的逃犯。 ","哦, 我明白了。 那继续追她吧... 我还有事要做。 ");
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple("把这些童话故事讲给你孙子听吧, 如果你能活到有孙子的话! ","你想骗谁呢, 你这个混蛋? ! ");
			link.l2.go = "Node_6";
			link.l3 = "我会自己带她回家, 避免发生不好的事。 她父母是谁? ";
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = "想找死? 这是你的选择... ";
			link.l1 = "看看谁在说话。 ";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = hrand(2);
			else	i = hrand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = "是个店主";
					pchar.GenQuest.EncGirl.FatherGen = "店主的";
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = "在港务局工作";
					pchar.GenQuest.EncGirl.FatherGen = "在港务局工作的";
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = "担任监狱长";
					pchar.GenQuest.EncGirl.FatherGen = "监狱长的";
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = "是造船厂老板";
					pchar.GenQuest.EncGirl.FatherGen = "造船厂老板的";
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dialog.text = "她的父亲" + pchar.GenQuest.EncGirl.FatherNom + ", 在" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "定居点。 但请不要让我们失望, 因为他不是好惹的, 他会把我们都活剥了... ";
			link.l1 = "别担心。 我会把她交给他。 ";
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = "所以我们又见面了。 你的同伴呢? 哦, 好吧, 实际上如果你在这里, 我不需要她。 ";
			link.l1 = "先生们, 我真的认为你们已经收到足够的钱, 可以放过这个女孩了。 ";
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(hrand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(hrand(4))
			{
				case 0:
					sTemp = "一条腿";
				break;
				case 1:
					sTemp = "一只胳膊";
				break;
				case 2:
					sTemp = "一只耳朵";
				break;
				case 3:
					sTemp = "一个鼻子";
				break;
				case 4:
					sTemp = "一只眼睛";
				break;
			}
			dialog.text = "你的钱与" + GetName(pchar.GenQuest.EncGirl.PirateIdx , pchar.GenQuest.EncGirl.PirateName1, NAME_GEN) + "的宝藏相比算什么? " +
						   "他太贪婪了, 甚至不想娶自己的女儿, 因为想避免额外的开销... \n但他的箱子里有我们的份额! " + 
						   GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.PirateName2, NAME_NOM) + "在登船时失去了" + sTemp + "! 我们得到了什么? " + 
						   "可怜的一把银子? " + GetName(pchar.GenQuest.EncGirl.PirateIdx , pchar.GenQuest.EncGirl.PirateName1, NAME_NOM) + "总是把所有战利品都藏起来。 但现在我们不会放弃! 告诉我们他的箱子在哪里! ";
			link.l1 = "好吧, 我当然没有申请守护你们船长的宝藏, 但我不能告诉你们地点... 因为我不知道那个地方在哪里。 ";
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = "你在撒谎! 我能闻到从这个山洞里传来的金子的味道! 如果你不想死, 就告诉我们地点! ";
			link.l1 = "我看我的话没能说服你。 也许我的刀刃会更有说服力? ";
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = "你这" + GetSexPhrase("杂种","败类") + "! 给我让开! ";
			link.l1 = "啊! ";
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = "你好, " + GetSexPhrase("先生","女士") + "。 我们有关于你的投诉。 ";
			link.l1 = "谁的投诉? 那个妓女? ";
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = "注意你的言辞, 好吗? 我不允许你侮辱我妹妹! 首先你在丛林里骚扰她, 然后带她来这里" + GetSexPhrase("进行更多下流行为","并抢劫了我") + "。 ";
			link.l1 = "嘿, 伙计, 我真的必须听这些吗? ";
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = "不。 只需支付" + sti(pchar.GenQuest.EncGirl.BerglarSum) + "比索的 modest 金额, 就可以帮你摆脱所有麻烦。 ";
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = "好吧, 如今高尚的行为确实有点昂贵。 好吧, 拿去吧... ";
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = "我想在你肚子上开个洞会更便宜, 这样你就不会挡着我出去的路了。 ";
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = "不。 但你也要把口袋翻出来, 否则我就捅你! ";
				link.l1 = "好吧, 拿去吧, 你这个混蛋! 但你不会得逞的... ";
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = "我想在你肚子上开个洞会更容易, 这样你就不会挡着我出去的路了。 ";
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = "很好。 滚吧。 ";
			link.l1 = "祝你好运。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = "当然我不会, 当然... 好吧, 再见, " + GetSexPhrase("伙计","姑娘") + "。 " + GetSexPhrase(" 记住, 你没那么帅, 不会有女孩一见到你就爱上你。 这算是我给你的教训。 ","") + "";
			link.l1 = "" + GetSexPhrase("那是肯定的! ..","快滚吧! ") + "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = "你看起来像" + GetSexPhrase("这么高尚的人","这么有教养的女士") + ", 为什么说脏话? ";
			link.l1 = "这最适合我... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = "好吧, 这是你自找的! 伙计们, 我们该用钢刀挠挠他" + GetSexPhrase("们","她") + "吗? ";
			Link.l1 = "死前祈祷吧! ";
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = "那么, 你想加入还是怎样? " + GetSexPhrase("滚开, 不够我们分的","趁你还能走的时候滚开, 我们有一个姑娘就够了") + "! ";
			Link.l1 = "好吧, 那我就不打扰你们了。 ";
			Link.l1.go = "Exit_NoFight";
			Link.l2 = "我不允许任何暴力行为发生! ";
			Link.l2.go = "Node_2";
		break;				
	}
}