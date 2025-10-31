void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("船长","女士") +"! 求您发发慈悲! 保护我, 我求求您! ","救命! "+ GetSexPhrase("陌生人","年轻女士") +", 救救我, 我求求您! ");
			link.l1 = LinkRandPhrase("发生了什么事? ","怎么了? ",RandPhraseSimple("有什么麻烦? ","发生了什么? "));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("船长! 船长","姑娘! 姑娘") +", 请等一下! ","等一下, "+ GetSexPhrase("船长","年轻女士") +"! 求您了。 ");
			link.l1 = LinkRandPhrase("发生了什么事? ","怎么了? ",RandPhraseSimple("有什么麻烦? ","发生了什么? "));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "哦, " + GetSexPhrase("先生","女士") + "! 求您帮帮可怜的姑娘吧, 我求求您! 那些人想对我做可怕的事! ";
			link.l1 = LinkRandPhrase("发生了什么事? ","怎么了? ",RandPhraseSimple("有什么麻烦? ","发生了什么? "));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple("这些恶棍要强奸我! 看在上帝的份上, 别让他们得逞! ","看在上帝的份上, 保护我免受这些怪物的伤害! 他们要玷污我的名誉! ");
			link.l1 = "别惊慌" + GetSexPhrase(", 美人","") + "。 这里发生了什么? ";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("强奸犯在追我! " + GetSexPhrase("你会维护一位女士的名誉吗? ","") + "","船长, " + GetSexPhrase("像个男人一样","你也是女人") + "你难道不会把一个女孩从耻辱中拯救出来吗! ");
			link.l1 = "别惊慌" + GetSexPhrase(", 美人","") + "。 这里发生了什么? ";
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = "他们在追我! 那些强盗! 叫他们离我远点! ";
			link.l1 = "别惊慌" + GetSexPhrase(", 美人","") + "。 这里发生了什么? ";
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("救命! 救命! 他们在追我! 救救我! ",
				"啊! 救命, " + GetSexPhrase("陌生人","年轻女士") + "! 把我从这些恶棍手中救出来! ",
				"请发慈悲, 保护我免受这些恶棍的伤害! 求您了! ");
			Link.l1 = LinkRandPhrase("发生了什么事? ", "怎么了? ", "发生了什么? ");
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase("他们...他们要强奸我! 看在上帝的份上, 别让他们得逞! 求您了! ",
				"这些野兽...他们在策划可怕的事情...请保护我免受他们的伤害, 求您了! ",
				"以上帝的名义, 把我从这些好色的野兽手中救出来! 他们想玷污我的名誉! ");
			Link.l1 = "那我们来弄清楚这一切吧。 ";
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("谢谢你, " + GetSexPhrase("船长","年轻女士") + "。 我刚才太害怕了! ","谢谢你救了我! 我太感激你了! ");
					link.l1 = "好了, " + GetSexPhrase("美人","亲爱的") + ", 冷静点, 都过去了。 ";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "哦, 谢谢你, " + GetSexPhrase("高贵的先生! 你真是个绅士! ","女士! 你救了我! ") + "";
					link.l1 = "我不能坐视不管。 ";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "哦, 谢谢你, " + GetSexPhrase("高贵的先生! 你真是个绅士! ","陌生人! 你救了我! ") + "";
					link.l1 = "我不能坐视不管。 ";
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = "你做了什么? 你为什么杀了他们? ! 现在他们会来找我的! 我的上帝, 我做了什么才配得上这个! ";
					link.l1 = "这就是感恩吗! ";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "你做了什么, " + GetSexPhrase("船长","年轻女士") + "? ! 你为什么杀了他们? 他们实际上是我父亲派来的...哦, 天哪, 现在他肯定会杀了我...";
				link.l1 = "这真是新闻! 那你哭着说被强盗追, 你是怎么想的? ! ";
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "我有些钱, 请收下作为我感激的象征。 我现在就告诉大家, " + GetSexPhrase("你是多么善良高贵的先生","你是多么善良高贵的女士") + "。 ";
			link.l1 = "你肯定会的。 谢谢...现在回家吧。 ";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = "我还是无法平静下来。 你能把" + GetSexPhrase("一位女士","我") + "带到" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "的定居点吗? 你知道, 现在每个灌木丛后面我都觉得有强奸犯。 ";
			link.l1 = RandPhraseSimple("别这么担心, 真的...好吧, 我们走吧。 ","你真是个胆小鬼, 不是吗? 好吧, 我带你去。 ");
			link.l1.go = "Node_121Next";
			link.l2 = "对不起, 亲爱的, 但我实在没时间, 我太忙了。 ";
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = "我以为你只会把他们吓跑! 现在你必须带我去" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "定居点的酒馆, 我除了你没有其他人可以求助了。 ";
			link.l1 = "哦, 该死! 好吧, 我们走。 别落后。 ";
			link.l1.go = "Node_122Next";
			link.l2 = "不, 就这样吧, " + GetSexPhrase("美人","亲爱的") + "! 我今天受够了惊喜。 找别人帮你吧。 ";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = "我该怎么办? 我父亲想让我嫁给放贷人的儿子, 那个懦夫...就因为他爸爸的金库里有一大笔钱! 但我爱上了另一个男人! 请带我去找他...";
			link.l1 = "你真是个负担! 好吧, 好吧, 我们走。 我现在不能把你留在这里, 不是吗? ...你选中的人叫什么名字, 我该带你去哪里? ";
			link.l1.go = "Node_32";
			link.l2 = "不, 就这样吧, " + GetSexPhrase("美人","亲爱的") + "! 我今天受够了惊喜。 找别人帮你吧。 ";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "他的名字是" + pchar.GenQuest.EncGirl.sLoverId + ", 他是个新来的。 现在他住在" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "的定居点, 想在那里找份工作, 但现在是困难时期。 每个人都在谈论危机...反正我现在也回不了家了。 ";
			link.l1 = "危机? 哈...对一个真正的海盗来说, 危机是当地平线有一支贸易商队, 却没有风扬起帆...";
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("你知道吗, " + GetSexPhrase("船长","年轻女士") + "? 我太害怕了, 甚至腿还有点发抖。 ","哦, 你知道吗, 我太害怕了。 上帝派你到我身边真是太好了。 ");
			link.l1 = RandPhraseSimple("谢天谢地你还活着。 ","别往心里去。 你知道, 这样结束很好。 ");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple("谢谢你, " + GetSexPhrase("船长","年轻女士") + ", 再次感谢。 真的, 我非常感激你。 ","非常感谢你, " + GetSexPhrase("船长","年轻女士") + "。 我不知道没有你的帮助我会怎么做。 ");
			link.l1 = RandPhraseSimple("这应该给你一个教训。 好了, 祝你好运...","下次你应该更小心...现在, 回家吧, 我还有事要做。 ");
			link.l1.go = "Node_1End";
			link.l2 = "你怎么能这么粗心? 你为什么一个人进丛林? ";
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("你改变主意了? ","船长, 你改变主意了, 真是太好了! ");
			link.l1 = RandPhraseSimple("不, 不, 亲爱的, 我放弃。 ","别抱幻想...");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "你可能会笑我, 但是...我在收集爱情药水...一个女巫告诉我这里有一种根可以帮助爱情。 ";
						link.l1 = "哦, 我的上帝! 这" + GetSexPhrase("些女人在想什么","你在想什么") + "? ! 显然, 你收集了很多, 有相当多的追求者在追你, 我费了很大劲才把他们都打败。 哈哈哈...再见。 ";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "我只是出去散步, 采些草药, 呼吸点新鲜空气。 显然, 这不是散步的最佳时间。 ";
						link.l1 = "多么粗心啊? ! 谢天谢地我及时出现了。 好吧, 祝你好运。 ";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "我的女主人在散步时把项链上的珍珠掉在这里了, 当她回家时, 她对我大喊大叫, 命令我出去把它们捡起来。 她说,'不把它们都捡起来就别回来!', 而我甚至不知道确切的地方。 此外, 我该如何在这片茂密的草丛中找到它们呢? 珍珠太小了...所以, 我只是在这里漫无目的地徘徊, 不知道该怎么办...";
					link.l1 = "那是一条什么样的项链? 也许干脆买一条新的比在丛林里徘徊更容易? 你的女主人丢了多少颗珍珠? ";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "我已故的父亲给我留了一张地图, 他的同伴们想从我这里拿走它。 当他还活着的时候, 他们都在他面前吓得发抖, 但我一埋葬他, 麻烦的时期就开始了。 起初他们试图向我买这张地图, 但我拒绝了, 于是他们开始恐吓我。 ";
					link.l1 = "那你为什么不卖掉它呢? 这张地图有什么特别之处, 让海盗团伙都在寻找它? ";
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "那条项链是由精选的珍珠组成的, 那些珍珠不便宜。 有" + sti(pchar.GenQuest.EncGirl.BigCoins) + "颗大珍珠和" + sti(pchar.GenQuest.EncGirl.SmallCoins) + "颗小珍珠。 如果找到这些珍珠, 我们可以委托再做一条那样的项链。 ";
			link.l1 = "这肯定不是一件容易的工作...好吧, 如果你的女主人给了你命令, 那你也没什么办法。 试着找到珍珠吧。 祝你好运。 ";
			link.l1.go = "Node_131End";
			link.l2 = "这是没有意义的。 在这片茂密的草丛中找珍珠比在干草堆里找针还难。 更不用说你甚至不知道珍珠丢失的地方...";
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = "我父亲在上面标记了他藏宝的地方。 你听说过著名的海盗" + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_VOC) + "吗? ";
			link.l1 = "不, 从没听说过他。 ";
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = "嗯, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_NOM) + "是我父亲。 每个人都害怕他, 没人敢说一句话。 现在他们当然变得厚颜无耻了。 当我拒绝把地图卖给他们时, 他们声称他们也必须分得一份宝藏。 我想把地图藏起来, 但他们还是找到了我...";
			link.l1 = "那你一开始为什么要藏起来呢? 租一艘船去, 索要你的宝藏。 你父亲不会无缘无故藏起来的。 ";
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = "说起来容易做起来难。 我没有钱租船, 而且...我害怕...我该如何把它全部挖出来, 搬到船上...之后我又该把宝藏带到哪里去呢? 一路上任何人都会轻易地成为我的猎物...";
			link.l1 = "有道理...好吧, 那就去藏你的地图吧。 记住把它放好。 ";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "嗯...这可能是真的。 更重要的是, 你应该把它卖掉。 ";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "你试过找同伴吗? ";
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = "失去这样的机会让我很伤心...爸爸告诉我他藏在那里的宝藏。 没有人会给我那么多钱...";
			link.l1 = "好吧, 别卖得太便宜。 而且, 无论如何, 黄金不值得你付出生命。 更不用说这对你来说是最简单的方式, 你只要拿到钱, 摆脱所有麻烦...";
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "这听起来很诱人...你能出多少钱买它? ";
			link.l1 = "我认为它的价值不超过" + sti(pchar.GenQuest.EncGirl.mapPrice) + "比索。 ";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "呵呵, 做女人不容易...好吧, 我同意。 这场噩梦终于要结束了...也许这张地图属于你, " + GetSexPhrase("一位高贵的绅士","") + ", 比属于那些无赖要好。 ";
				link.l1 = "好的。 这是你的钱...尽量不要一次花光。 ";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "不, " + GetSexPhrase("船长","年轻女士") + "。 我不会卖的。 我会嫁给一个好男人, 然后我们一起去索要宝藏。 ";
				link.l1 = "好吧, 这由你决定。 反正你的这张纸也不值更多钱。 ";
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			ref rMap = ItemsFromID("map_full"); // mitrokosta 修复空地图
			FillMapForTreasure(rMap, "");
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = "我在哪里能找到他们? 年轻人不可靠, 他们不太关心宝藏, 更关心其他事情。 而我害怕年长的人, 他们都让我想起我爸爸的伙伴。 如此狡猾和背信弃义, 你永远不知道会从他们那里得到什么。 ";
			link.l1 = "哈哈哈...好吧, 但你会带我一起去吗? ";
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = "你? 你会去吗? 但你必须把我带回这里, 到" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "的定居点, 好吗? ";
			link.l1 = "好的, 我向你保证。 只要给我指路。 ";
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "宝藏藏在" + XI_ConvertString(pchar.GenQuest.EncGirl.islandId + "Acc") + "的山洞里, 我们需要在" + XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen") + "登陆, 我会自己指给你看那个地方...但别忘了, 你只能得到一半! ";
			link.l1 = "好吧, 我不会骗你, 我保证。 跟着我, 别落后。 ";
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = "船长, 现在我们必须找到山洞。 ";
			link.l1 = "好吧, 我们现在看看。 ";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "船长, 我们必须找到山洞。 ";
			link.l1 = "好吧, 我们现在看看。 ";
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = "这里! 我找到了! 就像我父亲说的! 一大堆宝藏! 按约定, 一半是你的。 ";
			link.l1 = "看到了吗? 这并不难, 所以没什么好害怕的。 ";
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = "哈哈哈! 我现在有钱了! 你现在要拿你的那份吗? ";
			link.l1 = "我想是的。 ";
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = "那就拿着吧, 请帮我把这些东西都搬到船上。 你还记得你答应过要带我回家吗? ";
			link.l1 = "我没忘! 当然, 我会带你去。 ";
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes";// 护林员 。 取消了中断 , 如果不是从那个海湾进来的。 		
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("你已经收到了你的那份宝藏");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 2+hrand(6));
			TakeNItems(pchar, "jewelry1", 30+hrand(15));
			TakeNItems(pchar, "jewelry2", 30+hrand(15));
			TakeNItems(pchar, "jewelry3", 30+hrand(15));
			TakeNItems(pchar, "jewelry4", 30+hrand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			pchar.quest.EncGirl_AddPassenger.win_condition.l1 = "location";// 护林员到船上的女孩。 
			pchar.quest.EncGirl_AddPassenger.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.EncGirl_AddPassenger.function = "EncGirl_AddPassenger";
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "有钱真是太好了! 我现在感觉完全不同了。 "; 
			link.l1 = "我为你高兴。 ";
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = "好了, 船长。 我的旅程现在结束了。 感谢你的帮助。 ";
			link.l1 = "不客气...那么, 你打算如何处理你新获得的财富? 买一个有奴隶的种植园? ";
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = "我不知道, 我还没决定。 也许我会搬到欧洲...";
			link.l1 = "好吧, 那么! 祝你好运。 ";
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = "等一下...这个小饰品在我父亲的宝藏里。 我用不上它, 但你可能会喜欢它。 请接受它作为我个人对你为我所做一切的感激之情。 这是我那份里的, 哈哈哈! ";
			link.l1 = "哇, 这真是个不错的礼物。 谢谢你" + GetSexPhrase(",美人","") + "。 给自己找个好新郎, 好吗...";
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
            LAi_SetActorType(npchar); // 发送恢复以便不站立。 护林员。 
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
            pchar.quest.EncGirl_EnterToSea.over = "yes";// 护林员 。 取消了中断 , 如果不是从那个海湾进来的。 	
            PChar.quest.EncGirl_DialogAtShore.over = "yes";// 护林员 。 取消了中断 , 如果不是从那个海湾进来的。 						
		break;
		
		case "Node_133":
			dialog.text = "但我能做什么呢? 我不能忽视女主人的命令, 她会活剥了我的皮。 ";
			link.l1 = "在" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "定居点的教堂等我, 我会给你带珍珠来做一条新项链。 ";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "给你。 拿这15000比索。 这应该足够挑选项链的珍珠了, 或者买一条新的。 ";
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// 护林员 - 女孩逃跑如果玩家说在教堂等
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);			
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("船长","年轻女士") +", 很高兴再次见到你! 你设法为项链收集珍珠了吗? ","你好, 船长! 你给我带珍珠了吗? 你知道, 我的女主人越来越紧张了...");
			if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "是的。 这是你的珍珠。 拿给你的女主人, 告诉她下次小心点。 ";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "还没有。 你知道, 这并不容易...但我会带来的, 你等着。 ";
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "哦, " + GetSexPhrase("船长","年轻女士") + ", 很高兴遇到你! 作为对你为我所做一切的感激之情的象征, 我想给你这个小饰品和这些宝石。 我希望你会觉得它们有用。 ";
			link.l1 = "哇! 好吧, 也谢谢你" + GetSexPhrase(",美人","") + ", 我没想到...再见, 祝你幸福。 ";
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "哦, " + GetSexPhrase("船长","年轻女士") + ", 我就指望你了。 ";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+hrand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = "哦, " + GetSexPhrase("船长","年轻女士") + ", 你今天第二次帮了我。 非常感谢你。 我永远不会忘记你的好意。 ";
			link.l1 = "不客气。 向你的女主人问好...";
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("你不应该给他们任何钱。 他们在撒谎。 ","别相信他们。 他们是骗子。 你不应该给他们任何钱。 ");
					link.l1 = "我该杀了他们吗? ";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "哦, 多么高尚的行为! 我一眼就看出你是" + GetSexPhrase("一位真正的绅士","一位高贵的女士") + "! 请接受我最诚挚的感谢。 我希望你没有相信这些无赖的话? ";
					link.l1 = "那不重要。 一个女孩和一群流氓在丛林里, 这很正常...";
					link.l1.go = "Node_210";
					link.l2 = "你在说什么, " + GetSexPhrase("美人","亲爱的") + "? 我怎么会? ";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "谢谢你, 船长。 很抱歉让你卷入这件不愉快的事情, 但我实在别无选择。 ";
					link.l1 = "好吧, 我看你也很困难。 这是怎么发生的? ";
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "也许...他们现在永远不会放过我了。 ";
				link.l1 = "哦, 得了吧! 回家吧, 你现在没什么好怕的了。 ";
				link.l1.go = "Node_200End";
				link.l2 = "哇! 你为什么这么讨厌男人? ";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "当然不! 但他们无论如何都不会放过我。 你能把我带到" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "的定居点吗? ";
				link.l1 = "回家吧, 他们不会碰你的。 他们现在应该去酒馆挥霍他们的不义之财了。 ";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("别这么担心, 真的...好吧, 我们走吧。 ","你真是个胆小鬼, 不是吗? 好吧, 我带你去..");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = "哦不, 你在说什么? 我太了解这些恶棍了。 他们是我父亲以前的伙伴。 他们试图找到他藏宝的地方。 ";
			link.l1 = "那你父亲是做什么的? ";
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = "他曾经是一艘海盗船的船长。 最近他去世了...他们在葬礼上都很有礼貌, 但随着时间的推移, 他们忘记了他, 不久之后他们的荣誉和诚实也消失了。 幸好我注意到了他们。 一旦他们知道宝藏在哪里, 我就完了。 ";
			link.l1 = "这是一个悲伤的故事。 那么, 你打算继续躲避他们吗? ";
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = "我不能把珠宝放在家里, 我没有人保护我。 所以当钱用完的时候, 我晚上就去山洞...\n请带我去山洞, 我会把你给他们的钱还给你...我想, 有你在, 海盗们不敢跟着我们。 ";
			link.l1 = "对不起, 亲爱的, 但我有不同的计划。 你可以下次再去收集你的宝藏。 ";
			link.l1.go = "Node_200End";
			link.l2 = "好吧, 我们走, 如果你不怕我的话。 ";
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = "你知道, 不知为什么, 我不...";
			link.l1 = "嗯, 那是件好事。 ";
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "船长, 你答应过带我去山洞的。 ";
			link.l1 = "我们走吧...";
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = "好了, 船长, 我已经拿了我需要的东西。 我们现在可以回去了。 ";
			link.l1 = "我看你的伙伴不在附近。 ";
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = "谢天谢地。 我不需要更多的麻烦了...给, 拿这些锭子...应该足够支付你的费用了。 你自己走吧, 我走另一条路...";
			link.l1 = "好吧, 祝你好运, 如果你不害怕的话。 ";
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "嗯, " + GetSexPhrase("船长","年轻女士") + ", 我不喜欢你的讽刺。 ";
			link.l1 = "你可以走了, " + GetSexPhrase("美人","亲爱的") + "。 你最好快点去镇上, 免得他们再追你。 ";
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = "我太激动了! 你能把我带到" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "定居点的酒馆吗? 否则, 我担心他们会再追我。 ";
			link.l1 = "也许你是对的。 我们走吧...";
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dialog.text = "哦, 船长, 这是一个很长的故事, 我不确定你会觉得有趣。 虽然...现在没有你的帮助我还是做不到。 你能把我带到" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "定居点的酒馆吗? 我担心他们不会放过我。 ";
			link.l1 = "对不起, 亲爱的, 我没有时间。 我有事情要做。 ";
			link.l1.go = "Node_221";
			link.l2 = "你为什么这么神秘? ";
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = "如果每个人都想从我的不幸中获利, 我怎么能不神秘呢? ";
			link.l1 = "好吧, 那么...";
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dialog.text = "船长, 你答应过带我去" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "定居点的酒馆的。 ";
			link.l1 = RandPhraseSimple("我记得。 ","别担心, 我会带你去的。 ");
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
				{
					dialog.text = "那里人太多了。 我们去私人房间吧。 我有事要告诉你。 ";
					link.l1 = LinkRandPhrase("我已经为你做了太多, 现在再见。 ","你不应该滥用我的好意。 再见, 亲爱的。 ","我现在不需要你的故事了, 你可以自己解决。 ");
					link.l1.go = "Node_226";
					link.l2 = "嗯, 好吧。 那我去从酒保那里拿钥匙。 ";
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = "非常感谢你的帮助, 船长。 我不会忘记的。 ";
					link.l1 = "哦, 别麻烦了。 以后尽量小心点。 ";
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, 法国迷你任务 (FMK)
				{
					dialog.text = "非常感谢你的帮助, 船长。 我不会忘记的。 ";
					link.l1 = "哦, 别麻烦了。 以后尽量小心点。 ";
					link.l1.go = "Node_226_1";
				}
				else
				{
					dialog.text = "那里人太多了。 我们去私人房间吧。 我有事要告诉你。 ";
					link.l1 = LinkRandPhrase("我已经为你做了太多, 现在再见。 ","你不应该滥用我的好意。 再见, 亲爱的。 ","我现在不需要你的故事了, 你可以自己解决。 ");
					link.l1.go = "Node_226";
					link.l2 = "嗯, 好吧。 那我去从酒保那里拿钥匙。 ";
					link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // 关于一个无辜女孩误入妓院的感人故事
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "那么你仍然想听我的故事吗? ";
				link.l1 = "嗯...我想, 我该走了。 再见! ";
				link.l1.go = "Node_232";
				link.l2 = "好吧, 那就说吧。 ";
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = "哦, 我高贵的救世主, 终于我可以用一个女人唯一能感谢的方式来充分感谢你了\n当我在丛林中看到你时, 我内心的一切都改变了。 我忘记了强奸犯和抽打我脸颊的锋利棕榈叶。 忘记了要跑去哪里, 为什么要跑...我只看到了你。 并且只想要你...在你为我所做的一切之后...";
				link.l1 = "哇! 这脾气! 你的追捕者肯定知道该追谁...";
				link.l1.go = "Node_229"; // 主角惹恼了她 - 现在他将被简单地欺骗
				link.l2 = "听着, 美女, 我完全能理解, 但请控制一下你的脾气。 ";
				link.l2.go = "Node_230"; // 送她进行一次步行的色情之旅
			}
		break;
		
		case "Node_229":
			dialog.text = "现在到我这里来, 我的英雄...";
			link.l1 = "哦, 亲爱的...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = "哦! 你怎么...你怎么敢? ! 真是个混蛋! 一个女孩全心全意地感谢你, 而你...";
			link.l1 = "好吧, 如果你不那么调情, 不那么拼命追求你遇到的第一个男人, 你肯定不会有这么多麻烦。 我再也不会在丛林里救这样的调情者了...";
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = "我以前从未听过这样的话! 我不会原谅它们的! 你会记住我的! ";
			link.l1 = "好了, 走吧? 试着让自己精神点, 除非你想再被救一次...";
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "我的家人住在" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City) + "的定居点。 我是偶然来到这里的, 在我新郎带我去见他父母的船上, 但船被海盗劫持了。 船被夺走了, 乘客们被安置在离这里不远的海湾。 我的新郎在登船时被杀了, 我在穿越丛林的途中病得很重\n当地妓院的夫人治疗了我, 当我站起来时, 她要求我工作来支付治疗费用。 我是个妓女, 但我没有让夫人满意, 所以夫人把我卖给了一些土匪, 至少赚了一些钱。 故事的另一部分你知道。 ";
			link.l1 = "那就辞职回家! 你为什么允许他们像对待奴隶一样对待你? ! ";
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = "我不能! 我所有的东西: 体面的衣服。 钱。 文件...都在妓院里我的旅行袋里。 我把它藏在约会室里了。 而当我穿着这样的衣服时, 港口所有的水手都会追着我跑。 没有文件或钱, 谁会让我上船? 现在我甚至不能在镇上露面, 否则会被关进监狱...";
			link.l1 = "应该不是问题。 我们走。 我亲自送你回家。 ";
			link.l1.go = "Node_235";
			link.l2 = "在这里等。 我去给你拿旅行袋。 ";
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = "谁在乎你的文件? 你需要多少钱才能回家? ";
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = "哦, 谢谢你, 船长...但是...你知道, 我没有什么可以支付给你的。 ";
			link.l1 = "你说什么支付? 我们走吧, 趁他们还没被找到...";
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = "哦, 船长, 你知道, 我从来不敢问...";
			link.l1 = "不要害怕。 我很快就会回来。 ";
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "哦, 我已经在担心你可能发生了什么事。 ";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "可能发生什么事? 给, 拿你的东西。 ";
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = "听着, 我在那里什么也没找到。 你确定你把旅行袋留在约会室了吗? ";
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "谢谢你, " + GetSexPhrase("高贵的船长","高贵的女孩") + "。 我永远不会忘记你为我所做的一切。 我没有多少东西, 但请接受这个护身符。 也许正是这个小饰品在海盗袭击中救了我的命。 ";
			link.l1 = "谢谢你, 旅途愉快! 现在再见...";
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = "他们真的找到我的包了吗? ";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "你需要多少钱才能回家? ";
				link.l1.go = "Node_237";
			}
			link.l2 = "也许他们找到了。 不管怎样, 我们现在分道扬镳了。 再见! ";
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = "谢谢, 船长。 你知道, 很难相信我终于回家了。 请跟我来, 我把你介绍给我的父母。 ";
			link.l1 = "听着, " + GetSexPhrase("美女","亲爱的") + ", 我真的没有时间。 也许其他时间? ";
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = "真遗憾...那么, 再见, 愿上帝保佑你。 我没有什么可以报答你, 但请接受这个护身符。 ";
			link.l1 = "谢谢! 现在跑回家, 让你的父母高兴! ";
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = "嗯, 我不知道...也许, 我得等一个过路的车。 但我不能向你要钱。 ";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "我明白了。 好吧, 拿5000比索。 那应该够了。 ";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "我明白了。 好吧, 拿25000比索回家。 ";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "我明白了。 好吧, 拿35000比索。 那应该足够在船上买最好的客舱了。 ";
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			dialog.text = "谢谢你, " + GetSexPhrase("高贵的船长","高贵的女孩") + "。 我永远不会忘记你为我所做的一切。 ";
			link.l1 = "那么, 一路顺风。 再见...";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = "谢谢你, " + GetSexPhrase("高贵的船长","高贵的女孩") + "。 我永远不会忘记你为我所做的一切。 ";
			link.l1 = "那么, 一路顺风。 再见...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = "谢谢你, " + GetSexPhrase("高贵的船长","高贵的女孩") + "。 我永远不会忘记你为我所做的一切。 ";
			link.l1 = "那么, 一路顺风。 再见...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple("你听说了吗? 一个妓女试图无证偷偷登上一艘船, 但被抓住并带回了妓院。 他们说她欠了老鸨一大笔钱。 ",  
				"你听说了吗? 一个没有证件的妓女在港口被抓住了。 他们说她在试图逃离妓院之前清空了老鸨的金库。 我说, 这种污秽和盗窃的源头早就该关闭了。 我们的孩子甚至看到了这一点, 他们能从这样的例子中学到什么? "), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = "不要毁了我的生活, 船长! 我父亲想让我嫁给放贷人的儿子, 那个肮脏的懦夫...就因为他爸爸的金库里有很多钱! 嗯, 我宁愿留在丛林里被野兽吃掉, 也不愿和他一起被判终身监禁! ";
			link.l1 = "你的婚姻有什么问题, " + GetSexPhrase("美女","亲爱的") + "? 抓住那个想娶你的人, 然后快乐。 过一段时间你会很高兴嫁给那个懦夫, 但可能已经太晚了...";
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "不! 不, 船长, 我爱" + pchar.GenQuest.EncGirl.sLoverId + ", 我不会嫁给其他男人! 我父亲什么都不想听! 他说" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "在这里只是个访客, 所以他永远不会在这里找到工作, 他注定要在贫困中死去, 我也和他一起! 我会和他一起走到世界的尽头, 只为在他身边! 带我去找他, 我求你了! ";
			link.l1 = "好吧, 我们走。 我想我会想出怎么处理你...";
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "船长, 你答应过带我到" + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "的定居点。 ";
			link.l1 = RandPhraseSimple("我记得。 ","别担心, 我会带你去那里。 ");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("谢谢你, " + GetSexPhrase("船长","小姐") + ", 再一次。 真的, 我非常感激你。 ","非常感谢你, " + GetSexPhrase("船长","小姐") + "。 我不知道没有你的帮助我会做什么。 ");
				link.l1 = RandPhraseSimple("那应该给你一个教训。 好吧, 祝你好运...","下次你应该更小心...现在跑回家, 我有事情要做。 ");
				link.l1.go = "Node_260End";
				link.l2 = "你怎么能这么粗心? 你为什么一个人走进丛林? ";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "哦, " + GetSexPhrase("船长","小姐") + ", 我真的不知道如何感谢你。 ";
				link.l1 = "没什么。 总是乐于帮助...";
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = "你能带我去酒馆吗? 我需要等我的阿姨, 休息一下, 这次'冒险'耗尽了我所有的精力...";
			link.l1 = "不, " + GetSexPhrase("美女","亲爱的") + ", 对我来说这已经足够了。 我有很多事情要做。 ";
			link.l1.go = "Node_262";
			link.l2 = "" + GetSexPhrase("哦, 女人! 没有男人的帮助她们能做什么? ","你为什么这么无助? ") + "我们走吧...";
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = "我有一些钱...请接受它作为我感激的象征! ";
				Link.l1 = "谢谢。 下次尽量小心。 ";
				Link.l1.go = "exit";
			}
			else 
			{
				if(hrand(1) == 0)
				{
					dialog.text = "我会告诉所有人你救了我! 让每个人都知道, " + GetSexPhrase("你是一个多么勇敢和勇敢的男人","你是一个多么勇敢和勇敢的女人") + "! ";
					Link.l1 = "谢谢你。 现在你应该回家了。 ";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "我有一些钱...请接受它作为我感激的象征! ";
					Link.l1 = "谢谢。 下次尽量小心。 ";
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "我会告诉所有人你救了我! 让每个人都知道, " + GetSexPhrase("你是一个多么勇敢和勇敢的男人","你是一个多么勇敢和勇敢的女人") + "! ";
			Link.l1 = "谢谢你。 现在你应该回家了。 ";
			Link.l1.go = "exit";
		break;
	}
}