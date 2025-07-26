
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		////// 莱娅.卡诺 //////
		
		case "Exit":
			DialogExit();
		break;
		
		case "First Time":
			dialog.text = ""+GetSexPhrase("先生","女士")+"! 打扰了, 你是"+GetSexPhrase("水手","女水手")+"吗? ";
			link.l1 = "我是"+GetFullName(pchar)+"船长, 为你效劳。 ";
			link.l1.go = "Lea First Talk";
			DelLandQuestMark(npchar);
		break;

		case "Lea First Talk":
			dialog.text = "我是莱娅, 莱娅.卡诺... "+GetSexPhrase("先生","女士")+"船长, 你是最近才到的吗? 你在海上有没有见过一艘叫'鸬鹚号'的渔船? 你知道, 我的丈夫... 我的丈夫皮埃尔... 他两天前出海了, 到现在还没回来。 ";
			link.l1 = "'鸬鹚号'? 不, 我没见过这样的船。 这个名字我应该记得住。 听到这个消息我很难过, 夫人。 我希望你的丈夫平安无事, 只是在路上耽搁了。 ";
			link.l1.go = "Lea First Talk Rep Plus";
			link.l2 = "'鸬鹚号'? 哈! 这是船的名字还是船主的绰号? 不管怎样, 我都没见过。 ";
			link.l2.go = "Lea First Talk Rep Minus";
		break;

		case "Lea First Talk Rep Plus":
			dialog.text = "我不知道该怎么想... 他从来没有离开过这么久。 他总是在中午之前回来, 从来没有失过约。 现在... 出什么事了。 我能感觉到。 ";
			link.l1 = "去找当局。 他们可以派一艘巡逻船在沿海水域搜寻。 ";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
		break;

		case "Lea First Talk Rep Minus":
			dialog.text = "我不知道该怎么想... 他从来没有离开过这么久。 他总是在中午之前回来, 从来没有失过约。 现在... 出什么事了。 我能感觉到。 ";
			link.l1 = "去找当局。 他们可以派一艘巡逻船在沿海水域搜寻。 ";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
		break;

		case "Lea First Talk1":
			dialog.text = "哦, "+GetSexPhrase("先生","女士")+"船长, 我当然已经和指挥官谈过了。 但这有什么用呢? 他只是耸耸肩... 说他没有船只可以派去寻找我的丈夫。 \n而我呢? 我所能做的就是站在这里, 凝视着地平线, 等待... 并希望。 ";
			link.l1 = "好了好了, 莱娅夫人。 别这么绝望。 我想我可以抽出一天时间来帮你寻找。 ";
			link.l1.go = "Agree To Help";
			link.l2 = "为什么这么担心? 也许晨风吹着他投入了某个迷人女士的怀抱。 他会散散步, 呼吸一下新鲜空气, 然后回来的。 ";
			link.l2.go = "bad joke";
			link.l3 = "想要一点建议吗? 别再盯着地平线看了。 去勒弗朗索瓦的酒馆里找找你亲爱的丈夫吧。 别见怪, 但很可能他只是需要从家庭烦恼中解脱出来, 而你却把这变成了一场悲剧。 祝你好运。 ";
			link.l3.go = "Rejection";
		break;

		case "Agree To Help":
			dialog.text = ""+GetSexPhrase("先生","女士")+"船长, 我... 我不知道该怎么感谢你... 你... 你不知道这对我意味着什么! 每个人都只是耸耸肩... 但你... 你愿意帮忙。 谢谢你! ";
			link.l1 = "还不用谢我。 告诉我 --你丈夫通常在哪里捕鱼? 他有固定的地点, 还是喜欢四处游荡? ";
			link.l1.go = "Go To Help";
		break;
		
		case "bad joke":
			dialog.text = "一个迷人的女士? ! 你真的认为现在是开玩笑的时候吗? 我知道他有麻烦了... 而你却在嘲笑我的悲伤! (哭泣) 现在世界上的一切都与我作对。 没有人愿意帮忙... 没有人理解我的心有多沉重。 ";
			link.l1 = "莱娅夫人, 看在上帝的份上, 请原谅我的轻率。 我无意冒犯! 我发誓, 我会去找你的丈夫。 告诉我从哪里开始。 ";
			link.l1.go = "bad joke1";
		break;

		case "bad joke1":
			dialog.text = "你... ? 你真的打算帮我? ";
			link.l1 = "当然。 这是我能为我不可原谅。 不合时宜的笑话做出的最少补偿。 ";
			link.l1.go = "bad joke2";
		break;

		case "bad joke2":
			dialog.text = "谢谢你, "+GetSexPhrase("先生","女士")+"船长。 谢谢你... 真的, 你让我措手不及 --我不知道该说什么... ";
			link.l1 = "现在还不用谢。 相反, 告诉我 --你丈夫通常在哪里捕鱼? 他有固定的地点, 还是喜欢四处移动? ";
			link.l1.go = "Go To Help";
		break;

		case "Go To Help":
			dialog.text = "嗯... 皮埃尔... 他很少确切地告诉我他在哪里捕鱼。 他称这是'他的秘密'。 但如果这有助于找到他... 也许... 我不知道... 你真的打算帮忙, 对吗, "+GetSexPhrase("先生","女士")+"船长? 真的吗? ";
			link.l1 = "你在犹豫是否要分享你丈夫的秘密捕鱼地点? 我向你保证, 你家人的秘密与我同在 --我以船长的名义向你保证。 我必须知道这个地方才能开始搜索。 ";
			link.l1.go = "Go To Help1";
		break;

		case "Go To Help1":
			dialog.text = "你说得对, "+GetSexPhrase("先生","女士")+"船长... 请原谅我。 那个地方对皮埃尔意义重大。 他总是说那是他真正的秘密, 他的小宝藏。 \n但我知道它在哪里。 如果这能帮他回家... 他在勒马林峡附近捕鱼。 它沿着南海岸, 离城镇不远。 求你了, 我求求你 --找到他! ";
			link.l1 = "别担心, 莱娅。 我会尽我所能。 他有敌人吗? 最近有人威胁过他吗? ";
			link.l1.go = "Go To Help2";
		break;

		case "Go To Help2":
			dialog.text = "敌人? 皮埃尔? 他是世界上最善良的人! 他连一只苍蝇都不会伤害... 他只是一个普通的渔夫。 他可能得罪了谁呢? 我只是不明白发生了什么... 这一切都太奇怪了... 而且可怕... ";
			link.l1 = "别害怕, 莱娅夫人。 我马上就出发。 我相信你的丈夫很安全。 我会把他带回你爱的怀抱。 保持坚强。 ";
			link.l1.go = "Return Lea Exit";
		break;

		case "Return back to Lea":
			dialog.text = ""+GetSexPhrase("先生","女士")+"船长, 请 --你有什么消息吗? 你了解到什么了吗? 任何消息都行? ";
			link.l1 = "恐怕还没有。 但我还在搜索, 莱娅! ";
			link.l1.go = "Exit";
		break;
		
		case "Return Lea Exit":
			DialogExit();
			npchar.dialog.currentnode = "Return back to Lea";
			AddQuestRecord("VPVL", "2"); 
			DoQuestCheckDelay("VPVL_Start", 0.1);
			LocatorReloadEnterDisable("FortFrance_Town", "gate_back", true);
		break;
		
		case "Rejection":
			DialogExit();
			npchar.dialog.currentnode = "Rejection1";
			SetTimerCondition("VPVL_ClearLea", 0, 0, 2, false);  // 两天后删除莱娅
			CloseQuestHeader("VPVL");
		break;
		
		case "Rejection1":
			dialog.text = "你还想要什么? 你还没嘲笑够一个可怜的女人吗? ";
			link.l1 = "... ";
			link.l1.go = "Exit";
		break;

		case "Lea second talk":
			dialog.text = ""+GetSexPhrase("先生","女士")+"船长! 皮埃尔! 哦, 见到你我太高兴了! 你找到他了! ";
			link.l1 = "莱娅夫人, 我来介绍一下, 这是皮埃尔.卡诺本人。 我不能说他毫发无损, 但我毫不怀疑你的照顾会让他很快康复。 ";
			link.l1.go = "Lea second talk1";
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
		break;

		case "Lea second talk1":
			dialog.text = "皮埃尔! 圣母玛利亚! 我为你担心得要命! 你去哪儿了? 你的脸色一点血色都没有... 你太苍白了... 哦! 这是什么? ! 这些可怕的伤口? ! 割伤... 还有烧伤... ";
			link.l1 = "嘘, 我心中的珍宝。 只是些小伤, 很快就会好的。 能再次见到你的脸... 这就是我所希望的一切。 如果不是船长... 我欠"+GetSexPhrase("他","她")+"一条命。 ";
			link.l1.go = "Lea second talk2";
			CharacterTurnByChr(npchar, CharacterFromID("VPVL_Pier_carno"));
			sld = CharacterFromID("VPVL_Pier_carno");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_Lea_girl"));
			locCameraFromToPos(-7.62, 3.1, 83.26, false, 30, -15, 0);
		break;

		case "Lea second talk2":
			dialog.text = ""+GetSexPhrase("先生","女士")+"船长... 我... 我不知道该怎么感谢你... 你找到他了! 你救了我的皮埃尔! 谢谢你... 谢谢你所做的一切! 愿主保佑你, "+GetSexPhrase("先生","女士")+"船长! ";
			link.l1 = "好了好了, 够了。 皮埃尔真正需要的是一顿热饭和好好休息。 ";
			link.l1.go = "Exit";
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
			AddDialogExitQuest("VPVL_PierTalkOnThePirs");
		break;
		
		//////   走私者   //////
		
		case "Kontr Le Maren":
			dialog.text = "该死的! 你终于出现了, "+GetSexPhrase("你这个卑鄙的家伙","你这个讨厌的女人")+"! 你到底去哪儿了? 我们在这个该死的海滩上烤了三天了! 我们的货物呢? ! ";
			link.l1 = "看来没有我, 狂欢就无法开始, 是吧, 先生们? 嗯, 我可能迟到了一点 --但总比根本不来好! ";
			link.l1.go = "Exit_Sneak";
			link.l2 = "你在跟我说话吗? 也许在像舱底老鼠一样吠叫之前, 先学点礼貌! ";
			link.l2.go = "Exit_Lucky";
			//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
			locCameraFromToPos(-3.53, 2.35, 6.35, true, 1.93, -0.60, 11.17);
			DeleteAttribute(pchar, "questTemp.VPVL_Contr_V_Lemaren");
		break;
		
		case "Exit_Sneak":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification("获得潜行经验", SKILL_SNEAK);
		break;
		
		case "Exit_Lucky":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			notification("获得幸运经验", SKILL_FORTUNE);
		break;

		case "Kontr Le Maren0":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = ""+sld.name+", 你这个愚蠢的混蛋! 睁开你的死鱼眼, 你这个笨蛋 --这根本不是我们的联系人! ";
			link.l1 = "啊... 又是总督的一条走狗! 千真万确! 既然"+GetSexPhrase("这个黑鬼","这个傻女孩")+"把"+GetSexPhrase("自己","自己")+"拖到这里, 我们就把"+GetSexPhrase("他","她")+"和另一个老鼠一起拖到洞穴里。 我们会让"+GetSexPhrase("他","她")+"知道我们是如何迅速获取秘密的 --他们会吐露他们主人曾经梦想过的每一个肮脏计划! ";
			link.l1.go = "Kontr Le Maren1";
			locCameraFromToPos(-3.53, 2.35, 6.35, false, -0.03, 0.40, 7.77);
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_1"));
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_2"));
			
			sld = CharacterFromID("VPVL_contr_1");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_2"));
		break;
		
		case "Kontr Le Maren1":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = "你脑袋里在想什么肮脏的幻想, 你这个浸透了盐的畜生? 住口吧! 最好把她卖给... 你知道是谁。 他会为这样一个漂亮的姑娘掏出一箱金币, 我们就能痛饮狂欢一个月了! ";
			if (pchar.sex == "man")
			{
				dialog.text = "在戴维.琼斯的储物柜里, 我们要另一个水手来塞满我们的船舱干什么? 对他的同伴逼供 --他会像日出时的海鸥一样唱歌。 至于这个, 我们现在就把他在这里剖腹, 省得看着他的脸心烦! ";
			}
			link.l1 = "一千条饥饿的鲨鱼啃噬你的内脏, 西蒙! 你是整个群岛最狡猾的走私犯! ";
			link.l1.go = "Kontr Le Maren2";
		break;

		case "Kontr Le Maren2":
			dialog.text = "... ";
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) >= 20)
			{
				if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {
					notification("未装备手枪", "NONE");
					link.l2 = "如果那个笨蛋是你们最厉害的角色, 我真不敢想象你们其他人的脑袋里在想什么愚蠢的废话! ";
					link.l2.go = "Kontr Le Maren3";
					CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
					locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
					sld = CharacterFromID("VPVL_contr_1");
					CharacterTurnByChr(sld, CharacterFromID("Blaze"));
					CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
				}
				else
				{
					link.l1 = "(自言自语)(手枪) 当这些海老鼠喋喋不休地说废话时, 我有机会迅速而准确地出击, 就像晴天霹雳一样。 ";
					link.l1.go = "murder";
					notification("检查通过", SKILL_PISTOL);
					locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
				}
			}
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) < 20)
			{
				notification("技能太低 (20)", SKILL_PISTOL);
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				sld = CharacterFromID("VPVL_contr_2");
				CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
				CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
			}
			link.l2 = "如果那个笨蛋是你们最厉害的角色, 我真不敢想象你们其他人的脑袋里在想什么愚蠢的废话! ";
			link.l2.go = "Kontr Le Maren3";
		break;
		
		case "Kontr Le Maren3":
			dialog.text = "我要把你那喋喋不休的舌头从你脑袋里割下来, 你这个无礼的杂种"+GetSexPhrase(""," --下贱的荡妇")+ ", 然后把它喂给海鸥, 这样你就再也说不出另一个字了! ";
			link.l1 = "来啊, 你敢和魔鬼共舞吗? ";
			link.l1.go = "Kontr Le Maren Fight";
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
		break;
		
		case "Kontr Le Maren Fight":
			DialogExit();
			AddDialogExitQuest("VPVL_EveryoneFight");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false);
			EndQuestMovie();
		break;
		
		case "murder":
			DialogExit();
			AddDialogExitQuest("VPVL_Pistol_Murder");
			//locCameraFromToPos(-5.04, 2.62, 8.65, false, 20, -6, -15);
		break;
		
		/////////////   皮埃尔.卡诺   /////////////
		
		case "PierFirstTalk":
			dialog.text = ""+GetSexPhrase("先生","女士")+"... 原谅我... 我的头脑一片混乱... 你是来完成他们开始的事情的吗? ";
			link.l1 = "你是皮埃尔.卡诺吗? ";
			link.l1.go = "Pier_1";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.VPVL_SetFlagLeMaren");
		break;

		case "Pier_1":
			dialog.text = "是的, 是我。 你知道我的名字? ";
			link.l1 = "当然。 否则, 我来这里干什么? ";
			link.l1.go = "Pier_2";
		break;

		case "Pier_2":
			dialog.text = "原谅我, 我什么都不明白... 疼痛和饥饿让我失去了理智... 你为什么来? ";
			link.l1 = "很简单。 自从你失踪后, 你忠实的妻子一直在码头守望, 她的眼睛一直在寻找'鸬鹚号'的帆。 她的悲伤深深地刺痛了我, 我无法无动于衷地驶过 --我决心寻找你。 ";
			link.l1.go = "Pier_3";
		break;

		case "Pier_3":
			dialog.text = "我的妻子... 我亲爱的莱娅... 我以为我再也见不到她了... ";
			link.l1 = "那个时刻已经过去了。 她在码头等你, 仍然抱着希望。 我们离开这里吧。 扶着我的胳膊。 ";
			link.l1.go = "Pier_4";
		break;

		case "Pier_4":
			dialog.text = "仁慈... "+GetSexPhrase("先生","女士")+"... 我需要一会儿... 我的腿像浮木一样... 谢谢你, 真的。 如果不是你... 感觉好像是全能的上帝亲自派你来的... 你还没有告诉我你的名字。 我该如何称呼我的救命恩人? ";
			link.l1 = "我是"+GetFullName(pchar)+"船长。 在你恢复体力的时候, 告诉我你是怎么来到这个地方的。 你是在和这些... 人做生意吗? ";
			link.l1.go = "Pier_5";
			LAi_Fade("VPVL_PierStay", "");
		break;

		case "Pier_5":
			dialog.text = "天呐, 不, 船长。 我只是一个谦卑的渔夫。 那天一开始很顺利。 我在西海岸捕鱼 --收获非常好。 \n我急于把鱼装进桶里, 再撒一次网, 但没注意到水流把我的船冲向了礁石。 船体像蛋壳一样薄 --一击就足以让海水涌进来.'鸬鹚号'载着早晨的收获, 很快就沉没了。 ";
			link.l1 = "然后你上岸了, 结果走私者误以为你是总督的间谍? ";
			link.l1.go = "Pier_6";
		break;

		case "Pier_6":
			dialog.text = "正是如此。 我勉强上岸, 被该死的海浪打得遍体鳞伤。 我只需要晾干身子, 休息一下, 然后再回镇上。 然后, 那些魔鬼突然出现了。 \n他们一看就断定我是间谍。 我还没来得及说一句话, 他们就把我绑起来, 拖到了这里。 他们饿了我两天, 折磨我, 想让我承认我不知道的事情 --特工。 计划... 但我什么都不知道! ";
			link.l1 = "那帮家伙脑子不够用 --这就是为什么他们现在正在喂螃蟹。 但这一切都过去了。 你自由了。 是时候和你的妻子团聚了 --她肯定已经急得发疯了。 ";
			link.l1.go = "Pier_7";
		break;

		case "Pier_7":
			dialog.text = "我现在唯一想做的就是再次拥抱她。 我想... 我想我现在可以走路了。 ";
			link.l1 = "那就别再浪费时间了。 ";
			link.l1.go = "exit_grot";
		break;
		
		case "exit_grot":
			DialogExit();  
			AddQuestRecord("VPVL", "4");
			AddDialogExitQuest("VPVL_PierFollow");
		break;
		
		case "PierInThePirs":
			dialog.text = "船长, 我求你 --明天晚上六点钟到酒馆来。 如果我不能好好感谢你, 我的良心永远不会安宁。 现在... 我找不到合适的话语来表达我心中的感受。 求你了, 来吧。 这对我意义重大。 ";
			link.l1 = "好吧, 皮埃尔。 别担心 --我会去的。 ";
			link.l1.go = "GoHome";
			locCameraFromToPos(-8.28, 3.1, 82.93, false, 40, -15, 0);
		break;

		case "GoHome":
			DialogExit();
			AddQuestRecord("VPVL", "5");
			AddDialogExitQuest("VPVL_KarnoGoHome");
		break;

		case "PierTalkTavern":
			dialog.text = "船长! 你来了! 请坐! ";
			link.l1 = "乐意效劳! ";
			link.l1.go = "PierTalkTavern1";
			LAi_Fade("VPVL_SitOnTheTable", "");
			FreeSitLocator("FortFrance_Tavern", "sit6");  // 以防万一
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			pchar.questTemp.VPVL_DontSpawnSmugglersShipPier = true;
			DelLandQuestMark(npchar);
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
		break;

		case "PierTalkTavern1":
			dialog.text = "让我们举杯, 祝你的好运和健康长久! ";
			link.l1 = "不只是我的, 皮埃尔 --还有你的。 你看起来比我在那个可恶的洞穴里找到你时好多了。 干杯! ";
			link.l1.go = "PierTalkTavern2";
		break;

		case "PierTalkTavern2":
			dialog.text = "船长, 我无法用言语表达我无尽的感激! 你没有对我视而不见, 没有转身离开 --你帮助了一个完全陌生的人, 一个谦卑的渔夫。 这样的高尚品质值得丰厚的回报, 我希望把我所有的一切都给你。 \n这里 --二十块阳光金色的琥珀和五颗罕见的蓝色宝石, 是从一艘沉船中打捞出来的。 现在它们是你的了。 \n另外, 我想把我的航海仪器和渔具送给你。 我已经没有船了, 所以它们对我没有用了。 ";
			link.l1 = "谢谢你, 皮埃尔。 这些肯定会有用的。 但最重要的是, 你回家了 --你的妻子不必再生活在恐惧中了。 你们俩的事情会好起来的。 ";
			link.l1.go = "PierTakeGift";
			link.l2 = "皮埃尔, 我很感激你的心意, 但你应该留着它们。 你需要每一分钱来修理你的船, 买渔具。 渔网。 桶... 你的感谢 --看到你和你的妻子团聚 --这就足够了。 照顾好彼此。 ";
			link.l2.go = "PierWontGift1";
		break;
		
		case "PierTakeGift":
			dialog.text = "我仍然不敢相信这一切真的发生了... 让我们为我家庭的新篇章 --为你的高尚心灵干杯, 船长! ";
			link.l1 = "也为好运干杯, 皮埃尔。 我们都需要一点好运! ";
			link.l1.go = "ZastavkaVPVL";
			AddItems(PChar, "jewelry8", 20);
			AddItems(PChar, "jewelry7", 5);
			AddItems(PChar, "A_map_martiniqua", 1);
			AddItems(PChar, "spyglass3", 1);
			AddItems(PChar, "obereg_7", 1);
		break;

		case "PierWontGift1":
			dialog.text = "船长, 我不能就这样算了... 你救了我的命, 我欠你一切。 既然你拒绝了琥珀和其他礼物, 至少让我教你的船员如何在浅水区捕鱼。 这将让他们有饭吃, 当你购买物资时也能减轻你的负担。 你说呢? ";
			link.l1 = "这真是个好主意! 正如那句老话所说 --教一个人撒网, 他就永远不会挨饿。 ";
			link.l1.go = "PierWontGift2";
			pchar.questTemp.VPVL_Food = true;
		break;

		case "PierWontGift2":
			dialog.text = "说得好, 船长! 我很高兴能帮上忙。 现在 --我们再喝一杯怎么样? ";
			link.l1 = "为你的健康和繁荣干杯, 皮埃尔! ";
			link.l1.go = "ZastavkaVPVL";
		break;
		
		case "ZastavkaVPVL":
			DialogExit();
			SetLaunchFrameFormParam("四个小时过去了... ", "VPVL_SitOnTheTable", 2, 2);
			LaunchFrameForm();
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
			sld = CharacterFromID("VPVL_Pier_carno");
			sld.dialog.currentnode = "PierTalkTavern3";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;
		
		case "PierTalkTavern3":
			if(CheckAttribute(pchar, "questTemp.VPVL_Food"))
			{
			int foodDays = CalculateShipFood(&pchar);
			dialog.text = "以尼普顿的胡须起誓! 这朗姆酒真够劲! 再来两口, 我... 嗝... 我就要唱出一首能唤醒北海巨妖的船歌了! 从这里到港口的每个人都会听到我的声音! ";
			link.l1 = "把那船歌留到风平浪静的时候再唱吧, 皮埃尔。 留着你的嗓子... 嗝... 等我们下次靠港的时候再用。 要是你开始鬼哭狼嚎, 我很快就会跟着唱起来的。 而我有... 呃... 紧急的事情需要我关注。 潮水不等人... 嗝... 即使是喝醉了的人也一样! 祝你一路顺风... 嗝... 还有你那位好妻子也一样! ";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			notification("船只食物消耗减少15%", "None");
			}
			else
			{
			dialog.text = "以尼普顿的胡须起誓! 这朗姆酒真够劲! 再来两口, 我... 嗝... 我就要唱出一首能唤醒北海巨妖的船歌了! 从这里到港口的每个人都会听到我的声音! ";
			link.l1 = "把那船歌留到风平浪静的时候再唱吧, 皮埃尔。 留着你的嗓子... 嗝... 等我们下次靠港的时候再用。 要是你开始鬼哭狼嚎, 我很快就会跟着唱起来的。 而我有... 呃... 紧急的事情需要我关注。 潮水不等人... 嗝... 即使是喝醉了的人也一样! 祝你一路顺风... 嗝... 还有你那位好妻子也一样! ";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			}
		break;

		case "PierTalkTavern4":
			dialog.text = "啊, 船长... 你有一颗真正的水手之心... 嗝... 你确实有! 我对你的亏欠永远无法还清, 你听到了吗? 要是你的锚再次落入我们的港口... 我们的家... 我们的家就是你的, 就像你是同一个母亲所生的一样! 以我的灵魂和荣誉起誓! 当命运之轮再次把你带回这些海岸时, 我们会再次痛饮狂欢! ";
			link.l1 = "稳住船, 皮埃尔! 我最好... 嗝... 在我的海腿变成果冻之前起锚, 否则我会发现自己在这酒馆的地板上漂流! 愿顺风为你的帆助力! ";
			npchar.dialog.currentnode = "RepeatTavern";
			link.l1.go = "Exit2";
			CloseQuestHeader("VPVL");
		break;

		case "Exit2":
			DialogExit();
			LAi_Fade("VPVL_ExitFromTableVPVL", "VPVL_PierLivingTavern");
			DeleteAttribute(pchar, "questTemp.VPVL_Delete_Ship_RemoveFlag");
		break;

		case "RepeatTavern":
			dialog.text = "哟 --呵, 深邃的蓝色大 --海, 信风多温 --柔... 嗝... 拂晓时分我们就要航向渔 --场! ... 该死的, 这朗姆酒把我的脑子泡坏了! 歌词全忘了! 船长! ... 还没开船吗? 酒保! 快拿... 嗝... 你们酒窖里最好的西印度烈酒来! ";
			link.l1 = "我要起锚了, 皮埃尔! 嗝... 趁我还能在这危险的路上走回我的船, 不至于在浅滩上搁浅! ";
			link.l1.go = "Exit";
		break;

		case "MeetingInTneCity":
			dialog.text = ""+pchar.name+"! 真是让我这双被海盐腌渍的眼睛高兴啊! 来一杯加勒比最好的烈酒怎么样? 纪念我们在人生的茫茫大海上再次相遇! ";
			link.l1 = "你那饱经风霜的脸也让我满心欢喜, 皮埃尔。 可惜, 今天职责所在, 我得保持清醒。 我要穿越险象环生的海域, 需要清晰的头脑和稳健的双手。 也许下次我们运气好的时候? ";
			link.l1.go = "MeetingInTneCity1";
		break;

		case "MeetingInTneCity1":
			dialog.text = "遵命, 遵命, 船 --长! 船得先航行才能靠岸。 商人说得好, 先记账后享乐。 但等命运之轮再一次转向我们的时候, 我们一定要举杯痛饮, 让老黑胡子本人都为之骄傲! ";
			link.l1 = "把它记在航海日志里吧, 皮埃尔。 等潮水再一次把我们带到一起的时候! ";
			link.l1.go = "Exit";
			npchar.dialog.currentnode = "ExitRepeat";
		break;

		case "ExitRepeat":
			dialog.text = "船 --长! 你的船从那堆事务的风暴中找到安全的港湾了吗? ";
			link.l1 = "商务的浪潮还在拉扯着我的锚, 皮埃尔。 我的职责还得把我绑在舵轮上一会儿。 ";
			link.l1.go = "Exit";
		break;
	}
}