void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			int iMoney = makeint(makeint(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(LinkRandPhrase("听说了吗? 当地强盗" + GetFullName(npchar) + "找到了新目标。 有个船长被吓到了, 花钱消灾。 据说他给了" + FindRussianMoneyString(iMoney) + ", 嘿嘿... ", 
				"是啊, " +GetFullName(pchar)+ "船长, 我听说你不得不付" + FindRussianMoneyString(iMoney) + "给当地强盗" + GetFullName(npchar) + "。 这可真是倒霉! 哈哈哈! ", 
				"听说当地强盗袭击了一个船长吗? 他被彻底抢劫了, 损失了" + FindRussianMoneyString(iMoney) + "! "), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
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
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("听说了吗? 那个强盗" + GetFullName(npchar) + "终于得到了报应。 他和他的手下想抢劫" + GetSexPhrase("某个船长, 但结果发现他是","某个女船长, 但结果发现她是") + "个硬茬。 所以我们亲爱的强盗吓得屁滚尿流, 哈哈! 这对他是个教训! 抢劫当地农民是一回事, 但勇敢的船长是另一回事! ", 
				"感谢你, " +GetFullName(pchar)+ "船长, 终于解决了那个强盗" + GetFullName(npchar) + "的团伙。 那些无赖真是每个人的眼中钉。 我们甚至不敢派信使去农场取牛奶, 怕他们拦截抢钱。 "), 
				"听说了吗, " + GetSexPhrase("终于有个船长","终于有个女船长") + "阻止了那个在丛林里称王称霸。 恐吓当地农民的无赖" + GetFullName(npchar) + "。 我希望这能让他们长时间停止恶行... ", 
				"听说当地强盗" + GetFullName(npchar) + "和他的手下试图抢劫" + GetSexPhrase("某个船长","某个女船长") + "吗? 呸! 根本不是那么回事! 那个船长原来是个硬茬。 据说他像鲨鱼追沙丁鱼群一样在丛林里追着这些强盗跑。 谢天谢地, 当当局无所作为。 忙于阴暗勾当时, 还有人能为我们挺身而出... "), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("站在原地, 放下武器! 要钱还是要命! ",
				"站在原地, " + GetSexPhrase("旅行者","姑娘") + "! 别动武器, 别轻举妄动! ",
				"站在原地, " + GetSexPhrase("旅行者","姑娘") + "! 这是收费路段。 想过去就得付费。 "),
				LinkRandPhrase("嘿, " + GetSexPhrase("伙计","姑娘") + "! 别走那么快! 我想看看你的钱包有多鼓。 ",
				"朋友, 靠近点。 我想听听你钱包里金币的叮当声。 ",
				"等等, " + GetSexPhrase("伙计","姑娘") + "。 我和兄弟们打赌你的钱包能装多少金币。 现在我们得在事情变糟前检查一下。 "),
				"别着急, " + GetSexPhrase("旅行者","亲爱的") + "! 我们推心置腹地谈谈, 好吗? ");				
			Link.l1 = LinkRandPhrase(LinkRandPhrase("你说这些废话干什么? ","怎么了? ", "你在说什么? "), "你什么意思? ", "你到底什么意思? ");
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("强盗? ! 太好了, 我正想打架呢! ", 
				"哦, 你们是强盗! 躲着正义是吧? 看来正义刚刚来找你们了... ",
				"没人教过你打扰陌生人说废话是没礼貌的吗? 看来我得给你上这一课... "),
				LinkRandPhrase("哦, 你很无礼啊? ! 希望你的刀刃和你的舌头一样锋利。 ",
				"看来你很会耍嘴皮子, 希望你也很会用剑。 ",
				"哦, 强盗! 你们这种人绞死了很多, 但还是不停地走向绞刑架。 "),
				LinkRandPhrase(RandPhraseSimple("哦, 强盗! 知道吗, 我通常不跟你们这种人浪费口舌! ",
				"真是个无礼的家伙! 臭得像堆牛粪, 还敢跟体面的" + GetSexPhrase("男人","女人") + "说话。 "),
				"我不会跟你浪费口舌, 但我的手枪会很有说服力! ",
				"又是强盗! 好吧, 我不能保证让你上绞架, 但肯定能在你肚子上开几个洞! "));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase("你知道有巡逻队紧跟着我吗? 我只要吹个口哨, 你们就完了。 ", 
				RandPhraseSimple("你知道吗, 我可以叫巡逻队, 你不怕吗? 他们就在附近。 我猜是在找你们。 ", 
				"最近派出了一支巡逻队找你们, 他们随时会到。 你们在冒很大的风险。 "),
				RandPhraseSimple("我劝你尽快跑。 一支巡逻队正朝这边来, 我刚和他们的军官谈过。 ",
				"我很想继续我们的谈话, 但恐怕我刚遇到的巡逻队不会让我们的 acquaintance 发展成亲密友谊。 "));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase("别装傻了! 马上把钱交出来, 或许我会让你走! ",
				"没听说过过路钱吗? 不拿出金子, 就等着掉脑袋! ",
				"呵, 这次冒险会让你损失一个钱包... 如果我没生气的话。 "),
				RandPhraseSimple("很简单。 把所有的金子给我们, 然后你就可以走了, 否则你就留在这里, 我们照样拿走所有金子。 但我想你不会喜欢后者, 嘿嘿。 ",
				"别装不懂! 不想从尸体上拿钱包的话, 就把你的钱包给我! "),
				"如果你这么迟钝, 我就解释一下。 如果你珍惜生命, 就把所有的钱给我。 ");
			Link.l1 = "该死的, 混蛋! 我只有" + makeint(makeint(Pchar.money)/20)*10 + "比索。 ";
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("你想要我的钱? 自己来拿, 我倒要看看你有多大本事! ",
				"你怎么敢, 粗人! 我会教你懂礼貌! ",
				"真是自信! 那就看看你怎么对付真正的" + GetSexPhrase("海狼","海之母") + "! "),
				LinkRandPhrase("你这种无礼的行为应该被鞭打! ",
				"你们这些无赖! 向你们的魔鬼祈祷在地狱有个温暖的地方吧! ",
				"你们早该被绞死了, 吊死鬼! 看来我得用我的剑沾上你们的血了! "),
				RandPhraseSimple("你凭什么认为我会把钱给你? ",
				"你没注意到我装备精良, 来这里不是简单散步的吗? "));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 90;  
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("该死! 好吧, 你可以走。 但在这里别出声! ", 
					"这次你运气好, 但下次你得付双倍! 别忘了提醒我们, 嘿嘿。 ");
				Link.l1 = RandPhraseSimple("当然。 ", "趁你还能走, 赶紧跑吧。 ");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk = makeint(pchar.reputation.nobility) < 51 && makeint(pchar.reputation.nobility) > 41; // Captain Beltrop, 23.01.21 - 恶意!!! 只需要去掉个位数!
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("我们会安静地杀了你, 你连一声尖叫都发不出来。 ", 
						"该死! 我们得在你发出警报前快点杀了你。 ");
					Link.l1 = "好吧, 这是你自找的。 我警告过你。 ";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("我为什么要在乎你的巡逻队? 我在给他们付钱。 所以, 把你的钱包给我, 别再废话了。 ", 
						"你以为你能吓到我? 在这片丛林里, 我就是你们这种人的'巡逻队'。 还没人能不付费就离开! ");
					Link.l1 = "该死的, 混蛋! 我只有" + makeint(makeint(Pchar.money)/20)*10 + "比索。 ";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase("嘿嘿, 我不会听从你这种懦夫的命令。 ", 
						"我会在你脑袋上开几个新洞, 让你的脑子透透气。 ",
						"这种无礼的行为不会不受到惩罚! "),
						"你不该那么做的... ");
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
			bool isStrong = (GetCharacterSkillToOld(Pchar, "FencingL") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 7);
			bool z_ok = (isStrong) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation.nobility) <= 30); // Captain Beltrop & mitrokosta, 23.01.21 检查武器 (新变体)
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("嘿, 别这么激动, " + GetSexPhrase("伙计","姑娘") + "! 我只是开玩笑! 你可以继续走你的路! ",
					"好吧, 我改变主意了。 你这么厉害, 就走吧。 "),
					"什么, 又是个" + GetSexPhrase("'英勇船长'","'好斗姑娘'") + "? 好吧, 平安走吧... ",
					"放松点, " + GetSexPhrase("伙计","姑娘") + "。 你看, 我们搞错了, " + GetSexPhrase("我们以为你是商人","我们以为你是商人") + "。 你可以走了。 ");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("好吧, 后会有期! ",
					"你应该趁还能走的时候, 别再抢劫别人了。 ",
					"好吧, 但如果我再见到你... "),
					RandPhraseSimple("下次注意你威胁的是谁, 杂种。 ",
					"谢天谢地, 我今天心情好。 "),	
					RandPhraseSimple("这种犯罪勾当最终肯定会害死你。 再见。 ",
					"这是个明智的决定。 好吧, 祝你好运! "));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("不, 伙计。 现在我要教你懂礼貌! ",
					"哦, 害怕了? 好吧, 一个人应该为自己的行为付出代价, 对吧? ",
					"不! 在把你活剥了之前, 我是不会冷静的! ");
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase("你本可以平安离开的! 现在只能怪你自己! ",
								"你不该先挑事的, 无赖! 现在你要像狗一样死去! ",
								"啊! 我要把你撕成碎片! 挖出你的肝喂狗! ");
				Link.l1 = RandPhraseSimple("我会把你的话塞回你喉咙里! ","你在威胁谁, 人渣? ! ");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(makeint(makeint(Pchar.money)/20)*10 >= makeint(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("好吧! 给我钱, 然后滚! ",
					"不多, 但总比没有好。 和聪明人打交道真好! 你可以走了。 "),
					"现在这就对了! 就像我一个朋友说的'听聪明人的话总是好的, 但和傻瓜说话更好'! 嘿嘿! ",
					"用你的金子换我给你一个建议, 你不该在丛林里走, 如果你是" + GetSexPhrase("这样的懦夫。 在酒馆喝你的朗姆酒, 这样你和你的钱包都安全! ","个姑娘。 被抢劫还不是可能发生在你身上最糟糕的事。 ") + "。 ");
				Link.l1 = "该死的你! ";
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = "我猜你想骗我! 别担心, 我会用刀子挠挠你, 也许会掉些东西下来。 ";
				Link.l1 = "该死的! ";
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("又是你? 在我生气前滚回家找你妈妈去! ",
				"什么? 你还没把所有金子给我? 哈哈! ",
				"听着, " + GetSexPhrase("伙计","姑娘") + ", 我受够你了! 趁你还活着, 滚出我的视线! ");
			Link.l1 = "是的, 我这就走。 ";
			Link.l1.go = "Exit";
			Link.l2 = "我觉得这不公平。 所以我决定把事情弄清楚... ";
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("你还需要什么? 我们已经说好你要离开了! ",
				"别烦我了, " + GetSexPhrase("伙计","姑娘") + "。 我管我的事, 你管你的事, 我们不该合得来! ",
				"现在就走, " + GetSexPhrase("伙计","姑娘") + "! 该死的, 你真的想把所有钱都给我吗? ");
			Link.l1 = "是的, 我这就走。 ";
			Link.l1.go = "Exit";
			Link.l2 = "我想起你还没道别! 所以让我们好好道别一下... ";
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("别烦我! 救命! 我想活下去! ",
				"救命! " + GetSexPhrase("他是个疯子","她是个疯子") + "! 别杀我! ",
				"饶了我吧! 我只是个卑微的强盗! 我还年轻, 不想死! ");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("如果你待在家里, 就能活下去! ",
				"你之前就该想到的! ",
				"你早该知道总会有后果的! "),
				"迟早会发生的。 ",
				"后悔太晚了, 现在战斗吧人渣! ");
			Link.l1.go = "exit_Fight";			
		break; 				
	}
}