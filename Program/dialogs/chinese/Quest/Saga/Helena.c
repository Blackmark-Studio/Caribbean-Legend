// 埃伦.麦卡瑟 - 可疑的爱情与军官
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // 索引在末尾
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "有事吗? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "谢谢你的帮助, 船长! ";
			link.l1 = "我的天... 你比我想象的还要美丽! ";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "去他的美丽! 你知道这给我带来了多少麻烦吗? 如果不会毁了我的名声, 我早就割掉自己的鼻子了。 那个混蛋不让我活着离开护卫舰, 一直说我'知道得太多'。 然后昨天他告诉我, 他等腻了, 打算强行占有我\n你来得再及时不过了! 但我太失礼了, 我叫海伦.麦卡瑟。 爸爸以前叫我伦巴, 因为我总是不小心打碎他'获得'的精美瓷器, 所以现在我的船员都这么叫我。 ";
			link.l1 = "我叫" +GetFullName(pchar)+ ", 我是来救你的。 为了格拉迪斯女士, 我已经在加勒比海搜寻了你好几天。 ";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "格拉迪斯女士! ? 她怎么样了? ";
			link.l1 = "为你担心得要命。 但你很快就会见到她, 我们正在驶向蓝维尔德。 在路上你可以告诉我发生了什么。 ";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "说实话, " +pchar.name+ ", 我现在想吃点东西, 睡个觉。 在那怪物的船上熬了这么多天, 我累坏了... ";
			link.l1 = "当然, 麦卡瑟女士。 我会让管家为你准备一顿饭, 并在你的私人舱室里铺好床。 ";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//可以去岛上
			bQuestDisableMapEnter = false;//打开地图
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "德.莫尔船长, 我再次从心底感谢你的及时救援。 你一定要来拜访我和我母亲。 我们家离这里不远, 从码头过来在你左边。 记住, " +pchar.name+ ", 如果你不说再见就开船, 我永远不会原谅你! ";
			link.l1 = "这是我的荣幸, 麦卡瑟女士。 我一定会去拜访你! ";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // 打开斯文森的书房
			pchar.questTemp.Saga = "svenson";//去找斯文森
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//关闭埃伦的卧室
			// 关闭与格拉迪斯对话前的城镇
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "啊, 你来了, 德.莫尔船长! 很高兴你能来, 我有很多问题要问你。 ";
			link.l1 = "对不起, 麦卡瑟女士, 但我们的谈话需要推迟一下。 我需要先获取更多信息才能给出满意的答案。 现在我请你不要在街上露面。 希望你不会等太久。 相信我, 等我。 ";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CanDrink")) {
				link.l1.go = "drinking_refuse";
				link.l2 = "你自己说过, 如果我不来拜访, 你不会原谅我。 ";
				link.l2.go = "drinking_accept";
				
				DeleteQuestCondition("HelenDrinking_NoVisit");
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
			} else {
				link.l1.go = "exit";
				NextDiag.TempNode = "Helena_wait";
			}
		break;
		
		case "Helena_hire":
			dialog.text = "啊, 你来了, 我的船长! 你的眼神告诉我你有消息要告诉我! ";
			link.l1 = "斯文森船长告诉我你想和我一起航行。 我很欣赏你的愿望, 而且格拉迪斯女士提到你想念大海。 欢迎登船, 海伦.麦卡瑟女士! ";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "斯文森船长告诉我你想和我一起航行。 我很欣赏你的愿望, 而且格拉迪斯女士提到你想念大海。 欢迎加入我的船员, 海伦.夏普女士! ";
				link.l2.go = "Helena_hire_2";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 2;
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helen_friend");
			dialog.text = "是, 船长! 先生, 我不想这么说, 但我能保护自己, 不会容忍男人放肆。 我不对任何断手或挖眼负责。 ";
			link.l1 = "别担心, 我的船上纪律严明。 不过我必须问你一件事... ";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "... 什么事? ";
			link.l1 = "扬.斯文森和我发现你是宝藏岛的合法继承人。 是的, 是真的, 别摇头! 我有一半地图证明你的权利。 这不会容易, 但扬和我会尽力帮助你成为合法主人。 ";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+ PChar.name+ ", 你是认真的吗? 这样逗弄一个可怜的女孩可不善良! 我怎么会有整个岛屿的所有权? ! ";
			link.l1 = "我绝对是认真的, 麦卡瑟女士。 我会帮你夺回属于你的权利。 我们现在起航吧! ";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "你... 你说什么? 海伦.夏普? 为什么是Sharp? ";
			link.l1 = "海伦, 你是Beatrice Sharp的女儿, 也是Sharp王朝唯一的继承人。 这是格拉迪斯女士保存多年的半张地图。 这是你对宝藏岛权利的证明。 这不会容易, 但我和扬.斯文森会尽力帮助你继承祖父的岛屿。 ";
			link.l1.go = "Helena_hire_3";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
			Notification_Approve(true, "Helena");
			npchar.lastname = "Sharp";
		break;
		
		case "Helena_hire_3":
			dialog.text = "哦... 我可怜的母亲! 希望有一天我能找到她的坟墓, 在那里为她的灵魂祈祷。 但是... 等等! 不可能! ";
			link.l1 = "怎么了, Sharp女士? ";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "吉普赛女人的预言刚刚应验了... 我现在终于明白了。 ";
			link.l1 = "嗯? 什么预言? ";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+ PChar.name+ ", 你可能觉得我天真, 但我还是要告诉你。 我小时候, 一个吉普赛女人告诉我:'你的命运将掌握在那个不拿寡妇硬币。 归还死者黄金。 说出母亲名字的人手中'\n我当时以为这都是胡话, 但不知怎么的, 你竟然满足了预言的每一部分, 你不可能知道这些! ";
			link.l1 = "你说这是你的命运... 也许你是对的。 我不会让你失望的。 我们会一起寻找你母亲的坟墓。 现在... 海伦.夏普女士! 准备出发, 不要迟到! ";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "是, 船长! ";
			link.l1 = "... ";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//关闭地点
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//打开城市出口
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			AddQuestUserData("Saga", "sTimer", AddDaysToDateString(367));
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 请遵守最后期限! ");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2, false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				AddQuestRecord("HelenDrinking", "3");
				
				SetFunctionLocationCondition("HelenDrinking_IslaTesoroAmbush", "Pirates_town", false);
				sld = &locations[FindLocation("Pirates_town")];
				sld.locators_radius.quest.detector1 = 4.0;
			}
		break;
		
		//--> 巴尔巴宗诱惑中的海战咨询
		case "sea_bomb":
			dialog.text = ""+pchar.name+ "船长! 我有个主意... ";
			link.l1 = ""+npchar.name+ "? 这里不安全, 我告诉过你待在船上... ";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = "查尔斯, 这艘旧船上塞满了火药, 如果爆炸, 整个岛都会飞到圣彼得的家门口! 你让我躲起来也没用, 所以听我说! ";
			link.l1 = "好吧, 快点说! ";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "那艘护卫舰和轻帆船。 他们不认为奈夫的船是敌对的。 我们可以利用他们的自满。 我们拿几桶火药, 设置导火索, 然后驶向那些船\n他们会让我们靠近, 我们点燃导火索, 把桶扔到其中一艘船上, 然后尽快离开。 然后我们就能看到壮观的爆炸... 你觉得怎么样? ";
			link.l1 = "简易火船... 非常狡猾! 你的计划够疯狂, 说不定真能奏效... 如果我们能在不被认出来的情况下靠近。 ";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = ""+pchar.name+ ", 我们有什么可失去的? 同时对抗两艘船并不容易, 但我们有机会扳平比分... ";
			link.l1 = "好吧。 我们开始吧! 伙计们! 拿三桶火药! 我们要离开这里! 我喜欢你的想象力, " + npchar.name+ "... 我自己永远想不到这个主意。 ";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "是, 船长, 有什么事? ";
			link.l1 = "杰克曼的船在萨博-马蒂拉峡, 重型护卫舰'百夫长'。 这艘船曾经是霍克斯家族的财产, 所以杰克曼的船舱里一定有重要物品和文件... 我们必须登船。 ";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "说起来容易做起来难。 你打算怎么用我们的双桅船做到这一点? 他们的人员和火力都超过我们。 ";
			link.l1 = "你说得对。 杰克曼的人至少是我们的两倍, 而且都是经验丰富的剑客。 没有预先炮击就攻击是疯狂的。 但持久战也不是最佳选择。 所以我一直在想该怎么做。 ";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+ ", 他们还没有把我们认作敌人, 就像特克斯那些傻瓜一样... 我们可以再试一次我们的诡计... ";
			link.l1 = "海伦, 我刚告诉你我们必须登船搜索护卫舰, 把它炸上天不是选项。 ";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "等等, " +pchar.name+ ", 我们不会沉了它。 让我们变通一下。 听着, 我们要拿几个空朗姆酒桶, 装满火药。 葡萄弹和短导火索。 然后我们靠近他们的护卫舰, 把简易爆炸物扔到他们的甲板上。 ";
			link.l1 = "哈! 你的女性智慧继续让我惊讶! 你建议的不是火船, 而是福加斯? 你认为这能奏效吗? ";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "为什么不呢? 他们的干舷比我们高, 但两三个男人用滑轮可以轻松吊起并投掷满载的桶。 我们会大喊 -'这是奈夫送的免费朗姆酒!'桶在他们反应过来之前就会爆炸";
			link.l1 = "爆炸的葡萄弹会把甲板上的精锐变成肉泥... 该死, 听起来很诱人。 ";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "我们一次从后甲板向船尾扔五个桶。 " +pchar.name+ ", 我们有出其不意的优势。 他们还不会怀疑! 然后我们在他们有机会登船之前立即离开。 ";
			link.l1 = "好吧, 我们试试。 在我们把爆炸桶扔到他们甲板上之前, 他们不能认出我们... 靠近不会容易。 杰克曼不像食尸鬼那么愚蠢。 ";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "我们冒这个险吧, " +pchar.name+ "! 就像我之前说的, 我们有什么可失去的? ";
			link.l1 = "说得好... 各就各位! 准备福加斯, 准备战斗! ";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//< —海战咨询结束
		
	// --> 传奇结局对话
		case "result":
			//if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // 不是朋友
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 11) {
				Achievment_Set("ach_CL_83");
			}
			
			if (sti(pchar.questTemp.Saga.HelenRelation) < 6)
			{
				dialog.text = "好吧, 我亲爱的船长... 我们该说再见了。 我的服务结束了, 是时候习惯成为宝藏岛的海盗女王了。 希望我能成为我叔叔的合格继承者。 感谢你的帮助。 ";
				link.l1 = "是的, 很遗憾与你分开, 但命运就是如此。 你现在有比在我船上服务更重要的责任。 ";
				link.l1.go = "result_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Mary")) {
					dialog.text = "我想留在你的船上。 靠近你... 但不可能。 祝你幸福, 查尔斯。 她最好配得上你! ";
					link.l1 = "对不起, 海伦。 ";
					link.l1.go = "result_mary";
				} else {
					dialog.text = ""+pchar.name+ ", 这很奇怪! 我刚刚成为整个岛屿的主人, 但我并不觉得自己是宝藏岛的女王... 我想兄弟会的新首领能比我更好地管理殖民地。 我有很多东西要学。 ";
					link.l1 = "别担心, 海伦, 你是个能照顾好自己的女人 - 就像你第一次上船时告诉我的那样。 ";
					link.l1.go = "result_9";
				}
			}
			
			DeleteQuestCondition("HelenDrinking_AtSHDN");
			DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
		break;
		
		case "result_mary":
			dialog.text = "那么, 我们仍然是朋友, 对吗? ";
			link.l1 = "当然... 海伦, 我们会在宝藏岛再见。 要我带你去你的岛吗? ";
			link.l1.go = "result_12";
		break;
		
		case "result_1":
			dialog.text = "你说得对... 看, 我在你船上航行时存了一份战利品。 拿着, 别试图拒绝我的提议 - 我不想欠你人情。 ";
			link.l1 = "嘿, 等一下... ";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "我知道你要说什么。 当然, 你的帮助比这微薄的一箱财宝重要得多。 但这是我现在拥有的一切, 我必须报答你。 拿着, 如果你自己不拿, 我就留在你的船舱里。 ";
			link.l1 = "你现在要自己航行吗? 也许我可以带你去宝藏岛? ";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("你收到了一箱杜布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "不需要, " +pchar.name+ "。 我会自己去岛上。 我有剑和手枪, 暂时够用了... 我相信宝藏岛的女王到那里后不需要担心收入。 ";
			link.l1 = "是, 陛下。 祝你在新生活中好运。 ";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "够了, 即使是开玩笑。 对我来说你还是海伦。 但这不是我想说的全部。 我又找到了我父亲, 尽管有点奇怪。 他为了我的遗产付出了英国贵族的好名声, 这让我很困扰。 英国联邦在追捕他, 我不希望你, " +pchar.name+ ", 参与其中。 ";
			link.l1 = "清醒点, 海伦! 他是个强盗和海盗! ";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "海盗? 你他妈是谁, 敢说这种话? 他是我父亲, 这对我很重要! 而我, 强盗和海盗的女儿, 不在乎英国司法怎么看他。 如果你试图以任何方式伤害我父亲, 我会忘记你为我做的一切, 记住这一点。 考虑这是一个警告。 ";
			link.l1 = "是这样吗? 实际上, 女孩, 你最好礼貌一点。 当我把你漂亮的皮肤从强奸犯多诺万手中救出来时, 或者当我们分享战利品时, 我没注意到你对我的海盗态度有任何抱怨! ";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "我... ..我很抱歉。 我收回, 原谅我。 我失去了理智... 但尽管如此, 我想继续做你的朋友, 如果你开始追捕我父亲, 这就不可能了。 ";
			link.l1 = "明白了。 但女人, 永远不要威胁我。 你在我船上航行应该知道, 我不怕任何人任何事。 我尤其不会容忍一个女人的不尊重 - 不管是不是海盗女王。 我也许是个绅士, 但我的耐心也有限。 现在事情解决了, 再见。 祝你好运。 ";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "谢谢你... 。 也许我们会再见, " +pchar.name+ "... ";
			link.l1 = "为什么不呢? 我将来会多次访问宝藏岛。 在那里见... 再见, 海伦。 ";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // 埃伦离开, 但不删除她
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//关闭地点  // 已经不需要。 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors 伐木工。 让她跑开消失而不是站着。 
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // 伐木工。 码头。 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // 大门.
			InterfaceStates.Buttons.Save.enable = true;//可以保存		
			if (CheckAttribute(pchar, "questTemp.LSC.MaryWait")) {
				pchar.questTemp.LSC.Mary = "return";
			}
		break;
		
		case "result_9": // 关键时刻, 如果玩家找到了玛丽 - 选择哪个女孩更可爱
			dialog.text = "我确定。 " +pchar.name+ ", 如果你允许, 我想留在你的船上。 和你在一起... ";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(选择玛丽) 你不明白, 海伦。 你的整个未来都在前方, 没有什么可担心的。 我只有战争。 政治阴谋和前方的完全不确定性。 你必须安排自己的生活, 里面没有像我这样的流浪者的位置。 ";
				link.l1.go = "result_10";
				link.l2 = "(选择海伦) 这超出了我的期望, 海伦。 当然我不想失去你, 但你最好去宝藏岛。 谁知道我的命运会把我引向何方。 现在, 我有战争。 政治阴谋和不确定性在前方。 ";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "这超出了我的期望, 海伦。 当然我不想失去你, 但你最好去宝藏岛。 谁知道我的命运会把我引向何方。 现在, 我有战争。 政治阴谋和不确定性在前方。 ";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+ PChar.name+ "! 别骗我。 你只是不想... 告诉我, 她是谁? 是那个来自废弃船只之城的红发荡妇, 对吗? ";
			link.l1 = "海伦! 我在努力告诉你我认为什么对你最好! 你怎么不明白? ! ";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "哦, 当然, 你是... 她是怎么迷住你的, 嗯? 她有什么我没有的? ! 她真的那么好吗? 嗯, " +pchar.name+ "... 好吧, 这是你的决定, 我只能去我的岛。 我不能站在你们两个之间\n谢谢你为我所做的一切, 查尔斯。 你是我见过的最好的男人。 希望我们能继续做朋友? ";
			link.l1 = "当然... 海伦, 我会在宝藏岛再见到你。 要我带你去那里吗? ";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "不需要。 我会买一艘新船。 在你手下服务期间, 我已经攒够了钱买一艘纵帆船并装备它。 我会再次驾驶新的'彩虹'号航行。 ";
			link.l1 = "很高兴, 海伦, 你如此... 节俭。 但驾驶纵帆船不适合宝藏岛的海盗女王。 很快, 你应该给自己弄一艘护卫舰。 ";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "也许吧, " +pchar.name+ "。 好吧。 我会去造船厂, 但首先... 给我一个吻告别... 求你了... ? ";
			link.l1 = "海伦... ";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // 告别之吻
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //转动时间
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 0.5);
			pchar.questTemp.LSC.Mary = "return"; // 去找玛丽
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // 伐木工。 码头。 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // 大门.
			InterfaceStates.Buttons.Save.enable = true;//可以保存
		break;
		
		case "result_15":
			dialog.text = "自从我们相遇, 我的命运就是你的命运。 你不明白吗? " +pchar.name+ "? 我会跟随你到世界的尽头! ";
			link.l1 = "那你父亲呢? 劳伦斯.贝尔特罗普? 他是我的敌人... ";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "我父亲是肖恩.麦卡瑟。 我爱他, 为他哀悼。 他是我唯一的父亲。 而那个海盗... 我甚至不想谈论他。 ";
			link.l1 = "海伦... 我亲爱的海伦! ";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+ ", 我一直想告诉你, 你是我见过的最伟大的男人! 你为我做了太多, 我永远无法报答。 我想和你在一起。 永远。 如果你愿意, 我会嫁给你... 我爱你。 ";
			link.l1 = "我们会在一起的。 我保证! "; // 现在你还能去哪里 :)
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) {
				link.l1.go = "result_17A";
			} else {
				link.l1.go = "result_18";
			}
		break;
		
		case "result_17A":
			dialog.text = "答应我现在为我做件事? 请不要笑! ";
			link.l1 = "我答应, 亲爱的! ";
			link.l1.go = "result_17A_1";
		break;
		
		case "result_17A_1":
			dialog.text = "用我的真名称呼我。 求你了! ";
			link.l1 = "我爱你, 海伦.夏普。 ";
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+ PChar.name+ ", 亲爱的... 拥抱我! 我等这一刻等了太久了! ";
			link.l1 = "海伦, 我亲爱的... ";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // 浪漫场景
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			InterfaceStates.Buttons.Save.enable = false;//禁止保存
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // 伐木工。 码头。 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // 大门.																					   
			
			pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
			pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
			pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
			
			// 隆威任务"导航星", 开始第5阶段
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
		
		case "happy":
			dialog.text = ""+ PChar.name+ "! 那是... 难以置信! 我哪里也不想去... 我们在这里待到早上吧。 世界可以等! ";
			link.l1 = "我们让它等吧, 海伦! ";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("第二天早上... ", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // 标志, 埃伦永远是我们的
			npchar.SpecialRole = "fgirl";
			
			pchar.GenQuest.BrothelCount = 0;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
			
			// Выполнено требование для Дороже золота
			pchar.questTemp.GoldenGirl_Ready = true;
		break;
		
	// ------------------------------------------ —传奇失败 ------------------------------------
		case "failcenturion":
			dialog.text = "船长! 杰克曼死了... 我的家人终于安全了吗? ";
			link.l1 = "是的, 海伦, 你们都安全了。 但'百夫长'号沉没了, 所有能帮助我们找到你母亲坟墓并证明你对宝藏岛权利的文件也沉没了... 唉... 现在我只能独自突袭托尔图加... ";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+ ", 别太担心。 我们对此无能为力。 也别担心我, 没有那个岛我也能活得很好。 感谢你为我所做的一切! ";
			link.l1 = "听起来你要... 离开我, 对吗? ";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "是的, 我的船长。 我已经攒够了钱买一艘纵帆船并装备它。 我会再次驾驶我的'彩虹'号航行。 我们会在蓝维尔德再见... 我要回家了。 ";
			link.l1 = "好吧... 祝你好运, 海伦! ";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // 去找玛丽
			}
		break;
		
		case "late_l1":
			dialog.text = "好吧, 我的船长... 看来我们失败了。 再见。 我要回家了。 在你手下服务期间, 我已经赚够了钱为自己买一艘新的纵帆船。 我们海上再见! ";
			link.l1 = "祝你好运, 海伦。 我为一切感到抱歉。 再见。 ";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "船长! 杰克曼死了... 看来我的家人安全了, 对吗? ";
			link.l1 = "是的, 海伦, 安全了。 但我不高兴, 我浪费了太多时间, 宝藏岛现在是英国殖民地。 你失去了继承权, 所以我只能独自突袭托尔图加... ";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+ ", 律师告诉你什么了? ";
			link.l1 = "我浪费了太多时间, 宝藏岛现在是英国殖民地。 你失去了继承权, 所以我只能独自突袭托尔图加... 唉, 我们输了。 ";
			link.l1.go = "failcenturion_1";
		break;
	// < —传奇失败
		
		// 性 - 埃伦不总是同意 (头疼, 你还想怎样? :)) 并且自己不要求性
		case "cabin_sex":
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "不, 亲爱的, 不行。 ";
				link.l1 = "好吧, 为什么不? ! ";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0)// 拒绝概率20%
			{
				dialog.text = RandPhraseSimple(pchar.name+ ", 我今天感觉不舒服。 请不要难过, 这不是你的错。 我们今天不做了... ", pchar.name+ ", 亲爱的, 我最近几天太累了。 说实话, 我只想睡觉。 原谅我。 我们下次再做。 ");
				link.l1 = RandPhraseSimple("好吧... ", "没关系。 如你所愿... ");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(pchar.name+ ", 情绪正好, 我们走吧! ", pchar.name+ ", 当然, 没问题! 我们走吧! ");
				link.l1 = RandPhraseSimple("这才是我的女孩... ", "你真可爱, 海伦... ");
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			}
		break;
		
		case "sex_after":
			dialog.text = LinkRandPhrase(RandPhraseSimple("太棒了, " +pchar.name+ "! ..", "你一如既往地出色, 亲爱的... "), RandPhraseSimple("太棒了, 查尔斯! ", "亲爱的, 过得很愉快! "), RandPhraseSimple("和你在一起从不无聊, 我的船长! ", "你太棒了, 亲爱的! "));
			link.l1 = RandPhraseSimple("我爱你... ", "和你在一起总是很好, 海伦... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//打开地点
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+ ", 你知道我总是很高兴... 但现在不是时候 - 我们必须在蒂博逃跑前抓住那个恶棍。 ";
				link.l1 = "你总是对的, 海伦... ";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "不, 亲爱的, 不行。 ";
				link.l1 = "好吧, 为什么不? ! ";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0) // 拒绝概率20%
			{
				dialog.text = RandPhraseSimple(pchar.name+ ", 我今天感觉不舒服。 请不要受伤。 我们今天不做了... ", pchar.name+ ", 亲爱的, 我最近几天太累了。 说实话, 我只想睡觉。 原谅我。 我们下次再做。 ");
				link.l1 = RandPhraseSimple("好吧... ", "没关系。 如你所愿... ");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(pchar.name+ ", 我爱你! 我们走吧! ", pchar.name+ ", 是, 船长! 我们走吧! ");
				link.l1 = RandPhraseSimple("你是我的好女孩... ", "你真漂亮, 海伦... ");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
            pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;
			//npchar.quest.daily_sex_room = true; // 第一次在酒馆时启动计数器 。 伐木工
			//npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
			DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "LoveSex_Room_Go");
		break;
		
		//--> --------------------------------- —军官模块 ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("是的, " +pchar.name+ "? ", "是的, 我的船长? ", "我在听, " +pchar.name+ "... ");
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining");
				dialog.text = "看这个, 我的船长! ";
				link.l1 = "哇, 握得真紧! 我看你没浪费时间, 海伦。 ";
				link.l1.go = "cutlass_training";
				NextDiag.TempNode = "Helena_officer";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && sti(pchar.GenQuest.BrothelCount) > 0 && !CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "亲爱的, 关于你拜访妓女的事。 ";
				npchar.quest.refusesex = true;
				link.l1 = "什么? 海伦, 你完全搞错了! 我只是... ";
				link.l1.go = "brothel_found";
				NextDiag.TempNode = "Helena_officer";
				SetFunctionTimerCondition("Helena_ClearRefuseSex", 0, 0, 180, false);
				DeleteQuestCondition("Helen_GiveSex");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "海伦, 我要去拜访失落的印第安城市 Tayasal。 我不想骗你: 这次旅行非常危险, 甚至更多 - 包括通过神像传送。 你会... 跟我来吗? ";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////军需官///////////////////////////////////////////////////////////
           		// boal 船只报告
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "海伦, 给我一份完整的船只报告。 ";
			    Link.l11.go = "QMASTER_1";
			        
			    // 战舰。 自动购买货物
				Link.l12 = "我希望你每次靠岸时都购买特定货物。 ";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////军需官////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////同伴//////////////////////////////////////////////
			{
				//dialog.text = "我按你的命令来了, 船长。 ";
				Link.l2 = "海伦, 我需要给你几个命令。 ";
				Link.l2.go = "Companion_Tasks";
				
				sld = GetCharacter(sti(npchar.RealCompanionIdx));
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Rainbow") && sld.ship.type == pchar.questTemp.HelenDrinking.Rainbow && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
					DeleteAttribute(link, "");
					dialog.text = "你觉得这有趣吗? ";
					link.l1 = "不错的船, 不是吗? 给你买的, 海伦! 想想看, 加勒比海有哪个男人会给他的女人一艘真正的船, 嗯? ";
					link.l1.go = "rainbow";
					
					NextDiag.TempNode = "Helena_officer";
					break;
				}
				
				NextDiag.TempNode = "Helena_officer";// 别忘了根据不同的offa更改
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "海伦, 我需要你的建议。 ";
				Link.l3.go = "fugas";
			}
			Link.l1 = "海伦, 我有一个命令给你... ";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - 亲密关系的后续修复
			{
				Link.l2 = RandPhraseSimple("海伦, 我们单独在船舱里待... 几个小时? 你觉得怎么样? ", "亲爱的, 我们单独待几个小时怎么样? 你喜欢这个主意吗? ");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - 亲密关系的后续修复
			{
				Link.l2 = RandPhraseSimple("海伦, 我们为什么不租个房间, 私下待在那里... 接下来的几个小时? 你觉得怎么样? ", "亲爱的, 我们接下来几个小时单独待着怎么样? 我们租个房间... 你觉得呢? ");
				Link.l2.go = "room_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "town" && sti(pchar.money) >= 1000 && GetNpcQuestPastDayWOInit(npchar, "special_sex_date") >= 30 && !CheckAttribute(npchar, "quest.refusesex"))
			{
				Link.l2 = "海伦, 亲爱的, 我可以邀请你在酒馆度过一段美好时光吗? ";
				Link.l2.go = "special_sex";
			}
			if (CheckAttribute(pchar, "questTemp.MysteryPortRoyal_Helena")) {
				link.l4 = "海伦, 看来我找到了你崇拜者弗朗西斯的最后遗嘱。 他把遗产留给了你。 ";
				link.l4.go = "MysteryPortRoyal_Helena_1";
			}
			if (CheckCharacterItem(pchar, "pirate_cutlass") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
				link.l4 = "我认为这把弯刀现在是你的了。 布莱斯是你所谓的叔叔... ";
				link.l4.go = "give_cutlass";
			}
			link.l9 = "现在没什么事, 海伦。 ";
			NPChar.id = "Helena"; // 伐木工。 无论如何识别埃伦。 如果失去意识。 
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		/////////////////////////// 军需官回答 - 埃伦 ..(埃伦当军需官 - 可怕!))///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "查尔斯, 亲爱的, 你病了还是怎么了? 怎么, 你指望我下去, 打扫货舱, 开始数老鼠? ";
			Link.l1 = "对, 抱歉亲爱的, 是我错了... ";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "我想要一艘属于自己的战列舰, 一百门炮, 时速20节。 我一辈子都像你一样当船长。 你自己去找个该死的事务官, 去烦他吧。 ";
			link.l1 = "是, 你说得对, 海伦。 抱歉。 ";
			link.l1.go = "exit";
		break;
		//同伴指令 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "我洗耳恭听。 ";
			Link.l1 = "关于我们的登船策略... ";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "关于你指挥的船... ";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "目前没有。 ";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "你有什么愿望, 我的船长? ";
			Link.l1 = "我不希望你登任何船。 保护好自己和你的人。 ";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "我希望你一有机会就登敌船。 ";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "是的, 我的船长? ";
			Link.l1 = "如果你登船后能不换船, 我会很感激。 她对我太有价值了。 ";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "如果你碰巧登了任何人的船, 好好看看战利品船。 如果她不错, 随便拿去。 ";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "好吧, 我会考虑的。 ";
			Link.l1 = "她会考虑的... 对, 就像我能给她下命令一样。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "好吧, 我会考虑的。 ";
			Link.l1 = "她会考虑的... 对, 就像我能给她下命令一样。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "好吧, 我会考虑的。 ";
			Link.l1 = "她会考虑的... 对, 就像我能给她下命令一样。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "好吧, 我会考虑的。 ";
			Link.l1 = "她会考虑的... 对, 就像我能给她下命令一样。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "命令? ";
            Link.l1 = "待在这里! ";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "跟我来, 跟上! ";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "更改你火器的弹药类型。 ";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "选择弹药类型: ";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "遵命, 船长! ";
            Link.l1 = "... ";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "遵命, 船长! ";
            Link.l1 = "... ";
            Link.l1.go = "Exit";
        break;
		//< —--------------------------------- —军官模块 ----------------------------------------
		
		// --> 龟汤
		case "terrapin_grot":
			dialog.text = "你在这儿! 我终于找到你了... 刚才太惊险了, 我的船长! 我从未见过如此惊险的屋顶奔跑和从如此惊人高度的跳跃! 我的心都快跳出来了! 亲爱的, 总有一天你会用这些绝技吓死我... 哦, 你不是一个人... 这位姑娘是谁? ";
			link.l1 = "这是凯瑟琳.福克斯, 福克斯上校的女儿, 著名的英国海上步兵团'海狐'的指挥官。 我们要带她去安提瓜。 ";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "是这样吗... 欢迎登船, 福克斯女士! .不, 不, 别挽着德.莫尔船长的胳膊, 你自己能走得很好! 现在我们去长艇 - 我们需要离开这里。 "; 
			link.l1 = "哈! 谢谢你, 海伦! 没有你我该怎么办? 凯瑟琳, 跟我们来! ";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// < —龟汤
		
		// --> 幽灵船
		case "on_coast":
			dialog.text = "亲爱的, 你终于醒了! 感觉怎么样? 你快把我吓死了... ";
			link.l1 = "海伦, 发生了什么? 我头痛欲裂... ";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "我们进入船长舱时, 你一动不动地躺在地板上。 我的心都快停止跳动了! 伙计们把你抬回我们的船 - 正好及时, 因为甲板上的死人开始再次站起来。 \n太恐怖了! 这几乎让我想找到上帝! 他们完全不受我们的刀刃和子弹影响! 我们迅速切断绳索试图逃离, 但他们船上的一轮齐射严重损坏了我们的船, 我们失去了控制。 然后他们升起帆, 眨眼间就不见了。 \n我们的船搁浅了, 所以我们必须在风暴摧毁它之前逃到这个海岸。 今天很多好人死了, 但船最终幸存了下来... 要是我没有命令弃船就好了... ";
			link.l1 = "这不是你的错, 海伦。 这是正确的决定。 没有你我该怎么办? ";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "我把你拖上小船, 然后把你带到岸上。 你看起来像死了一样, 只有心脏在微弱地跳动。 看! 我的手还在抖";
			link.l1 = "谢谢你, 亲爱的。 我欠你一条命。 我在这里躺了多久? ";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "整整一天。 我清洗并包扎了你的伤口, 给你喂了药, 还给你灌了些朗姆酒。 现在你必须好起来! ";
			link.l1 = "这次我不会死的, 亲爱的。 虽然我感觉不太好... 呃... ";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "告诉我... 。 查尔斯, 那是真正的'飞翔的荷兰人'吗? 他们为什么攻击我们? 为什么他们靠近时不向我们射击, 而是登船后立即试图击沉我们? ";
			link.l1 = "他们的船长需要那个护身符, 就是我和印第安萨满图图阿帕克谈过的那个。 我不知道他们为什么需要它... 但一旦他们的首领拿到护身符, 就处置了我们... 全能的上帝啊, 真是一场噩梦! 一艘由活死人驾驶的船! 难以置信... ";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "是啊, 现在轮到我们遭遇'飞翔的荷兰人'了。 呸! 让我毛骨悚然! 我们下一个停靠的港口, 我要去教堂, 点一支蜡烛, 向我们的主耶稣基督祈祷我们奇迹般的获救。 见鬼, 我太感激了, 甚至会向一些天主教圣徒祈祷... ";
			link.l1 = "我会和你一起去, 海伦, 我有段时间没去做过正式的忏悔了... 但首先我们必须回到那个村庄。 我需要把一切都告诉图图阿帕克。 那艘被诅咒的船因为护身符攻击了我们! 我希望那个红皮肤的魔鬼知道为什么那些活死人需要它。 ";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "好吧。 但我们必须小心 - 你的伤口才刚刚愈合。 ";
			link.l1 = "但你会帮助我更快康复, 对吗? 我爱你, 海伦... ";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//打开地点
			dialog.text = "我也爱你, 亲爱的... ";
			link.l1 = "... ";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// < —幽灵船
		
		// 在泰亚萨尔
		case "tieyasal":
			dialog.text = ""+ PChar.name+ ", 我告诉过你, 我们现在命运相连。 你的命运就是我的命运。 我们什么时候出发? ";
			link.l1 = "很高兴听到你这么说。 等我们去的时候我再详细告诉你。 我们需要做些准备。 ";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "我准备好了, 我的船长! 我会跟随你到天涯海角! ";
			link.l1 = "谢谢你, 我的爱人... ";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// 在宝藏岛
		case "islatesoro":
			dialog.text = "哦, " +pchar.name+ "! 很高兴见到你! 你在宝藏岛做什么? ";
			link.l1 = "和往常一样 - 办事。 只是想顺道看看你。 海伦, 一切都好吗? ";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// 杰森 比黄金更珍贵
		case "GoldenGirl":
			dialog.text = "我们最亲爱的总督怎么了, 船长? 这次我们要踢谁的屁股? 西班牙人。 海盗, 还是更糟的人? ";
			link.l1 = "更糟的, 海伦, 糟得多。 总督打算拜访一位昂贵的交际花, 我要作为奇人陪同。 他答应他的情妇带一个真正的私掠者。 冒险家, 总之是个海上猛男。 所以我要面对无聊的谈话。 高价的葡萄酒和乏味的贵族。 ";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "恰恰相反, 是参加一个由贵妇人举办的愉快社交活动。 大人让我惊讶地邀请我陪同, 但说实话, 能暂时从工作中解脱出来我很高兴。 ";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "是啊... 所以令人生畏的查尔斯.德.莫尔船长会打扮得像只宠物猴子, 供他们取乐? 多可爱! 我有个更好的主意。 我们扬帆起航, 离开这里。 如果你想度个应得的假期, 我们就去宝藏岛。 我们在那里总是受欢迎的。 日光浴。 白沙滩。 老朋友。 朗姆潘趣酒, 放松心情 - 你说了算。 ";
			link.l1 = "听着, 这一切听起来棒极了, 我也很想去... 但稍后吧。 我答应了总督, 这件事对老人很重要, 而且... ";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "而且什么? 你认为你的贵族血统对他们来说很重要? 我可能没有法国血统, 但我了解他们的'上流社会', 对他们来说, 查尔斯.德.莫尔不是一个人们追随并以生命相托的船长。 他不像他们那样是绅士。 真正的绅士不会出海, 不会在火药烟雾中战斗。 查尔斯.德.莫尔只是他们餐桌上的一个新奇点缀。 就像宠物豹或穿着盛装的家奴! 一个花哨的玩具! 你什么时候开始接受这种待遇了? ! ";
			link.l1 = "海伦, 请冷静。 我相信为了总督的满意和我们未来的繁荣, 我能应付一些不舒服的目光。 有强大的朋友是好事。 毕竟, 这比带领登船队容易! 而且这些'无用之辈'并不总是那样。 即使在上流社会也有值得尊敬的人... 至少应该有。 ";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "随便。 (甩了甩头发) 但警告你 - 我绝不会挤在华丽的礼服里。 如果你让我去, 我就穿我的马裤。 我才不在乎加勒比所有的贵妇人是否会因不满而晕倒。 ";
			link.l1 = "我没打算让你去。 我们俩都受苦没意义。 我会熬过这个派对, 然后我们就去宝藏岛。 作为款待, 我在货舱里藏了一箱极好的西班牙马德拉酒... ";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "哦嗬嗬, 查尔斯! 你是说我不适合这样的上流社会? 穿马裤的女孩会毁了你的夜晚? 真有趣。 好吧, 但别忘了把自己打扮成花花公子。 穿华丽衣服的猴子甚至能打动交际花的心。 表演愉快! ";
			link.l1 = "海伦, 等等! 该死的... 女人! ";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "是啊, 我们确实该休息了。 但该死的, 我才不会为了这个穿华丽的礼服。 你认为关于你女人穿得像男人和水手的流言会传多远? ";
			link.l1 = "啊... 我觉得这不是个好主意。 我该怎么说... 这不是男人带妻子或体面女士参加的活动... ";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "哈! 妓女和堕落! 太好了 - 所以你要去参加狂欢! 那你为什么不直接说呢? 你很幸运, 我不是那种爱吃醋的女人, 不会当场开枪打死你。 至少现在不会。 ";
			link.l1 = "海伦, 求你了, 我只是陪同我们的总督, 他请求我, 而且非常坚持。 不会有什么该死的交际花\n等等, 说岔了... 我是说不会有和交际花鬼混... 哦该死! 我只是去表示敬意! ";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "我建议你穿得时髦些去'表示敬意', 德.莫尔船长。 这是上流社会。 不戴领圈和袖口去那里简直是丑闻。 即使是参加狂欢。 玩得开心。 ";
			link.l1 = "海伦, 等等! 该死的... 女人! ";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "袖口和领圈, 船长。 也许还有蕾丝。 我听说又流行起来了。 但我懂什么呢! ";
			link.l1 = "哦, 海伦, 得了吧! ";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "看看这个! 我亲爱的船长, 从狂欢中回家了! ";
			link.l1 = "... ";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "当地的绅士们还认可他们的新猴子吗? 他们说它昨晚的表演堪称传奇! 赌船赌女人, 向出身高贵的公子哥挑战决斗? 你能解释一下你到底怎么了吗? ";
			link.l1 = "海伦, 让我解释! 没那么简单。 该死, 我很抱歉, 但我从没想过要在博托夫人那里过夜。 我只是睡在那里, 是的, 我发誓是一个人! 而且, 我确实在牌桌上赢了一艘护卫舰。 想象一下? ";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "好吧! 你要么是个伟大的骗子, 要么是个圣人, 要么是个傻瓜。 我们稍后再讨论你赢的女人和船 - 现在告诉我决斗的事, 为什么每个人都在八卦你挑战了一位王储? ";
			link.l1 = "不是王储, 只是一个伯爵的私生子。 他是一位非常有影响力的贵族, 德.列维.万塔杜尔伯爵的儿子。 听着, 不是我先挑事的! 是他先挑战我的, 现在我必须在决斗中获胜, 同时不能太伤害他, 以免惹他父亲生气。 ";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "哦,'只是一个伯爵的儿子'是吗? 查尔斯, 你现在是认真的吗? ! 我们该怎么做? 如果他作弊怎么办? 他会杀了你的! ";
			link.l1 = "这就是为什么大人给我派了贵族副手。 我只带他们去 - 如果事情搞砸了, 至少我能证明一切都符合决斗准则和法律。 我走的时候请你照看一下那艘护卫舰。 ";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "让我理清一下... 你离开一整天一夜, 在牌桌上赢了一个妓女和一艘护卫舰。 现在, 你要和一个你不能杀的贵族混蛋决斗, 而*我*只能坐在这里等? 你让我怎么想? ! ";
			link.l1 = "海伦, 听着, 你完全有理由生我的气, 我很抱歉, 但这只是... ";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "你知道吗, 我受够了。 你去做你的事吧! 我会打扫你的船舱, 洗你的脏衣服! 别以为你就没事了。 等这事结束我们再谈。 我会照看你的新护卫舰, 伟大的德.莫尔船长, 别担心。 哦, 德.莫尔船长, 尽量别死... 因为我打算之后亲手杀了你。 现在失陪, 我要把自己锁在舱房里, 喝掉我在你舱里找到的那瓶好酒。 ";
			link.l1 = "海伦, 让我解释! 靠... 又来! ";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "我听说最新的巴黎时尚要求绅士们在牌桌上赢船和交际花, 而不是买! 此外, 如果想给人留下好印象, 就必须向它们的前主人挑战决斗。 你这次又惹了什么麻烦? ! ";
			link.l1 = "海伦, 没那么简单。 该死, 我很抱歉, 但我从没想过要在博托夫人那里过夜! 昨晚变成了一场耗尽心力的智力较量。 是的, 我在牌桌上赢了一艘该死的护卫舰。 想象一下? ";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "太好了。 意思是你还赢了一个交际花? 你拿什么赌的那艘护卫舰? 不是我们的船吧, 你不会... ";
			link.l1 = "我不得不。 看, 现在不重要了, 最后我赢了。 我的对手挑战我决斗, 指控我作弊。 他是一位极有影响力的贵族, 德.列维.万塔杜尔伯爵的私生子。 这意味着我必须尽力不杀他, 也不把他伤得太重。 ";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "他会同样手下留情吗? 查尔斯, 你疯了吗? 为了某个别的女人, 拿你的船。 你的生命冒险? 她真的值得吗? 我对你就毫无意义吗? ! ";
			link.l1 = "海伦, 没有理由吃醋, 我发誓。 事情就是这样。 我不得不这么做, 总督给我派了贵族军官作为副手, 确保一切按规则进行。 我不能带你或我们的人去。 我走的时候请你照看一下那艘护卫舰。 ";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "太棒了! 首先, 你和陌生女人去参加狂欢, 第二天早上才回来, 我甚至没为此揍你。 现在, 你告诉我几乎在牌桌上输了我们的船, 却赢了一个交际花! 现在你要为她的'荣誉'和某个出身高贵的混蛋决斗, 而你甚至不能杀他! 你让我怎么想? 告诉我。 ";
			link.l1 = "海伦, 听着, 你完全有理由生我的气, 但让我解释... ";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "你知道吗, 我受够了。 去打你那该死的决斗吧。 我会照看你的新护卫舰, 伟大的德.莫尔船长, 别担心。 现在失陪, 我要把自己锁在舱房里, 喝掉我在你舱里找到的那瓶好酒。 但如果你出了什么事, 我向上帝发誓, 我会让这个城镇天翻地覆, 我会把这个妓院和你敬爱的大人的宫殿一起埋葬! ";
			link.l1 = "海伦, 会没事的, 相信我... 等等, 你要去哪里? ! 靠! 又来... ";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "查尔斯, 你得解释一下。 你能告诉我到底发生了什么吗? 我没设好警戒, 伙计们在喝酒... 一些恶棍袭击了我们的船, 趁我们睡觉时把我们绑了起来。 然后那些肮脏的混蛋开始问我, 你会为救我做到什么地步。 最后, 他们把我锁在货舱里。 我都数不清等了多少天了! ";
			link.l1 = "那个混蛋想报复我让他蒙羞。 我担心他会对你做什么! 谢天谢地你没事! ";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "我猜你为了救我不得不做了些什么? 一些不好的事, 对吗? ";
			link.l1 = "重要的是你回到我身边了。 我辜负了你, 海伦。 非常抱歉! 希望你能从心里原谅我! ";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "已经原谅了。 我有很多时间思考我说的话... 我也很抱歉, 查尔斯。 如果我没有那么在意你和那个侯爵的交易, 那天晚上我就会设好警戒, 我就会保持警惕。 啊! 我真是个没用的女人! ";
			link.l1 = "别这么说, 过去的就让它过去。 我爱你, 我再也不会离开你了。 我保证! ";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "我想, 我最好还是不知道你具体做了什么, 对吗? 好吧, 我们又在一起了, 这才是最重要的。 ";
			link.l1 = "我对你没有秘密。 我会告诉你... ";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("一段时间后... ", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "真是一团糟... 我知道你别无选择, 但怎么向迪卢.帕克斯和他的朋友们解释? 我是说, 你现在成了罪犯! ";
				link.l1 = "我选择付出这个代价, 但我真的别无选择。 别担心, 我会找到办法弥补, 恢复我们的好名声。 如果不行, 宝藏岛永远欢迎我们! 有你在我身边, 我能应付。 ";
			}
			else
			{
				dialog.text = "查尔斯, 真是个故事... 我相信你别无选择, 但接下来会怎样? 那个英国人会主持公道, 还是会开战? 你确定不想去巴斯特尔见证他们给那个混蛋戴上锁链? ";
				link.l1 = "你知道吗, 海伦, 两周前我绝不会错过。 但今天我要说去他的! 我甚至不再关心他是否得到应有的惩罚。 我们又在一起了, 这才是最重要的! ";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "你知道我会永远在你身边。 哈! 这不是你我第一次陷入困境。 我们会再次成功的。 ";
				link.l1 = "没错。 我们起航吧, 亲爱的! 地平线在等待我们! ";
			}
			else
			{
				dialog.text = "我喜欢你的想法, 查尔斯! 不再有贵族: 法国人。 英国人。 西班牙人 - 不管是什么。 我想我们该度个假了! ";
				link.l1 = "同意。 只有你和我! 不再有总督和出身高贵的混蛋! ";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "是, 船长! ";
				link.l1 = "";
			}
			else
			{
				dialog.text = "听起来很棒! 我去告诉伙计们该起锚了! 还有查尔斯... ";
				link.l1 = "我知道, 海伦, 我知道。 我马上就来。 ";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "查尔斯, 你做到了! 葡萄牙人把一切都告诉我了! 真是个故事! ";
			link.l1 = "谢天谢地, 你还活着, 海伦! 你不知道再次见到你我有多高兴! ";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "说到这个。 你答应过要告诉我一些事, 记得吗? 一些重大而复杂的事。 现在是你的机会, 船长。 到底发生了什么? ! ";
			link.l1 = "我爱你, 海伦。 剩下的都不重要了。 ";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "是啊, 这很有帮助, 但是... 该死, 我也是, 查尔斯。 我也爱你。 我的上帝, 我太想你了! ";
			link.l1 = "我也是。 跟我来, 今晚即使天塌下来砸在这个悲惨的小镇上, 我也不会离开你。 我再也不会离开你了。 永远。 ";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "我想, 我最好还是不知道你具体做了什么, 对吗? 是啊, 我们又在一起了, 这才是最重要的。 ";
			link.l1 = "我对你没有秘密。 我会告诉你... ";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("一段时间后... ", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "难以置信! 你是说因为我, 法国和英国正处于战争边缘? ";
			link.l1 = "不, 海伦。 是因为我做了一个非常糟糕的判断。 但我必须把你带回来, 弥补一切。 ";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "这一切都很感人很浪漫, 我甚至准备忘记这一切最初是怎么开始的。 几乎准备好。 但说真的, 他们逮捕你是因为葡萄牙人给了那艘该死的双桅帆船一个错误的名字? ";
			link.l1 = "恰恰相反, 他给了我正确的名字! 我希望知道他是怎么做到的, 为什么。 顺便问一下, 他本人在哪里? ! ";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "他走了。 他带我来这里后就走了。 我不想用你赢的交际花的'款待', 所以让巴塞洛缪给我租了个房间。 他付了钱, 没说一句话就消失了。 实际上等等, 不, 他确实给你留了一封信! ";
			link.l1 = "一封信? 来自葡萄牙人巴塞洛缪? 这是新情况。 我不喜欢事情朝这个方向发展... ";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "对, 我把信留给你在这里读, 我去和伙计们打个招呼。 他们一定很担心。 我从没想过我会想念那些忧郁沮丧的面孔! 同时尽量别再惹上另一场灾难! ";
			link.l1 = "该死... 我还是不敢相信我把你救回来了! ";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// 杰森 长长久久
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "白沙滩, 清澈的绿水, 你, 我, 还有美酒 - 查尔斯, 这太浪漫了! 我们应该经常这样一起散步, 好吗! ";
			link.l1 = "很高兴你喜欢。 我想我们现在应该多花时间这样做。 ";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "查尔斯, 你在做什么, 为什么跪着? 太突然了... ";
			link.l1 = "海伦, 我爱你。 我想和你共度上天赐予我的每一天。 因此, 在这里, 在大海和天空面前, 我请求你 - 海伦.Beatrice Sharp - 给我荣幸, 在上帝和众人面前与我相守, 直到死亡将我们分开。 我, 查尔斯.德.莫尔, 蒙佩尔骑士, 问你 - 你愿意嫁给我吗? ";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "你知道, 我从不喜欢这些形式, 但我会陪你到世界的尽头。 至于你的问题, 答案是... 哦, 抱歉, 我洒了! ";
				link.l1 = "没关系, 只是酒, 我从不喜欢这件衬衫... ";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "查尔斯, 当然愿意! 愿意, 愿意, 还是愿意!!! 但我希望你不打算让我们退休到某个尘土飞扬的家族城堡里种萝卜, 直到生命尽头? ";
				link.l1 = "嗯, 我们确实有一座家族城堡, 但它不 dusty, 我们也不会待在那里。 我们的生活是自由, 地平线在我们指尖! ";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//关闭地点
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "那就为你干杯, 我的船长, 我的丈夫, 为我们的婚礼! ";
			link.l1 = "为你干杯, 我的爱人! 为我们在一起的未来, 有太多等待我们! ";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "那就为你干杯, 我的船长, 我的丈夫, 为我的婚礼! ";
			link.l1 = "为你干杯, 我的爱人! 为我们在一起的未来, 有太多等待我们! ";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "所以, 本诺特神父回来了, 准备为我们主持婚礼。 但你要知道, 即使是这种场合我也不会穿裙子! 你认为我穿马裤会引起轰动吗? ";
			link.l1 = "海伦, 我爱你穿任何衣服, 他们会适应的。 首先我想和你商量一下客人和仪式。 ";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "是啊, 有个问题 - 我们大多数想与之分享这一天的好朋友都不允许进入城市, 更别说教堂了。 因此 - 我们按预期在这里和重要人物举行婚礼, 然后我们扬帆去宝藏岛, 和我们真正的朋友举行一个合适的庆祝活动, 你觉得怎么样? ";
			link.l1 = "我觉得很好! 我会和本诺特神父谈谈, 但我们需要发出邀请, 还有更多... ";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "冷静点, 船长。 你亲爱的未来妻子会分担一部分负担! 我会在宝藏岛安排一切, 给我们的朋友写信, 告诉我: 你想要多大的婚礼? ";
			link.l1 = "只有你。 我和我们最亲密的朋友。 毕竟在马提尼克这里的官方排场之后, 我们会想要一些真诚的亲密。 ";
			link.l1.go = "LongHappy_10";
			link.l2 = "每个人都必须记住这一天! 叫上所有人! 一个都不能少! ";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "舒适友好 - 你读懂了我的心思! 我们必须访问夏普敦, 我会准备好一切。 我想五十桶朗姆酒和二十几桶葡萄酒就够了。 另外, 食物和娱乐需要三十万八里亚尔。 ";
			link.l1 = "提醒我 - 为什么你不再管理船上的财务? 我会弄到所有东西。 只是快速拜访一下神父, 然后我们起航去夏普敦。 ";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "所以, 你想办一个真正的海狼派对? 好吧! 我们必须访问夏普敦, 我会准备好一切。 我们得大量储备 - 我想一百桶朗姆酒和五十桶葡萄酒就够了。 其他费用至少需要五十万八里亚尔。 ";
			link.l1 = "你是在邀请整个海岸兄弟会吗? 哦, 该死, 就这样吧! 我会弄到物资。 只是快速拜访一下神父, 我们就起航去夏普敦。 ";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "查尔斯, 那我负责装货, 然后把邀请函交给男爵, 并和酒吧老板谈妥。 应该不会太久。 ";
			link.l1 = "别担心, 亲爱的, 我会找点有意义的事做... 或者就在沙滩上打个盹。 上帝啊, 我没想到策划自己的婚礼比突袭托尔图加还难。 ";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("几小时后... ", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "查尔斯, 你休息了吗? 有好消息和坏消息。 坏消息是当地人上周玩得太开心, 不小心把该死的'老啄木鸟'酒馆烧掉了! 好消息是, 男爵承诺在我们回来时, 它会被重建得比以前更大更好。 我已经安排好了, 我们可以起航了。 ";
			link.l1 = "希望我们的婚礼不会在离开时给镇上留下类似的一堆灰烬。 真遗憾, 我很喜欢'老啄木鸟'- 舒适。 私密, 只有一丝呕吐物和麻絮的味道! 哦, 好吧, 亲爱的, 你说得对 - 我们该走了。 ";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "扬已经和格拉迪斯在镇上了, 你能想象吗? 我没想到他们会来参加我的婚礼! 哦, 天哪! 即使在那个可怕的印第安神庙城市, 我也没有现在这么害怕! ";
			link.l1 = "一切都好, 亲爱的, 一切都好。 我也很担心 - 紧张是正常的。 既然客人已经到了, 我该去找本诺特神父, 问问仪式什么时候开始。 ";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "这将是漫长而艰难的一天... 我要去见扬和格拉迪斯。 ";
			link.l1 = "很高兴他们能来。 老斯文森像爱自己的女儿一样爱你, 麦卡瑟夫人更是如此。 他们今天能来真好。 去吧, 别担心 - 一切都会好的。 ";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//禁止等待
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = "是的。 ";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "是的。 ";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "是的。 ";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "我, 查尔斯.亨利.德.莫尔, 蒙佩尔骑士, 娶你, 海伦.Beatrice Sharp, 为我的妻子, 从今日起, 无论顺境逆境, 富贵贫穷, 健康疾病, 直至死亡将我们分离。 我以上帝的圣法为证, 在上帝面前许下此誓。 ";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "我, 海伦.Beatrice Sharp, 嫁给你, 查尔斯.亨利.德.莫尔, 为我的丈夫, 从今日起, 无论顺境逆境, 富贵贫穷, 健康疾病, 直至死亡将我们分离。 我以上帝的圣法为证, 在上帝面前许下此誓。 ";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "阿门。 ";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "海伦.Beatrice.德.莫尔, 蒙佩尔夫人 - 哦, 我喜欢这个称呼, 我最亲爱的丈夫! ";
			link.l1 = "没有比这更好的了, 我的妻子! ";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "你知道吗 - 我原以为这不会改变什么, 或许确实没有 - 我以前就爱你, 想和你共度余生, 但今天, 这场神圣的仪式... 查尔斯, 我真的很幸福! 从未如此幸福, 看看格拉迪斯和扬 - 他们容光焕发! 周围有这么多幸福的面孔! 顺便说一句 - 现在你该去拜访客人, 接受他们的祝贺了。 结束后回来, 别忘了 - 我们在夏普敦等着呢。 ";
			link.l1 = "我马上就去, 亲爱的。 走之前亲一个! ";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "你好, 丈夫, 你已经和客人谈过了吗? ";
			link.l1 = "还没有, 耐心点, 妻子, 我很快就回来。 ";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "是的, 我从未一次性听过这么多祝贺。 你知道吗 - 我觉得他们大多数人都是真诚的! ";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "是的, 这些贵族出人意料地真诚 - 说实话, 我预期会有更多虚假和虚伪。 或者只是我太幸福了, 什么都没注意到。 但毕竟, 我们的朋友在夏普敦等着我们! 我们什么时候起航? ";
			link.l1 = "现在就走。 我们将乘着鹰的翅膀直奔友好的盛宴。 我希望我的妻子不介意在我们的船舱里度过今晚? ";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "哦, 是的, 我的丈夫, 你太浪漫了! 别这么紧张, 现在我有权在公共场合吻你... 是的, 我们现在就走! ";
			link.l1 = "领航员, 设定前往夏普敦的航线, 无论发生什么都不要打扰我们! 就算幽灵舰队向我们驶来我也不在乎! ";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "哦, 我亲爱的丈夫, 我太幸福了! 今天是美好的一天... ";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "来吧, 查尔斯。 这个骗子还没落地就会死! ";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "我没事, 查尔斯, 没关系。 内森怎么样? ";
			link.l1 = "这么多血... 丹妮, 他还在呼吸吗? 我看到他在呼吸! ";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "快点, 亲爱的, 别浪费时间! ";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "查尔斯, 你没事吧? 真是一场血战! 抱歉, 我们被困在楼上, 有十几个混蛋, 所以我不得不先解决他们! ";
			link.l1 = "没事, 我处理了。 很高兴终于了结了雅克的事... 他罪有应得。 ";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "好的, 亲爱的, 我们结束这里的事然后回去。 我一直在想内森, 他怎么样? 他为我挡了那颗子弹! ";
			link.l1 = "你说得对, 甜心, 我也担心。 走吧, 我就在你后面。 ";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "我们找到马库斯了! 他在货舱里, 被绑着, 失去了意识。 ";
			link.l1 = "他还活着? ";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "别担心, 亲爱的, 泰雷克斯男爵会比我们活得更久。 他刚醒过来, 已经在嚷嚷了, 他不停地要朗姆酒。 他的军刀和桥 - 按这个顺序。 ";
			link.l1 = "那才是我们的老马库斯! 让他休息一下, 我们结束这里的事然后回岸边。 ";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "我很抱歉, 亲爱的... 先是我们忠实的朋友提钦吉图, 现在是吉诺... 巴尔巴宗早就该为他所做的一切死十几次了! ";
				link.l1 = "唉, 我只杀了他一次。 我也很难过... 但我们赢了, 他再也不能伤害任何人了。 ";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "查尔斯, 我为吉诺感到很难过! 当我发现时, 我简直不敢相信! 你怎么样, 亲爱的? ";
					link.l1 = "我也不敢相信... 怎么会这样... 我没想到今天会是这样的结局。 ";
				}
				else
				{
					dialog.text = "我在想, 未来的历史学家会写关于私掠者湾的伟大战役吗? 海岸兄弟会的男爵们公开交战的那一天 - 我打赌西班牙海岸警卫队正在感激涕零! 但是, 我们又赢了! 我们的朋友还活着, 我们的敌人死了 - 一份光荣的结婚礼物! ";
					link.l1 = "是啊, 这样的庆祝, 但我们做到了, 我的天使。 我们做到了。 ";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "来吧, 丹妮在镇外给我们找了间房子, 我现在不想回船上, 直到它被清理干净。 我们坐下来, 为那些没能挺过来的人干一杯。 ";
			link.l1 = "好的, 海伦, 我们走吧。 ";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "查尔斯, 我为吉诺感到很难过! 当我发现时, 我简直不敢相信! 你怎么样? ";
				link.l1 = "我也不敢相信... 怎么会这样... 我没想到今天会是这样的结局。 ";
			}
			else
			{
				dialog.text = "你看到霍克了吗? 当吉诺说'危险结束了'时, 丹妮让我出来了。 我很高兴一切都好。 我们的朋友还活着, 我们的敌人死了 - 一份光荣的结婚礼物! ";
				link.l1 = "我也是, 亲爱的。 我们赢了。 巴尔巴宗死了, 男爵们在集结他们剩下的船员。 战斗结束了。 ";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "查尔斯, 我看你都快站不住了, 但我去了酒馆, 你不会相信我从酒保那里听到了什么。 ";
			link.l1 = "是啊, 我从扬那里也听说了, 他也去过。 在我看来, 我们亲爱的印第安人已经踏上了战争之路。 我们去萨博-马蒂拉峡走走吧, 有人看到他朝那个方向去了。 ";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "我的上帝! 这才是精神, 提钦吉图! 呼, 我笑得屁股都快掉了! 为什么我们欧洲人不也采用这样的习俗呢? ! 哦, 查尔斯, 你几乎站着睡着了! 来吧, 丹妮在镇外给我们找了间房子 - 你需要休息一下。 ";
			link.l1 = "带路吧... 我想我以前在那个海滩上睡过。 ";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "tonzag_jailed":
			dialog.text = "... 没事。 ";
			link.l1 = "听到这个很高兴。 ";
			link.l1.go = "exit";
			link.l2 = "真的吗? ";
			link.l2.go = "tonzag_jailed_1";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "是的。 ";
			link.l1 = "听到这个很高兴。 ";
			link.l1.go = "exit";
			link.l2 = "得了吧, 我看得出你有心事! ";
			link.l2.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "我完全没事, 别管了! \n查尔斯, 去死吧! 我讨厌地牢, 我讨厌你, 我讨厌这个该死的岛! 马上带我离开这里! \n抱歉... 我真的不喜欢地牢, 别碰我! ";
			link.l1 = "对不起。 我们都有害怕的东西。 ";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "啊啊啊! 让我们离开这里! 查尔斯, 做点什么! ";
			link.l1 = "振作起来! ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "我的船长, 敌人在第二层甲板突破了船体, 并派出了登船队。 全船都在激战, 大多数炮手都被击倒了! 我们需要营救我们的船员和赫拉克勒斯! 你去, 还是我去? ";
			link.l1 = "这次我自己去, 海伦! 你指挥船, 让我们离开这里! ";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "是, 我的船长。 我不会让你失望的, 你也请小心! ";
			link.l1 = "我知道, 海伦。 你也小心! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "胜利了, 我的船长! 登陆队已被消灭, 敌人选择撤退, 向南驶去。 船的状况尚可。 幸存船员: " + GetCrewQuantity(pchar) + "人。 报告完毕! ";
			link.l1 = "谢谢你, 海伦, 还有什么... ";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "脱衣服吧, 胜利者, 你的奖赏是对我为所欲为! ";
			link.l1 = "呃... ";
			link.l1.go = "tonzag_after_victory_2";
			link.l2 = "我们走! ";
			link.l2.go = "tonzag_after_victory_2";
		break;
		
		case "tonzag_after_victory_2":
			dialog.text = "哦, 嗨, 赫拉克勒斯。 抱歉, 你撞见我们了! 但该死的, 很高兴看到你活着, 浑身是别人的血 - 这是你的自然状态, 嗯? ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog");
		break;
		
		case "tonzag_after_victory_3":
			dialog.text = "";
			link.l1 = "好吧, 海伦, 你真了不起! ";
			link.l1.go = "tonzag_after_victory_4";
		break;
		
		case "tonzag_after_victory_4":
			dialog.text = "我还没开始呢, 我的船长。 我们庆祝一下? ";
			link.l1 = "不需要说服我! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "别看, 别看, 别看... 这是另一个世界, 我的船长! 不可能是这样的! ";
			link.l1 = "我想现在这就是我们的世界了, 亲爱的。 你说得对, 我们别待在这儿... ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
		break;
		
		// 杰森 莫纳岛
		case "IslaMona":
			dialog.text = "恐怕这场流行病正在影响你的女孩们, 罗德里戈。 让她们忙于编织或其他什么吧! ";
			link.l1 = "这次谈话显然毫无进展。 我们约定明天去教堂。 去祈祷... 当然。 ";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "我为你骄傲, 我的爱人! ";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "好吧, 查尔斯... ";
			link.l1 = "海伦, 你又在想什么? ";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "加勒比海最声名狼藉的夫妇拥有两个完整的岛屿! 我的宝藏岛海盗天堂和你的应许之地 - 你认为当文明最终来到西印度群岛时, 它们能持续多久? ";
			link.l1 = "足够持续我们一生, 亲爱的。 之后呢? 我们无法控制那时发生的事。 其他人会讲述我们的故事。 最重要的是你和我此时此刻在一起, 幸福快乐。 ";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "说到幸福... 我现在要上楼了: 我需要点蜡烛, 整理床铺, 也许写日记... ";
			link.l1 = "我在这里再待一会儿, 然后上来帮你'整理床铺'。 ";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "别待太久... ";
			link.l1 = "";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("LoveSex_Classic", 2.5);
			NextDiag.CurrentNode = "sex_after";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "drinking_refuse":
			dialog.text = "你真的那么忙吗? 太遗憾了, 但我理解。 我会找点别的事做。 ";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
			
			pchar.questTemp.HelenDrinking.Result = "no_visit";
			CloseQuestHeader("HelenDrinking");
		break;
		
		case "drinking_accept":
			dialog.text = "很高兴你还记得。 我想告诉你我非常感激。 不是每天都有人把你从... 你知道的事情中救出来。 我们去喝一杯吧。 我请客。 ";
			link.l1 = "海伦... 格拉迪斯会怎么说? ";
			link.l1.go = "drinking_accept_1";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToHouse");
		break;
		
		case "drinking_accept_1":
			dialog.text = "真有趣, 查尔斯。 来吧, 别惹我生气。 ";
			link.l1 = "这是约会吗? ";
			link.l1.go = "drinking_accept_1_1";
			link.l2 = "来了, 没必要发脾气。 ";
			link.l2.go = "drinking_accept_1_2";
		break;
		
		case "drinking_accept_1_1":
			dialog.text = "哈哈! 你想多了! 我得喝得酩酊大醉才行! ";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_accept_1_2":
			dialog.text = "这才对。 ";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_in_tavern":
			dialog.text = "";
			link.l1 = "... 她有很多优点, 但就是酒量不行。 我们就是这样认识的。 ";
			link.l1.go = "drinking_in_tavern_1";
			link.l2 = "... 我父亲坚持要我服兵役。 我屈服了, 带着一封推荐信去了巴黎。 但我从未到达指定地址, 成了一名艺术家。 ";
			link.l2.go = "drinking_in_tavern_2";
		break;
				
		case "drinking_in_tavern_1":
			dialog.text = "啊, 现在我明白你说的优点是什么了。 她叫什么名字? ";
			link.l1 = "露露。 ";
			link.l1.go = "drinking_in_tavern_1_1";
		break;
		
		case "drinking_in_tavern_1_1":
			dialog.text = "露露... 听了你这些故事, 你完全毁了我对巴黎的印象。 我以为那是一个奢华生活的城市, 但听起来像个大妓院。 ";
			link.l1 = "你谴责妓院吗? ";
			link.l1.go = "drinking_in_tavern_1_2";
		break;
		
		case "drinking_in_tavern_1_2":
			dialog.text = "是的, 船长, 而且我不理解去那里的男人。 ";
			link.l1 = "(盯着杯子)";
			link.l1.go = "drinking_in_tavern_1_4";
			link.l2 = "(剧烈咳嗽)";
			link.l2.go = "drinking_in_tavern_1_4";
			link.l3 = "呃... 各有所好... 我想? ";
			link.l3.go = "drinking_in_tavern_1_4";
		break;
		
		case "drinking_in_tavern_1_4":
			dialog.text = "(笑) 哈! 你该看看你的表情! 害怕了? 我们再干一杯! 为巴黎! ";
			link.l1 = "为巴黎! ";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_2":
			dialog.text = "(笑) 你? ! 一个艺术家? 所以, 英国舰队的骄傲。 强奸犯。 混蛋多诺万, 死在了一个巴黎艺术家的手里? 啊, 真遗憾你登船时没穿你那件崭新的花边领, 没用手杖揍那个混蛋! ";
			link.l1 = "是啊, 太遗憾了。 那天花边装饰领刚好在洗。 ";
			link.l1.go = "drinking_in_tavern_2_1";
		break;
		
		case "drinking_in_tavern_2_1":
			dialog.text = "(笑) 好吧, 谢谢你, 查尔斯。 我不知道今晚剩下的时间会怎样, 但这个晚上已经很棒了。 我甚至可能允许你给我画肖像。 但是, 注意, 不要用你画巴黎女孩的那种风格! ";
			link.l1 = "哈! 那得看我是否同意画你。 ";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_3":
			dialog.text = "抱歉, 我的船长, 听你讲述冒险经历和贵族... 男女交际花的生活。 真见鬼, 我永远不会相信你找不到更有价值的事情来打发时间! 别告诉我你所做的只是涂抹画布和挥霍爸爸的钱。 如果是那样, 你和我们在一起一天都活不下去。 ";
			link.l1 = "我有... 其他追求。 ";
			link.l1.go = "drinking_in_tavern_" + pchar.HeroParam.HeroType;
		break;
		
		case "drinking_in_tavern_herotype_3":
			dialog.text = "";
			link.l1 = "我把宫廷生活和军事服务结合起来, 但不是... 呵呵, 当然不是我父亲想要的方式。 几次跳窗逃跑和一次斗殴 - 我就和卫兵成了朋友。 当然我也学到了很多东西, 磨练了身体。 老战友教我如何承受打击。 穿盔甲。 使用剑, 以及适当放松。 最后一部分当然特别适合我。 你不会相信, 不是每个人都能从早到晚挥剑, 然后从中午喝到第二天早上。 ";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_1":
			dialog.text = "";
			link.l1 = "想想看, 一个名声不好。 钱包空空的贵族在首都容易吗? 第一天就把爸爸的推荐信弄丢了。 我不得不证明自己, 不让任何人嘲笑我。 家里的击剑课没有忘记, 我对任何侧目都用决斗回应。 然后我真的沉迷其中。 不过, 我从未杀过人, 在遇到一个能终结我的有经验的战士之前, 我设法离开了巴黎。 ";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_4":
			dialog.text = "";
			link.l1 = "在墓地花了很多时间。 别想歪了 - 这只是我社交圈的流行爱好。 为了勇气, 我们会在晚上去墓地, 把空瓶子放在篱笆上, 在计时器响时射击。 一晚上我们会浪费一百发子弹和一箱香槟。 现在当然, 我为这种行为感到羞耻, 但那时赢家会拿到一大笔奖金, 并从宫廷的女性那里得到一些... 青睐。 所有东西都被使用 - 我甚至还尝试了一点火药混合物。 但为什么我们中没有人想到学习如何制作纸 cartridges - 我永远不会知道。 ";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_2":
			dialog.text = "";
			link.l1 = "学习, 而且相当勤奋 - 甚至差点进入索邦大学。 在办公室工作到厌倦, 总之 - 什么都做了一点。 老师是我父亲的老朋友, 更喜欢实践而非理论, 所以我从各个方面了解了巴黎, 与不同的人交谈: 从强盗到贵族。 所有这些最终在这里都派上了用场。 ";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_4":
			dialog.text = "还有... 就这样? 所以你身上还有东西, 我的船长。 一些你自己还没看到的东西。 为你干杯! ";
			link.l1 = "干杯! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernChange");
		break;
		
		case "drinking_my_background":
			dialog.text = "";
			link.l1 = "告诉我你的故事, 海伦。 我在首都的冒险与一个三十岁以下的女孩指挥一艘有一百人的纵帆船相比, 简直不值一提。 ";
			link.l1.go = "drinking_my_background_1";
		break;
		
		case "drinking_my_background_1":
			dialog.text = "刚三十岁以下, 嗯, 查尔斯? 为了这句有力的评论, 你得买下一轮! 我所有的人都死了, 我再也不指挥纵帆船了。 坦白说, 我不知道是否还会再指挥。 ";
			link.l1 = "对不起, 海伦。 不是有意触痛你的神经。 但为什么你认为你的船长生涯结束了? ";
			link.l1.go = "drinking_my_background_2";
		break;
		
		case "drinking_my_background_2":
			dialog.text = "因为我的船员死了, 另一个船员永远不会接受我。 唉! 好吧, 我的船长, 你已经告诉我很多你的生活; 现在轮到我了! 真相不在这个杯子底, 所以我们别再故弄玄虚了。 ";
			link.l1 = "";
			link.l1.go = "drinking_my_background_3";
		break;
		
		case "drinking_my_background_3":
			dialog.text = "我的情况, 查尔斯, 很独特。 我父亲是这一带最好的水手之一, 深受森林恶魔的尊敬, 他的船员崇拜他, 他也爱我胜过生命。 ";
			link.l1 = "";
			link.l1.go = "drinking_my_background_4";
		break;
		
		case "drinking_my_background_4":
			dialog.text = "拿走其中任何一样, 他要么会把我送到伦敦生活在... 文明中, 要么让我像我母亲一样在这里枯萎。 起初一切都很顺利: 我想要自由, 真正的自由, 查尔斯, 熟练指挥一艘有忠诚船员的战船正好能给你自由。 我父亲给了我他所能给的一切。 我十二岁就和他出海, 头六个月在货舱里追老鼠, 之后才被允许和水手一起工作。 ";
			link.l1 = "肖恩.麦卡瑟让你当船上的老鼠? 抱歉, 海伦, 但这无法回头了! 船员们怎么接受你? ";
			link.l1.go = "drinking_my_background_5";
		break;
		
		case "drinking_my_background_5":
			dialog.text = "嗯, 也许我为了故事效果稍微夸张了一点? 我父亲的船员接受了我; 他聚集了好人。 但从那以后, 我一直害怕... 货舱和任何狭小黑暗的空间。 哈! 斯文森发现后差点杀了我父亲! ";
			link.l1 = "他对你很重要。 显然他在你的命运中扮演了至少和肖恩一样的角色。 ";
			link.l1.go = "drinking_my_background_6";
		break;
		
		case "drinking_my_background_6":
			dialog.text = "是的。 所有的男爵都直接告诉我父亲他是个傻瓜, 但在我打破船员爬桅杆的记录后, 是森林恶魔给予了他认可并和他握手。 那一刻将永远留在我心中: 船员们的欢呼, 无论我看向哪里, 都是清澈的海平线。 还有我父亲赞许的目光, 我看不见, 但我全心全意地感受到了。 ";
			link.l1 = "我的胜利以第一天去瓜德罗普岛时从索具上掉下来告终。 ";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.TakeFolke")) {
				link.l1 = link.l1 + " 我的舵手德鲁克也有一个很有意味的眼神。 "
			}
			link.l1.go = "drinking_my_background_7";
		break;
		
		case "drinking_my_background_7":
			dialog.text = "啊哈哈! 我可以想象! 别担心, 那是很久以前的事了; 现在你是真正的海狼! ";
			link.l1 = "";
			link.l1.go = "drinking_my_background_8";
		break;
		
		case "drinking_my_background_8":
			dialog.text = "为我们的胜利干杯! ";
			link.l1 = " 好啊! 好啊! ";
			link.l1.go = "drinking_my_background_12";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "... 然后我逐渐晋升, 在父亲和军官的会议上担任船长桌的服务。 学到了很多。 从十五岁开始, 他们带我参加军事行动, 我在第一次战斗中杀了人。 那是一场令人作呕的战役; 我们不该在星期一起航... 真的不该! ";
			link.l1 = "十五岁? 你吓到我了, 海伦。 ";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "我甚至不明白发生了什么。 荷兰商人有他的先头部队 - 公司的雇佣兵。 他们决定大胆反击我们的船尾甲板。 而我, 一个傻瓜, 毫无惧色地伸出了我金色的脑袋。 我立刻被手枪枪托击中。 但在那之前, 我设法把我的细剑插进了某个公司的傻瓜身上。 ";
			link.l1 = "天哪, 肖恩呢? 他怎么没在那之后把你赶上岸? ";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_13":
			dialog.text = "我父亲在那场战斗中也未能幸免, 看到我破裂的傻瓜脑袋肯定也没帮上忙。 他开始慢慢衰落, 可能除了我没人注意到。 然后他就走了。 根据他的遗嘱, 我继承了彩虹号和她的船员, 还有足够维持船一年的资金。 ";
			link.l1 = "船员们接受你作为船长吗? ";
			link.l1.go = "drinking_my_background_14";
		break;
		
		case "drinking_my_background_14":
			dialog.text = "我们不生活在童话里, 我的船长。 有些人对我父亲的遗嘱持敌意 - 事情变得不愉快\n如果有一个水手离开彩虹号, 拒绝在我手下服役, 这对我的形象将非常不利。 但斯文森介入并让每个人都端正了态度。 没有人公开离开船员... 当时。 七年来, 我指挥着我的美人, 为森林恶魔运输可疑货物, 寻找宝藏, 生活... 但现在, 这一切都成为过去了。 ";
			link.l1 = "不是过去。 我相信你注定会再次在自己的旗帜下航行! 我们为此干杯! ";
			link.l1.go = "drinking_my_background_sea";
			link.l2 = "我们可能无法找回船, 但你的细剑还在你身边。 ";
			link.l2.go = "drinking_my_background_land";
		break;
		
		case "drinking_my_background_sea":
			dialog.text = "你知道吗, 当你这样说时, 我也相信了。 我们干杯! ";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_COMMERCE, 5);
			AddCharacterSkill(npchar, SKILL_ACCURACY, 5);
			AddCharacterSkill(npchar, SKILL_CANNONS, 5);
			AddCharacterSkill(npchar, SKILL_SAILING, 5);
			AddCharacterSkill(npchar, SKILL_REPAIR, 5);
			AddCharacterSkill(npchar, SKILL_GRAPPLING, 5);
			AddCharacterSkill(npchar, SKILL_DEFENCE, 5);
			notification("航海技能 +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "sea";
		break;
		
		case "drinking_my_background_land":
			dialog.text = "但我的细剑会给我带来幸福吗? 答案可能在这个杯子底。 我们干杯! ";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_F_LIGHT, 5);
			AddCharacterSkill(npchar, SKILL_FENCING, 5);
			AddCharacterSkill(npchar, SKILL_F_HEAVY, 5);
			AddCharacterSkill(npchar, SKILL_PISTOL, 5);
			AddCharacterSkill(npchar, SKILL_FORTUNE, 5);
			AddCharacterSkill(npchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(npchar, SKILL_SNEAK, 5);
			notification("个人技能 +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "land";
		break;
		
		case "drinking_my_background_15":
			dialog.text = "我一直在想你在欧洲的生活... 看, 你是城市花花公子, 而我只是个普通女孩, 但我们已经在世界上最危险的角落成名了。 ";
			link.l1 = "听起来像是个祝酒词! 那么, 有什么东西把我们联系在一起吗? ";
			link.l1.go = "drinking_my_background_16";
		break;
		
		case "drinking_my_background_16":
			dialog.text = "嗯, 我站在我父亲的肩膀上。 我不知道你怎样, 但也许你的家族也对你有同样的影响? 也许你还没有意识到? ";
			link.l1 = "等我把我亲爱的弟弟从监狱里救出来后, 我会问他的。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernEmpty");
		break;
		
		case "drinking_game":
			dialog.text = "好了, 我的船长。 我们已经交换了故事, 是时候结束今晚了。 ";
			link.l1 = "嗯, 我还希望今晚有个不同的结局。 ";
			link.l1.go = "drinking_game_1";
		break;
		
		case "drinking_game_1":
			dialog.text = "夜晚还没结束。 我建议玩个游戏: 如果你出牌正确, 也许你的祈祷会得到回应。 ";
			link.l1 = "我们要打牌吗? 我加入! ";
			link.l1.go = "drinking_game_2";
		break;
		
		case "drinking_game_2":
			dialog.text = "别着急, 海狼。 我不会和你玩脱衣扑克。 ";
			link.l1 = "是啊, 你说得对, 海伦。 我们在这里没有隐私。 ";
			link.l1.go = "drinking_game_3";
		break;
		
		case "drinking_game_3":
			dialog.text = "这不是我们唯一没有的东西, 查尔斯... 这不是纸牌游戏, 但别担心, 我打赌你是这方面的大师.'我从未'- 听说过吗? ";
			link.l1 = "熟悉。 从前的生活。 你经常玩吗? ";
			link.l1.go = "drinking_game_4";
		break;
		
		case "drinking_game_4":
			dialog.text = "一直想试试, 但没有人一起玩。 ";
			link.l1 = "对于我们第一次一起喝酒来说, 这是个相当大胆的游戏。 你确定吗? ";
			link.l1.go = "drinking_game_5";
			link.l2 = "顺便问一下, 大家都在哪里? 我们单独在这里吗? ";
			link.l2.go = "drinking_game_6";
		break;
		
		case "drinking_game_5":
			dialog.text = "是的, 在最近的事件之后, 我需要活一活。 做些愚蠢的事, 你知道吗? ";
			link.l1 = "不, 这总是以糟糕的结局告终, 伦巴。 ";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "开始吧! 女士优先! ";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_6":
			dialog.text = "把他们都送回家了 - 不需要让外人听到。 ";
			link.l1 = "不, 这总是以糟糕的结局告终, 伦巴。 ";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "我们做吧! 女士优先! ";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_refuse":
			dialog.text = "太遗憾了, 但也许你是对的。 再来一杯? ";
			link.l1 = "开始吧! 女士优先! ";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_refuse_1":
			dialog.text = "我已经安排好了 - 楼上的房间是你的。 它被某个重要的法国军官占用, 但森林恶魔的手下礼貌地请他腾出了地方。 去睡一觉吧 - 我不会让你在这种状态下在街上闲逛, 或者更糟, 出海。 ";
			link.l1 = "遵命, 女士! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToTavernRoom");
		break;
		
		case "drinking_game_accept":
			dialog.text = "哈! 嗝! 意思是, 你先开始! ";
			link.l1 = "小心点, 亲爱的! 嗯。 我从未在货舱里追过老鼠! ";
			link.l1.go = "drinking_game_accept_1";
		break;
		
		case "drinking_game_accept_1":
			dialog.text = "原来如此? 得提防你! (喝酒)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_2";
		break;
		
		case "drinking_game_accept_2":
			dialog.text = "呵! 一想到那个... 好吧, 准备好, 帅哥: 我从未从桅杆上掉下来过! ";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_3";
		break;
		
		case "drinking_game_accept_3":
			dialog.text = "";
			link.l1 = "好样的! 允许我, 小姐, 为你干杯! (喝酒)";
			link.l1.go = "drinking_game_accept_4";
		break;
		
		case "drinking_game_accept_4":
			dialog.text = "";
			link.l1 = "我从未迷信过。 ";
			link.l1.go = "drinking_game_accept_5";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 1;
			SetCamShuttle(loadedLocation);
			SetPitch(0.95);
		break;
		
		case "drinking_game_accept_5":
			dialog.text = "你还自称是水手! 你很清楚我们是什么样的人。 永远不知道航行会带来什么, 不知道何时何地能看到陆地, 如果能看到的话。 你必须在地图和导航工具之外寻找答案! 为你的健康干杯! (喝酒)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_6";
		break;
		
		case "drinking_game_accept_6":
			dialog.text = "你亲自画的那些女孩... 她们喜欢结果吗? ";
			link.l1 = "她们并不总是喜欢画, 但, 嗯... 结果 - 总是喜欢。 ";
			link.l1.go = "drinking_game_accept_7";
		break;
		
		case "drinking_game_accept_7":
			dialog.text = "查尔斯! 如果我们那时相遇, 我会开枪打你或者把你扣为人质勒索赎金。 顺便说一句, 我从未拿起过画笔。 ";
			link.l1 = "嘿! 好吧, 这太老套了。 亲爱的海伦, 如果我开始列出你从未拿起过的东西... ";
			link.l1.go = "drinking_game_accept_8";
		break;
		
		case "drinking_game_accept_8":
			dialog.text = "好吧, 好吧, 我会公平游戏。 轮到你了, 我的船长。 ";
			link.l1 = "(抿了一口) 嗝!。 嗯... 我从未让我的模特用手枪枪托打我的头。 ";
			link.l1.go = "drinking_game_accept_9";
		break;
		
		case "drinking_game_accept_9":
			dialog.text = "(抿了一口) 呃。 我们玩错了, 亲爱的。 我以为我们会喝酒并了解彼此, 但相反我们在互相嘲讽和... 和... 嗝。 该死! ";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_10";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 2;
			SetCamShuttle(loadedLocation);
			SetPitch(0.90);
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "让我们更有趣一点! 最好不是一小时前我们谈论的内容! ";
			link.l1 = "我从未在饮酒狂欢后在陌生的地方醒来。 ";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "哎哟! 该死, 查尔斯! (喝酒)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_11":
			dialog.text = "我... 嗝... 不敢相信。 我承认, 有罪 - 小伦巴曾经喝到见底。 但我从未进过监狱! ";
			link.l1 = "你怎么... ?";
			link.l1.go = "drinking_game_accept_12";
		break;
		
		case "drinking_game_accept_12":
			dialog.text = "哈哈哈! 喝, 喝! ";
			link.l1 = "我会后悔的。 (喝酒)";
			
			if (IsCharacterEquippedArtefact(pchar, "totem_01")) {
				link.l1.go = "drinking_game_accept_13";
			} else {
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_LightsOut");
			}
		break;
		
		case "drinking_game_accept_13":
			dialog.text = "来吧, 亲爱的。 最后一个问题和最后一次击败我的机会! ";
			link.l1 = "不... 我... 我们去透透气吧。 ";
			link.l1.go = "drinking_game_enough";
			link.l2 = "我经常喝酒, 但从未像这样... 我从未和一个女孩喝得这么醉。 以我的名誉发誓, 喝酒真是一种极大的罪过... ";
			link.l2.go = "drinking_game_accept_14";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 3;
			SetCamShuttle(loadedLocation);
			SetPitch(0.85);
		break;
		
		case "drinking_game_enough":
			dialog.text = "呃! ";
			link.l1 = "";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_accept_14":
			dialog.text = "";
			link.l1 = "等... 你没喝? ";
			link.l1.go = "drinking_game_accept_15";
		break;
		
		case "drinking_game_accept_15":
			dialog.text = "啊哈哈! 太搞笑了! 你的目标很高, 我的船长。 让你知道... 嗝!... 你应该知道... ";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_16";
		break;
		
		case "drinking_game_accept_16":
			dialog.text = "我不幸生活在全是男性的船员中, 我必须小心行事。 我是个诚实的女孩。 ";
			link.l1 = "我为你高兴, 海伦。 ";
			link.l1.go = "drinking_game_accept_17";
		break;
		
		case "drinking_game_accept_17":
			dialog.text = "你会更高兴的, 因为我赢了! 但说实话, 我也从未和一个男孩喝得这么醉过。 ";
			link.l1 = "(默默地喝了一口) 敬你。 恭喜... 嗝... ";
			link.l1.go = "drinking_game_accept_18";
		break;
		
		case "drinking_game_accept_18":
			dialog.text = "嘿嘿嘿! 船长, 你要去哪里? 生气了, 也许? ";
			link.l1 = "我需要... 休息一下? 只是去找我的剑... ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_ExitTavern");
		break;
		
		case "drinking_at_svenson":
			dialog.text = "船长, 你准备好了吗? 没有回头路了, 如果出了什么问题, 我会让你娶我。 ";
			link.l1 = "呼! 至少让我呼吸点新鲜空气! 海伦, 你确定吗? ";
			link.l1.go = "drinking_at_svenson_1";
		break;
		
		case "drinking_at_svenson_1":
			dialog.text = "是的, 该死的, 别像根杆子一样站在那里! 我需要迷失自己, 即使只是一个晚上! ";
			link.l1 = "我担心这个晚上之后, 我才是那个想迷失自己的人。 在我们吵醒整个镇子之前走吧。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_EnterSvenson");
		break;
		
		case "drinking_give_key":
			dialog.text = "船长, 拿上钥匙上楼去。 应该有个箱子; 你可能在斯文森有它的时候见过。 抓起那个桶, 马上回来。 ";
			link.l1 = "等等, 亲爱的, 为什么我要抢劫你的老板? ";
			link.l1.go = "drinking_give_key_1";
			
			GiveItem2Character(pchar, "key3");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_give_key_1":
			dialog.text = "别傻了。 我从小就在这里; 如果主人回来, 我能处理并为你掩护。 来吧, 现在不要降低你的帆! ";
			link.l1 = "像刀一样锋利, 真正的走私者! 等等, 我很快就回来。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GotKey");
		break;
		
		case "drinking_got_whiskey":
			dialog.text = "拿到了? ";
			link.l1 = "当然! 不是我第一次清空箱子, 肯定也不是最后一次! ";
			link.l1.go = "drinking_got_whiskey_1";
		break;
		
		case "drinking_got_whiskey_1":
			dialog.text = "我为你骄傲! 哈哈! 一流的爱尔兰威士忌,'布什米尔斯'! 酒馆里不会给我们上这种酒。 ";
			link.l1 = "听起来不错, 但斯文森不会注意到它不见了吗? ";
			link.l1.go = "drinking_got_whiskey_2";
		break;
		
		case "drinking_got_whiskey_2":
			dialog.text = "他肯定会注意到, 但他自己不喝。 他似乎把它作为礼物留给了他的海盗伙伴多德森, 而多德森要么消失了, 要么杀了人... ";
			link.l1 = "太可怕了! 这样的礼物绝对不能浪费。 抓起桶, 我们换个环境! ";
			link.l1.go = "drinking_got_whiskey_3";
		break;
		
		case "drinking_got_whiskey_3":
			dialog.text = "说得好, 船长。 还有一件事 - 告诉我, 你从箱子里还拿了别的东西吗? 老实回答。 ";
			if (HelenDrinking_RobbedSvenson()) {
				link.l1 = "拿了点东西, 习惯了, 你知道的。 ";
				link.l1.go = "drinking_got_whiskey_notbelieve";
			}
			
			link.l2 = "没有。 不确定我是不是海盗, 但我肯定不是小偷。 ";
			link.l2.go = "drinking_got_whiskey_believe";
			
			if (HelenDrinking_RobbedSvenson()) {
				link.l2.go = "drinking_got_whiskey_notbelieve";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
				Notification_Approve(false, "Helena");
				pchar.questTemp.HelenDrinking.RobbedSvenson = true;
			}
		break;
		
		case "drinking_got_whiskey_believe":
			dialog.text = "不知为何我相信你... 我真是个傻瓜! ";
			link.l1 = "";
			link.l1.go = "drinking_get_out";
		break;
		
		case "drinking_got_whiskey_notbelieve":
			dialog.text = "去确认一下你没因为什么原因拿了别的东西。 ";
			link.l1 = "";
			link.l1.go = "exit";
			if (!HelenDrinking_RobbedSvenson()) {
				AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
				TakeItemFromCharacter(pchar, "cask_whisky");
				sld = ItemsFromID("cask_whisky");
				sld.price = sld.pricebak;
				DeleteAttribute(sld, "pricebak");
			}
			
			NextDiag.TempNode = "drinking_got_whiskey_notbelieve";
		break;
		
		case "drinking_get_out":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
			TakeItemFromCharacter(pchar, "cask_whisky");
			sld = ItemsFromID("cask_whisky");
			sld.price = sld.pricebak;
			DeleteAttribute(sld, "pricebak");
		break;
		
		case "drinking_at_fort":
			dialog.text = "嘿, 嘿, 亲爱的! 集中注意力! 我这张被海风吹拂的脸就在这儿呢! ";
			link.l1 = "呼, 好吧, 你的服装真了不起! 你一定在缝纫材料上省了不少钱。 而我... 嗝! 我见过很多! 但这个... 但这是我见过的最好的东西。 ";
			link.l1.go = "drinking_at_fort_1";
			locCameraFromToPos(-1.65, 44.45, 76.64, true, -5.93, 42.10, 70.13);
		break;
		
		case "drinking_at_fort_1":
			dialog.text = "大家都这么说, 但不知为何, 我相信你! 你真的喜欢吗? ";
			link.l1 = "嗯, 当然, 它非常有利地突出了你的身材, 尽管... ";
			link.l1.go = "drinking_at_fort_2";
		break;
		
		case "drinking_at_fort_2":
			dialog.text = "哦, 现在你把一切都毁了! ";
			link.l1 = "... 尽管我毫不怀疑在普通人中, 它能激起敬畏! ";
			link.l1.go = "drinking_at_fort_3";
		break;
		
		case "drinking_at_fort_3":
			dialog.text = "我更敬畏这种在如此炎热的天气里, 普通人和不那么普通的人都普遍穿着厚重欧式服装的奇怪习惯。 这让我们的村庄看起来更加滑稽... 查尔斯, 我喜欢我的服装。 穿着它, 我觉得自己很美, 这对一个女人来说很重要。 ";
			link.l1 = "即使没有那身服装, 你依然美丽, 海伦。 ";
			link.l1.go = "drinking_at_fort_4";
		break;
		
		case "drinking_at_fort_4":
			dialog.text = "小心点, 我的船长! 说这么甜的话可能会腐蚀一个可怜的女孩! ";
			link.l1 = "如果她不反对, 那我也不反对。 ";
			link.l1.go = "drinking_at_fort_5";
		break;
		
		case "drinking_at_fort_5":
			dialog.text = "嘻嘻! 最好问我点别的。 我喜欢你好奇的样子。 ";
			link.l1 = "那我们就挤时间问一个关于你服装的问题。 我不相信水手能认真对待穿成这样的船长。 ";
			link.l1.go = "drinking_at_fort_6";
		break;
		
		case "drinking_at_fort_6":
			dialog.text = "而且我根本不相信水手能把女人当作船长, 所以我的服装可能没给我增加麻烦。 或者也许是因为这是新衣服, 还没来得及增加麻烦。 我自己缝的! \n啊哈哈! 我以前穿过那种... 叫什么来着? 我们的军队还在穿! 呸... 现在看到那些东西就让我恶心。 ";
			link.l1 = "制服? ";
			link.l1.go = "drinking_at_fort_7";
		break;
		
		case "drinking_at_fort_7":
			dialog.text = "哦, 对, 制服! 红色制服! 就像那个人穿的一样。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.GenQuest.BlockDialogCamera = true;
			AddDialogExitQuestFunction("HelenDrinking_OfficerAtFort");
		break;
		
		case "drinking_at_fort_7_1":
			dialog.text = "哦, 对不起, 少校, 让我请你喝些上等的爱尔兰威士忌作为... 嗝!... 道歉。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog2");
		break;
		
		case "drinking_at_fort_7_2":
			dialog.text = "查尔斯不会有麻烦吧, 少校? 告诉我他不会, 求你了! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog4");
		break;
		
		case "drinking_at_fort_8":
			dialog.text = "我太高兴了! 我们喝酒吧! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToVillage");
		break;
		
		case "drinking_at_miskito":
			dialog.text = "呃。 看看我拿到了什么! ";
			link.l1 = "海伦... 你打算用那个... 来提振精神? ! ... 想都别想! 曼陀罗能完全控制一个人, 耗尽他们的力气, 摧毁他们的意志! 不知不觉中, 你就会成为活死人, 然后很快就真的死了... ";
			link.l1.go = "drinking_at_miskito_1";
		break;
		
		case "drinking_at_miskito_1":
			dialog.text = "查尔斯, 但是... 现在... ";
			link.l1 = "没有但是。 抱歉我语气严厉, 但这不是开玩笑。 我要把这个拿走。 不敢相信你在想什么... 来, 喝这个, 清醒一下。 ";
			link.l1.go = "drinking_at_miskito_2";
			
			GiveItem2Character(pchar, "cannabis7");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_at_miskito_2":
			dialog.text = "对不起, 查尔斯。 你完全正确, 我知道。 一时软弱。 不会再发生了。 谢谢你把我从魔鬼的诱惑中救出来... ";
			link.l1 = "我们忘了吧... 现在, 告诉我, 你是如何在镇上赢得尊重, 与驻军军官保持良好关系, 并与当地人成为朋友的? ";
			link.l1.go = "drinking_at_miskito_3";
		break;
		
		case "drinking_at_miskito_3":
			dialog.text = "他们尊重斯文森, 我也沾了点光。 我们的小镇完全靠扬的交易生存。 他从可可种植园的利润中拿出一部分分给红衣士兵, 而米斯基托人则欠他整个生计。 ";
			link.l1 = "这是怎么发生的? ";
			link.l1.go = "drinking_at_miskito_4";
		break;
		
		case "drinking_at_miskito_4":
			dialog.text = "卡斯蒂利亚人掌权时, 他们不太打扰印第安人。 但在他们赶走高贵的伊达尔戈斯之后, 我们的人决定控制当地的森林。 扬当时非常果断地解决了这个问题 - 甚至派人去了伦敦! 当然, 不是出于好心: 在每棵灌木都跟你作对的森林里采摘可可豆是徒劳的。 但现在, 印第安人不仅帮助扬从贝洛港走私到布鲁维尔德, 还以微薄的薪水砍伐自己的森林。 太棒了, 森林恶魔, 太棒了! ";
			link.l1 = "听起来你并不完全赞成他的方法。 ";
			link.l1.go = "drinking_at_miskito_5";
		break;
		
		case "drinking_at_miskito_5":
			dialog.text = "我爱并尊重米斯基托人, 但我也尊重扬的策略。 我们不生活在童话里, 我的船长。 ";
			link.l1 = "嗯... 我看你和斯文森的关系比乍看起来更复杂... ";
			link.l1.go = "drinking_at_miskito_6";
		break;
		
		case "drinking_at_miskito_6":
			dialog.text = "比你知道的还要复杂。 他的妻子有充分的理由对我充满敌意... 扬从我十五岁左右就开始注意我了。 大约在我开始作为平等成员在彩虹号甲板上行走的时候, 显然那时森林恶魔的脑子里有了什么想法... 但我说得太多了, 我的船长。 我们别深入这个话题了, 议论我们的赞助人不太得体。 ";
			link.l1 = "那我们换个话题。 我是想说, 你显然很适合这个圈子, 他们把你当作自己人。 ";
			link.l1.go = "drinking_at_miskito_7";
		break;
		
		case "drinking_at_miskito_7":
			dialog.text = "碰巧的是, 我更容易和印第安人。 吉普赛人以及其他正派的异类相处。 妈妈的炖菜。 海滩篝火和彩虹号的舷梯 - 我为自己建造了一个舒适的小世界, 船长。 可惜就在我以为一切都弄清楚的时候, 这一切都崩塌了。 ";
			link.l1 = "桶快空了... 最后一轮? ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToShipyard");
		break;
		
		case "drinking_at_perlas":
			dialog.text = "太好了... 很高兴你同意和我共度时光, 船长。 我真的需要这个。 我相信你也一样。 ";
			link.l1 = "是的, 我已经有一段时间没有这样放松了。 这会是值得铭记的! ";
			link.l1.go = "drinking_at_perlas_1";
		break;
		
		case "drinking_at_perlas_1":
			dialog.text = "你现在可能对我有各种想法。 查尔斯, 我天生是个很封闭的人。 我只是... 该死, 我只是想感觉自己还活着! 只是想和人说说话! ";
			link.l1 = "格拉迪斯呢? 扬呢? ";
			link.l1.go = "drinking_at_perlas_2";
		break;
		
		case "drinking_at_perlas_2":
			dialog.text = "妈妈只会哭, 而扬现在好像变了个人。 也许是我想象的, 我不知道, 但好像他现在为我感到羞耻? 原谅我, 我... (抽噎)。 \n够了, 老姑娘。 抱歉, 我有点失控了。 ";
			link.l1 = "没必要道歉。 我理解一切, 或者至少我认为我理解。 ";
			link.l1.go = "drinking_at_perlas_3";
		break;
		
		case "drinking_at_perlas_3":
			dialog.text = "我说这些是因为我们才刚认识, 而我甚至不习惯对认识很久的人如此开放。 他们叫我伦巴, 表面上是因为我的性格, 但如你所见, 这是个误称。 酒都喝完了吗? ";
			link.l1 = "有一会儿了, 黎明已经破晓。 ";
			link.l1.go = "drinking_at_perlas_4";
		break;
		
		case "drinking_at_perlas_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend") && !CheckAttribute(pchar, "questTemp.HelenDrinking.RobbedSvenson")) {
				dialog.text = "对不起, 我的船长, 如果你对我们的夜晚有其他期望。 我... 我不能。 不是今天。 ";
			} else {
				dialog.text = "那么谢谢你的夜晚, 船长。 谁知道呢, 也许我们会再这样做。 ";
			}
			link.l1 = "当然, 海伦。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_PoormanTalk");
		break;
		
		case "ambush":
			dialog.text = "谢谢你带我来这里, 船长。 我们四处看看, 好吗? 检查一下我的遗产。 ";
			link.l1 = "你以前没来过这里吗? ";
			link.l1.go = "ambush_1";
		break;
		
		case "ambush_1":
			dialog.text = "没有, 这里太远了; 此外, 我不是海盗。 这个地方从来没有特别吸引人, 在他们杀了布莱斯之后... 最好不要在这里久留。 ";
			link.l1 = "我们不会的。 我已经后悔带你来这里了。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPrepareAmbush");
		break;
		
		case "after_ambush":
			switch (pchar.questTemp.HelenDrinking.IslaTesoroAmbush) {
				case "A":
					if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB") && !CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC")) {
						dialog.text = "你必须这样做吗, 船长? 为什么这么快就动手? 好吧, 大概不该评判胜利者。 来吧, 我们去看看宅邸; 这里也没什么别的可看了。 ";
						pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
						Notification_Approve(false, "Helena");
					} else {
						dialog.text = "恭喜你, 我的船长, 在动手之前尝试明智地解决问题。 来吧, 我们去看看宅邸; 这里也没什么别的可看了。 ";
					}
					
					link.l1 = "那艘被拖上岸的大船呢? ";
					link.l1.go = "after_ambush_1";
				break;
				
				case "B":
					dialog.text = "你巧妙地愚弄了那些傻瓜, 我的船长! 我差点笑出来, 说真的! 来吧, 我们去看看宅邸; 这里也没什么别的可看了。 ";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					Notification_Approve(true, "Helena");
					
					link.l1 = "那艘被拖上岸的大船呢? ";
					link.l1.go = "after_ambush_1";
				break;
				
				case "C":
					dialog.text = "等一下, 让女孩喘口气! 你真的是查理.普林斯吗? ";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					Notification_Approve(true, "Helena");
					
					link.l1 = "我的传记中确实有那个时期, 是的。 你印象深刻吗? ";
					link.l1.go = "after_ambush_c";
				break;
			}
		break;
		
		case "after_ambush_1":
			dialog.text = "是的, 你说得对。 我很想探索它, 但说实话, 查尔斯, 我有点害怕。 我们走吧。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroGoToResidence");
		break;
		
		case "after_ambush_c":
			dialog.text = "哦, 我的上帝, 是的! 以后一定要把一切都告诉我, 好吗? 因为我只听过故事... 非常不雅的故事! ";
			link.l1 = "我会告诉你一切... 几乎一切。 ";
			link.l1.go = "after_ambush_c_1";
		break;
		
		case "after_ambush_c_1":
			dialog.text = "我会热切期待! 来吧, 我们去看看宅邸; 这里也没什么别的可看了。 ";
			link.l1 = "那艘被拖上岸的大船呢? ";
			link.l1.go = "after_ambush_1";
		break;
		
		case "ambush_inresidence":
			dialog.text = "一个狭窄。 寒冷的小屋, 还有荒谬的要求。 我已经觉得自己像掉进了陷阱! ";
			link.l1 = "看来目前你对这处潜在房产并不满意? ";
			link.l1.go = "ambush_inresidence_1";
		break;
		
		case "ambush_inresidence_1":
			dialog.text = "是的, 查尔斯。 也许我太挑剔了, 但目前它体现了我害怕和憎恨的一切。 我希望我能把它租出去... 不过, 我不确定该把钱花在哪里。 ";
			link.l1 = "别低估租金的价值。 我没有租金, 经常不得不想出支付船员的方法。 你会给自己买一艘新船,'彩虹二号'- 听起来不错, 不是吗? ! ";
			link.l1.go = "ambush_inresidence_sea";
			link.l2 = "有很多犒劳自己的方式。 不妨先定制一把宝剑, 再配上一瓶佳酿。 好好款待自己吧, 海伦, 你值得拥有这一切。 ";
			link.l2.go = "ambush_inresidence_land";
		break;
		
		case "ambush_inresidence_sea":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "sea") {
				dialog.text = "谢谢你, 我的船长。 很高兴听到你这么说。 第二次听到尤其开心。 你很了解我。 ";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
				Notification_Approve(true, "Helena");
			} else {
				dialog.text = "谢谢你, 我的船长。 很高兴听到你这么说。 ";
			}
			
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_COMMERCE, 5);
			AddCharacterSkill(sld, SKILL_ACCURACY, 5);
			AddCharacterSkill(sld, SKILL_CANNONS, 5);
			AddCharacterSkill(sld, SKILL_SAILING, 5);
			AddCharacterSkill(sld, SKILL_REPAIR, 5);
			AddCharacterSkill(sld, SKILL_GRAPPLING, 5);
			AddCharacterSkill(sld, SKILL_DEFENCE, 5);
		break;
		
		case "ambush_inresidence_land":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "land") {
				dialog.text = "你认为我值得吗? 我从未在这种琐事上花过钱, 但我想凡事都有第一次。 我看你不会停止试图让我忘记大海, 是吗, 船长? 也许你是对的... ";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 3;
				Notification_Approve(false, "Helena");
			} else {
				dialog.text = "你认为我值得吗? 我从未在这种琐事上花过钱, 但我想凡事都有第一次。 ";
			}
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_F_LIGHT, 5);
			AddCharacterSkill(sld, SKILL_FENCING, 5);
			AddCharacterSkill(sld, SKILL_F_HEAVY, 5);
			AddCharacterSkill(sld, SKILL_PISTOL, 5);
			AddCharacterSkill(sld, SKILL_FORTUNE, 5);
			AddCharacterSkill(sld, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(sld, SKILL_SNEAK, 5);
		break;
		
		case "ambush_inresidence_2":
			dialog.text = "无论如何, 检查已经完成。 这里似乎没有贵重物品 - 那些乌合之众已经把一切都洗劫一空, 而且我敢肯定二楼也是一样的情况。 ";
			link.l1 = "海伦, 你好像变了。 上次我们一起时, 你更... 我不知道, 更开放? ";
			link.l1.go = "ambush_inresidence_3";
		break;
		
		case "ambush_inresidence_3":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "没什么变化, 我的船长, 但一个可怜的女孩肩上压了很多事, 哈哈! 我不是有意冒犯你。 我现在只是需要思考很多事情。 你知道, 生活中这样的急转弯不是每天都有的。 我们还有很多时间在一起! ";
				link.l1 = "很高兴听到你这么说! 我们离开这里吧。 ";
			} else {
				dialog.text = "变化很大, 船长。 恐怕我现在必须更成熟, 以不同的方式看待生活。 这不是关于公主和遗产的童话; 这是大政治, 我还得认清自己在其中的位置。 还有我家族的位置。 ";
				link.l1 = "很高兴我们澄清了这一点。 我们离开这里吧。 ";
			}
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroBeforeExit");
		break;
		
		case "ambush_inresidence_wait":
			dialog.text = "什么事? ";
			if (CheckCharacterItem(pchar, "pirate_cutlass")) {
				link.l1 = "嘿, 不是所有东西都被洗劫了! 看, 海伦! 这把军刀似乎很传奇, 因为即使是当地的乌合之众也犹豫着没把它拿走。 ";
				link.l1.go = "ambush_inresidence_give_cutlass";
			}
			
			link.l2 = "不, 没什么。 ";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "ambush_inresidence_wait";
		break;
		
		case "ambush_inresidence_give_cutlass":
			dialog.text = "哇, 这是... 布莱斯本人的传奇弯刀! 即使在他死后, 海盗们也太尊敬他了, 不敢从他家里拿走这把军刀。 当然, 他们拿走了钱和贵重物品, 但即使是未来的绞刑犯也有一点荣誉感... ";
			link.l1 = "看来有人在这里精心整理过。 好像主人会回来... 这不是家; 这是纪念馆! ";
			link.l1.go = "ambush_inresidence_give_cutlass_1";
		break;
		
		case "ambush_inresidence_give_cutlass_1":
			dialog.text = "谢谢你的敏锐观察, 查尔斯。 你彻底毁了我对这个地方的印象, 哈哈! ";
			link.l1 = "我认为这把弯刀现在属于你了。 布莱斯是你所谓的叔叔... ";
			link.l1.go = "ambush_inresidence_give_cutlass_2";
		break;
		
		case "ambush_inresidence_give_cutlass_2":
			dialog.text = "你这是在给它增添更多恐怖, 我的船长。 我... 我不能。 我担心如果我接受它, 我过去的生活就会彻底结束。 ";
			link.l1 = "那就别把它当作遗产的一部分, 而是当作一个英俊男人的礼物。 ";
			link.l1.go = "ambush_inresidence_give_cutlass_3";
		break;
		
		case "ambush_inresidence_give_cutlass_3":
			dialog.text = "那是谁? 开玩笑的! 谢谢你驱散了我的阴暗想法, 我的船长。 我保证会多训练, 配得上这把刀! ";
			link.l1 = "海伦, 你配得上最好的武器。 我们走吧, 这里结束了。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "give_cutlass":
			dialog.text = "哇, 这是... 布莱斯本人的传奇弯刀! 即使在他死后, 海盗们也太尊敬他了, 不敢从他家里拿走这把军刀。 当然, 他们拿走了钱和贵重物品, 但即使是未来的绞刑犯也有一点荣誉感\n我... 我不能。 我担心如果我接受它, 我过去的生活就会彻底结束。 ";
			link.l1 = "那就别把它当作遗产的一部分, 而是当作一个英俊男人的礼物。 ";
			link.l1.go = "give_cutlass_1";
		break;
		
		case "give_cutlass_1":
			dialog.text = "那是谁? 开玩笑的! 谢谢你驱散了我的阴暗想法, 我的船长。 ";
			link.l1 = "海伦, 你配得上最好的武器。 很高兴你喜欢它。 ";
			link.l1.go = "give_cutlass_2";
		break;
		
		case "give_cutlass_2":
			dialog.text = "我保证会多训练, 配得上这把刀! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "arrive":
			dialog.text = "我的船长! 查理! ";
			link.l1 = "查理? 这是新称呼! 很高兴见到你, 亲爱的。 ";
			link.l1.go = "arrive_1";
		break;

		case "arrive_1":
			dialog.text = "我不小心说漏嘴了, 哈! 也很高兴见到你... ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog1");
		break;

		case "arrive_2":
			dialog.text = "姐妹情谊就这么回事! 我的船长, 我... 我真的很担心, 非常想你! ";
			link.l1 = "那你为什么要跑回家? ";
			link.l1.go = "arrive_3";
		break;

		case "arrive_3":
			dialog.text = "为了... 哦, 对了! 我有个小礼物给你, 给! ";
			link.l1 = "三个护身符... 海伦, 为什么? 你想跟着我吗? ";
			link.l1.go = "arrive_4";
			
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Indian);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Amulet);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Obereg);
		break;

		case "arrive_4":
			dialog.text = "过来, 你这个傻瓜! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FirstKiss");
		break;

		case "after_kiss":
			dialog.text = "你敢破坏这一刻 - 我想象了一辈子! ";
			link.l1 = "我不会的, 海伦。 ";
			link.l1.go = "after_kiss_a";
			link.l2 = "你一辈子都在等遇见我? 受宠若惊! ";
			link.l2.go = "after_kiss_b";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l3 = "海伦, 有件事... 在正义岛, 我遇见了一个女人, 而且... ";
				link.l3.go = "after_kiss_c";
			}
			locCameraFromToPos(-19.00, 1.56, 19.07, true, -11.19, -0.90, 17.49);
		break;
		
		case "after_kiss_a":
			dialog.text = "没错! 你会告诉我一切, 一切! 我在船上等你, 我的船长! ";
			link.l1 = "等等!... ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_b":
			dialog.text = "傻瓜! 想冒犯我? 好吧, 我被冒犯了! 哈哈! 我现在就去船上, 在丹尼再嘲笑我之前... ";
			link.l1 = "等等!... ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_c":
			dialog.text = "傻瓜! 我让你别破坏这一刻! 遇见... 好吧, 你遇见了 - 我还没看到你手指上的戒指。 但别以为你能逃脱 - 等你回到船上, 我会等着听详细故事。 ";
			link.l1 = "等等!... ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "loot_good":
			dialog.text = "我的船长, 有什么消息? 从你苍白的脸色我能看出, 律师决定给你添更多麻烦而不是帮助你。 ";
			link.l1 = "你说得对, 海伦。 洛克斯利要了一笔可观的预付款, 而这个案子本身要花我一大笔钱。 我要去摇醒扬 - 我受够了! 好像兄弟会决定把所有费用都转嫁给我! ";
			link.l1.go = "loot_good_1";
		break;
		
		case "loot_good_1":
			dialog.text = "这没有恶意, 查尔斯。 他们就是这样 - 除非迫不得已, 否则不会动一根手指。 我相信扬会帮助你, 我也不会袖手旁观。 ";
			link.l1 = "我知道, 海伦。 告诉我你有什么想法。 ";
			link.l1.go = "loot_good_2";
		break;
		
		case "loot_good_2":
			dialog.text = "我以前为扬工作 - 在缅因州各地走私贵重木材。 但我是个足智多谋的女孩, 在所有那些旅行中, 我为自己存了点东西。 ";
			link.l1 = "扬没发现? 真聪明! ";
			link.l1.go = "loot_good_3";
		break;
		
		case "loot_good_3":
			dialog.text = "我有个好会计。 长话短说, 我攒了一笔可观的钱, 把它藏在离这里不远的地方。 你现在要去见扬吗? 那我们去圣胡安德尔诺特。 附近有个山洞, 我们只需要一些水手帮忙, 这样就不用自己搬所有东西了。 ";
			link.l1 = "你已经都想好了, 是吗? 谢谢你, 海伦, 如果有时间我们一定会去。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "loot_bad":
			dialog.text = "我的船长, 有什么消息? 从你苍白的脸色我能看出, 律师决定给你添更多麻烦而不是帮助你。 ";
			link.l1 = "你说得对, 海伦。 洛克斯利要了一笔可观的预付款, 而这个案子本身要花我一大笔钱。 我要去摇醒扬 - 我受够了! 好像兄弟会决定把所有费用都转嫁给我! ";
			link.l1.go = "loot_bad_1";
		break;
		
		case "loot_bad_1":
			dialog.text = "你以为你在童话里吗? 别担心, 我们都处境相同, 我会帮你。 毕竟, 我有权继承遗产, 不是吗? ";
			link.l1 = "没错... 告诉我, 你在想什么! ";
			link.l1.go = "loot_bad_2";
		break;
		
		case "loot_bad_2":
			dialog.text = "我在圣胡安德尔诺特藏了些东西。 附近有个山洞 - 我们只需要抓些水手, 这样就不用自己搬所有东西了。 ";
			link.l1 = "你已经都想好了, 是吗? 谢谢你, 海伦, 如果有时间我们一定会去。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "shdn":
			dialog.text = "就是这里, 查尔斯! 但你得一个人去 - 我讨厌山洞! ";
			link.l1 = "像任何封闭空间一样, 我知道, 海伦。 在这里等我。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoForLoot");
		break;
		
		case "shdn_ambush":
			dialog.text = "我们有麻烦了! 一队士兵正朝这边走来, 他们看起来很凶恶。 小心, 查尔斯, 不只是普通的海岸警卫 - 其中有个法国军官! 我求你, 别做傻事! ";
			link.l1 = "我什么时候做过傻事? ! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SpawnAmbushSoldiers");
		break;
		
		case "shdn_ambush_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "哈, 第二个选项听起来更诱人, 但我希望你不要太得意, 查尔斯? ";
			} else {
				dialog.text = "查尔斯, 我并不惊讶... ";
			}
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog1");
		break;
		
		case "shdn_ambush_2":
			dialog.text = "你说完了吗? 现在轮到我说话! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_HelenKillFrancois");
		break;
		
		case "shdn_ambush_3":
			dialog.text = "我叫海伦.麦卡瑟! 船长, 你知道我是谁, 知道我为谁工作! 告诉你的人, 尤其是躺在地上的这个花哨白痴, 听我现在宣布今天的结果! ";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "richard");
			sld = CharacterFromID("HelenDrinking_Richard");
			CharacterTurnByChr(sld, npchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath2");
		break;
		
		case "shdn_ambush_4":
			dialog.text = "抗议? 我不在乎你是否写信给克伦威尔本人。 首先, 德.莫尔先生今天没有失去荣誉。 ";
			link.l1 = "";
			link.l1.go = "shdn_ambush_5";
			CharacterTurnToLoc(npchar, "quest", "richard");
		break;
		
		case "shdn_ambush_5":
			dialog.text = "其次, 德.塔旺上校因为称一个穿着非常火辣服装的女孩为妓女而被她开枪击中。 ";
			link.l1 = "";
			link.l1.go = "shdn_ambush_6";
		break;
		
		case "shdn_ambush_6":
			dialog.text = "第三, 你立即撤回你的士兵, 忘记发生的一切, 除非你想让森林恶魔知道这件事。 ";
			link.l1 = "";
			link.l1.go = "shdn_ambush_7";
		break;
		
		case "shdn_ambush_7":
			locCameraSleep(false);
			dialog.text = "我看没有问题。 祝你今天愉快, 船长。 ";
			link.l1 = "上帝啊, 海伦, 你太棒了! ";
			link.l1.go = "shdn_ambush_8";
		break;
		
		case "shdn_ambush_8":
			dialog.text = "以后再说, 查尔斯。 在他们从震惊中恢复之前, 我们离开这里。 我也在发抖。 我们能在布鲁维尔德谈谈吗? ";
			link.l1 = "同意。 ";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, pchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath3");
		break;
		
		case "duel_victory":
			dialog.text = "在他们从震惊中恢复之前, 我们离开这里。 我们还需要取回铁木, 记得吗? 我们可以在布鲁维尔德谈谈。 ";
			link.l1 = "哇! 连一句祝贺都没有? 好吧, 走吧。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory1");
		break;
		
		case "after_cave":
			dialog.text = "终于到家了... ";
			link.l1 = "你怎么看待发生的事? ";
			link.l1.go = "after_cave_1";
		break;
		
		case "after_cave_1":
			dialog.text = "我不懂决斗。 男人的消遣, 通常以两具尸体告终, 运气好的话, 甚至更多。 而荣誉... 我认为荣誉建立在尽可能避免冲突的愿望上, 因为它很少被证明是值得的。 哈! 听听我 - 我在胡说八道! ";
			link.l1 = "这是个有趣的观点, 海伦。 不过不是每个人都会同意。 ";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
				link.l1.go = "after_cave_duel";
			} else {
				link.l1.go = "after_cave_notduel";
			}
		break;
		
		case "after_cave_duel":
			dialog.text = "可惜你落入了他们的圈套。 上校显然很着迷, 其他人只是想看热闹和找点八卦素材。 好吧, 我不会再提了 - 你今天已经受够了。 ";
			link.l1 = "是的, 决斗之后, 总是有一种空虚感。 今天的冒险够多了。 你接下来想做什么? ";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_notduel":
			dialog.text = "呃! 我只是想说, 我为我们感到骄傲。 你今天表现出了真正的勇气, 我的船长。 没有屈服于那些只想指挥你一次的船员的歇斯底里。 坚定地反对红衣制服的虚伪和蓝衣人的痴迷。 上校显然是在寻死, 但只在不合适的地方受了伤, 哈哈! ";
			link.l1 = "谢谢你, 海伦。 你出色地引导我们避开了打击, 像个真正的海军军官。 你为自己骄傲吗? ";
			link.l1.go = "after_cave_notduel_1";
		break;
		
		case "after_cave_notduel_1":
			dialog.text = "是的, 我需要那个。 可惜是蓝色制服, 不是红色的, 但至少穿它的人得到了应有的惩罚。 ";
			link.l1 = "那个人确实无关紧要, 我承认。 今天的冒险够多了。 你接下来想做什么? ";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_mild":
			dialog.text = "我要回家了, 我的船长。 想念我妈妈... 格拉迪斯。 可惜她现在在家, 否则我会邀请你过来! ";
			link.l1 = "确实, 真遗憾! ";
			link.l1.go = "after_cave_mild_1";
		break;
		
		case "after_cave_mild_1":
			dialog.text = "别这么沮丧。 很快, 亲爱的。 同时... ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "嗯... 这个比我们第一次的还要好。 记得吗? 在神像旁边? ";
				link.l1 = "那不是轻易能忘记的, 亲爱的。 ";
				link.l1.go = "after_second_kiss_1";
			} else {
				dialog.text = "你敢破坏这一刻 - 我想象了一辈子! ";
				link.l1 = "我不会的, 海伦。 ";
				link.l1.go = "after_second_kiss_a";
				link.l2 = "你一辈子都在等遇见我? 受宠若惊! ";
				link.l2.go = "after_second_kiss_b";
			}
		break;
		
		case "after_second_kiss_1":
			dialog.text = "哦! 控制一下自己, 女孩! 再见, 我的船长。 ";
			link.l1 = "再见, 海伦。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_a":
			dialog.text = "没错! 我们很快会再见, 我的船长。 ";
			link.l1 = "再见, 海伦。 哦, 上帝, 多好的女孩... ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_b":
			dialog.text = "傻瓜! 想冒犯我? 好吧, 我被冒犯了! 哈哈! 我们很快会再见, 我的船长。 ";
			link.l1 = "再见, 海伦。 哦, 上帝, 多好的女孩... ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_cave_cold":
			dialog.text = "我要回家了, 船长。 我想和律师的钱问题现在解决了? 我们面前有艰难的障碍, 所以从现在起尽量远离麻烦。 麻烦自己会找上门的。 ";
			link.l1 = "哇, 真的吗? ";
			link.l1.go = "after_cave_cold_1";
		break;
		
		case "after_cave_cold_1":
			dialog.text = "抱歉说话直, 船长。 你知道, 我的命运现在也在被决定。 ";
			link.l1 = "我知道, 我会尽量表现得有尊严。 船上见, 海伦。 ";
			link.l1.go = "after_cave_cold_2";
		break;
		
		case "after_cave_cold_2":
			dialog.text = "是, 船长! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveCold");
		break;
		
		case "after_cave_lewd":
			dialog.text = "接下来做什么? 我会让你看的。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss1":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "嗯... 这个比我们第一次的还要好。 记得吗? 在神像旁边? ";
				link.l1 = "那不是轻易能忘记的, 亲爱的。 ";
				link.l1.go = "after_second_kiss1_1";
			} else {
				dialog.text = "你敢破坏这一刻 - 我想象了一辈子! ";
				link.l1 = "我不会的, 海伦。 ";
				link.l1.go = "after_second_kiss1_a";
				link.l2 = "你一辈子都在等遇见我? 受宠若惊! ";
				link.l2.go = "after_second_kiss1_b";
			}
		break;
		
		case "after_second_kiss1_1":
			dialog.text = "没错! 哇! 格拉迪斯现在不在家。 想进来吗? ";
			link.l1 = "邀请我过去? 我们会做什么? ";
			link.l1.go = "after_cave_lewd_accept";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l2 = "不, 海伦。 另一个女人在正义岛等我。 我不能那样对她。 ";
				link.l2.go = "after_cave_lewd_refuse_mary";
			}
			link.l3 = "下次吧, 亲爱的。 我真的很想, 但今天几乎要了我的命。 我们会补上, 十倍补偿错过的时间。 ";
			link.l3.go = "after_cave_lewd_refuse_head";
		break;
		
		case "after_second_kiss1_a":
			dialog.text = "没错! 哇! 格拉迪斯现在不在家。 想进来吗? ";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "不, 海伦。 另一个女人在正义岛等我。 我不能那样对她。 ";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "下次吧, 亲爱的。 我真的很想, 但今天几乎要了我的命。 我们会补上, 十倍补偿错过的时间。 ";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "邀请我过去? 我们会做什么? ";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_second_kiss1_b":
			dialog.text = "傻瓜! 想冒犯我? 好吧, 我被冒犯了! 哈哈! 你得补偿我, 我的船长。 哇! 格拉迪斯现在不在家。 想进来吗? ";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "不, 海伦。 另一个女人在正义岛等我。 我不能那样对她。 ";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "下次吧, 亲爱的。 我真的很想, 但今天几乎要了我的命。 我们会补上, 十倍补偿错过的时间。 ";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "邀请我过去? 我们会做什么? ";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_cave_lewd_refuse_mary":
			dialog.text = "啊, 所以我在诱惑艺术上不够娴熟? 而她是吗? 她是谁? ";
			link.l1 = "她叫玛丽.卡斯帕, 我爱她。 ";
			link.l1.go = "after_cave_lewd_refuse_mary_1";
		break;
		
		case "after_cave_lewd_refuse_mary_1":
			dialog.text = "那个穿红制服的红发女人? 穿红制服... 好吧, 如果我需要一个信号, 这就是了。 命中注定如此。 别担心, 船长, 这不会影响我在你船上的服务。 ";
			link.l1 = "对不起, 海伦。 ";
			link.l1.go = "exit";
			
			pchar.questTemp.HelenDrinking.Mary = true;
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMary");
		break;
		
		case "after_cave_lewd_refuse_head":
			dialog.text = "哦, 我的船长! 让女人处于这种状态是危险的! 我记住你的话了, 现在快跑... 我现在需要一个人待着, 试着自己处理我的问题... 自己! 船上见! ";
			link.l1 = "多好的女孩! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMild");
		break;
		
		case "after_cave_lewd_accept":
			dialog.text = "别担心, 亲爱的, 如果我迷路了, 我会引导你。 ";
			link.l1 = "那么... 带路吧! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveAccept");
		break;
		
		case "after_cave_bedroom":
			dialog.text = "什么都别说, 我求你。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex1");
		break;
		
		case "after_cave_sex":
			dialog.text = "... 当然, 直到今天, 我对这个话题的理解完全基于彩虹号船员的粗俗谈话, 如果那能称为谈话的话。 ";
			link.l1 = "感觉如何? 现实符合你的期望吗? ";
			link.l1.go = "after_cave_sex_1";
		break;
		
		case "after_cave_sex_1":
			dialog.text = "我非常喜欢, 但感觉还没有完全体验到。 而如何... ";
			link.l1 = "让我展示给你! 我们继续? ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex2");
		break;
		
		case "after_cave_sex_again":
			dialog.text = "哦, 现在我明白了! 太奇妙了, 我的船长! ";
			link.l1 = "至少可以说, 你让我很惊讶! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysEnter");
		break;
		
		case "after_cave_gladys":
			dialog.text = "啊哈哈! 这绝对是个好笑话! 现在她要么用蜡堵住耳朵, 要么跑到堡垒的最高平台去! ";
			link.l1 = "那出乎意料但非常有趣, 啊哈哈! ";
			link.l1.go = "after_cave_gladys_1";
			locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - 卧室镜头
		break;
		
		case "after_cave_gladys_1":
			dialog.text = "准备好了吗, 我的船长? ";
			link.l1 = "已经? ! 不, 海伦, 求求你怜悯我。 格拉迪斯的突然出现绝对不利于气氛。 ";
			link.l1.go = "after_cave_gladys_2";
		break;
		
		case "after_cave_gladys_2":
			dialog.text = "好吧, 你能做什么... 虽然... ";
			link.l1 = "不, 不, 降下你的帆! ";
			link.l1.go = "after_cave_gladys_3";
		break;
		
		case "after_cave_gladys_3":
			dialog.text = "好吧, 那我们就一起待一会儿。 我们的未来如此模糊和可怕, 但很长一段时间以来, 我第一次不再害怕其他任何事情。 我知道一些新的恐惧会悄悄袭来, 但不是今天。 不是今天, 我的船长。 ";
			link.l1 = "不是今天, 我亲爱的。 不是今天。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveFin");
		break;
		
		case "give_potions":
			dialog.text = "船长, 允许我发言吗? ";
			link.l1 = "怎么了, 海伦? ";
			link.l1.go = "give_potions_1";
		break;
		
		case "give_potions_1":
			dialog.text = "我认识这个蛇眼 - 他是个好人, 但有点古怪。 他定期派人们去寻找天知道什么任务。 我看你也获得了那份可疑的荣誉。 ";
			if (!CheckAttribute(CharacterFromID("SnakeEye"), "quest.amulet")) {
				link.l1 = "没错, 我需要给他带三个护身符, 否则他不会帮我去霍克的地方。 但你知道有趣的是什么吗? 我身上已经有了! 也许他从一开始就知道? ";
				link.l1.go = "give_potions_already";
			} else {
				link.l1 = "没错, 我需要给他带三个护身符, 否则他不会帮我去霍克的地方。 我现在想不出去哪里找, 时间也不多了。 ";
				link.l1.go = "give_potions_3";
			}
		break;
		
		case "give_potions_already":
			dialog.text = "哦, 真遗憾! 我很高兴你不必到处从灯塔看守那里获取那些护身符, 但我希望有一次我能对你有用, 希望能证明自己。 ";
			link.l1 = "胡说, 海伦。 你不需要向我证明任何东西。 ";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_3":
			dialog.text = "我会帮你! 我承认, 我希望有一次我能对你有用, 希望能证明自己。 ";
			link.l1 = "胡说, 海伦。 你不需要向我证明任何东西。 ";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_4":
			dialog.text = "尽管如此, 我还是想帮你。 给, 拿上我房间的钥匙... 我是说, 我房间里的箱子! 东西不多, 但对你会有用。 还有... 查尔斯, 现在尽量别笑! ";
			link.l1 = "咳咳, 我不会的。 我看你对这些东西感兴趣? ";
			link.l1.go = "give_potions_5";
		break;
		
		case "give_potions_5":
			dialog.text = "我是个水手, 我的船长, 就像你一样。 在我们这行, 我们必须尽一切可能让幸运女神站在我们这边。 ";
			link.l1 = "谢谢你, 海伦。 我真的很感激。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GivePotionsKey");
		break;
		
		case "upgrade":
			dialog.text = "亲爱的, 我有礼物给你! ";
			link.l1 = "我看到了, 就在那里 - 站着微笑! ";
			link.l1.go = "upgrade_1";
		break;
		
		case "upgrade_1":
			dialog.text = "啊哈, 住手! 我曾经给当地的造船匠送过一批不错的丝绸, 所以现在他欠我一次船的全面大修。 我本想把'彩虹号'交给他做这个工作, 但那并不合适。 另一方面, 你的船真的可以从这样的护理中受益, 你不觉得吗? ";
			link.l1 = "确实, 一份极好的礼物, 海伦 - 正合你意! ";
			link.l1.go = "upgrade_2";
		break;
		
		case "upgrade_2":
			dialog.text = "我很高兴你喜欢。 随时拜访他, 告诉他是我派你去的。 他们会尽最大努力。 ";
			link.l1 = "一定! ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("HelenUpgradeShip1");
		break;
		
		case "give_sex":
			dialog.text = "我的船长, 允许我发言吗? ";
			link.l1 = "当然, 我亲爱的。 ";
			link.l1.go = "give_sex_1";
		break;
		
		case "give_sex_1":
			dialog.text = LinkRandPhrase("你的女士想你了, 需要关注。 我可以请求为她安排一个房间并花些时间陪她吗", "报告: 当地酒馆的床上需要你。 只需要你五分钟, 但船员希望你待得更久! ", "船上发生哗变, 我的船长! 我被派去在私人场合给你一个黑色印记。 立即跟我来! ");
			link.l1 = "嘿嘿, 咳咳! Sharp军官, 你的请求被批准了! ";
			link.l1.go = "give_sex_1_yes";
			link.l2 = "今天不行, 亲爱的。 现在发生的事情太多了。 ";
			link.l2.go = "give_sex_1_no";
		break;
		
		case "give_sex_1_yes":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			DialogExit();
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "give_sex_1_no":
			dialog.text = "哦, 那你想让一个可怜的女孩做什么, 嗯? 好吧, 亲爱的, 那就下次吧。 ";
			link.l1 = "";
			link.l1.go = "give_sex_2_no";
		break;
		
		case "give_sex_2_no":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			npchar.location = "None";
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			chrDisableReloadToLocation = false;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		break;
		
		case "special_sex":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			SaveCurrentNpcQuestDateParam(npchar, "special_sex_date");
			
			dialog.text = "哈! 不用问我第二遍! 当然, 我们走! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "rainbow":
			dialog.text = "我现在就把你扔到海里去! ";
			link.l1 = "嘿, 嘿, 嘿! 冷静点, 亲爱的! ";
			link.l1.go = "rainbow_1";
		break;
		
		case "rainbow_1":
			dialog.text = "过来, 你这个流氓! ";
			link.l1 = "只是开玩笑, 海伦! 我不是有意冒犯你! ";
			link.l1.go = "rainbow_2";
		break;
		
		case "rainbow_2":
			dialog.text = "哦, 真的吗? 混蛋... ";
			link.l1 = "你是最美丽的, 我疯狂地爱你! ";
			link.l1.go = "rainbow_3";
		break;
		
		case "rainbow_3":
			dialog.text = "滚吧, 查尔斯。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Rainbow");
			Achievment_Set("ach_CL_84");
		break;
		
		case "joan":
			dialog.text = "你自己才是荡妇! 很高兴扬让你成为一个正派女人, 否则你还会对每个过路人张开双腿! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog2");
		break;
		
		case "joan_1":
			dialog.text = "娼妇! 我们走, 查尔斯! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			ResetSound();
			SetMusic("helendrinking_shanty");
			pchar.questTemp.lockedMusic = true;
			AddDialogExitQuestFunction("HelenDrinking_GoToFort");
		break;
		
		case "cutlass_training":
			dialog.text = "这把弯刀在我手里非常合适! 我不知道如何解释... 我总是在其他类型的冷兵器上挣扎, 比如细剑和剑。 但这把弯刀不同! 感觉太棒了! 谢谢你, 查尔斯! ";
			link.l1 = "命运总有办法找到我们。 我为你高兴, 海伦! ";
			link.l1.go = "exit";
			notification("中型武器 +", "Helena");
		break;
		
		case "brothel_found":
			dialog.text = "把你的故事留给别人吧, 对我没用。 我看起来像一个天真。 热恋的傻瓜吗? 我的意思是, 我确实疯狂地爱上了你, 但称我为傻瓜就有点过分了\n 听着, 亲爱的, 你想怎么做就怎么做, 但请记住, 你不会找到比我更好的女人。 如果你想在妓院找她, 去吧, 然后我会从你的生活中永远消失。 ";
			link.l1 = "海伦, 我... ";
			link.l1.go = "brothel_found_1";
		break;
		
		case "brothel_found_1":
			dialog.text = "我明白一切, 查尔斯。 你只爱我, 这些只是自然冲动。 你知道我的自然冲动是什么吗? 来自我男人的尊重。 一个女人可能不仅仅满足于爱, 亲爱的。 我们现在先忘记这个误会, 但仔细想想我的话。 好吗? ";
			link.l1 = "好的, 海伦。 ";
			link.l1.go = "exit";
		break;
		
		case "refuse":
			dialog.text = "你知道是怎么回事。 先让一个女孩冷静下来。 ";
			link.l1 = "唉... ";
			link.l1.go = "exit";
		break;
		
		// 皇家港之谜
		case "MysteryPortRoyal_Helena_1":
			dialog.text = "弗朗西斯... 我记得他。 他总是在皇家港等我到来, 是个无可救药的浪漫主义者。 我喜欢和一个远离大海的人共度时光 - 所有那些诗歌和小夜曲... 这是新的东西。 一瞥我从未了解的世界。 \n弗朗西斯富有。 聪明。 英俊 - 相当有魅力。 任何当地女孩都会为他的关注而疯狂, 但那时, 我更关心如何让彩虹号维持下去。 ";
			link.l1 = "似乎诗人敏感的灵魂无法承受你的拒绝。 在他所有的信中, 他只谈论你, 回忆你们相遇的地方。 如果你想要, 我可以把他留下的一切都给你。 ";
			link.l1.go = "MysteryPortRoyal_Helena_2";
		break;
		
		case "MysteryPortRoyal_Helena_2":
			dialog.text = "我不知道他生病了。 现在这一切都觉得很愚蠢。 至于他的礼物... 我已经受够了遗嘱和遗产。 相信我, 我拥有我需要的一切 - 甚至更多。 你最好留着它。 ";
			link.l1 = "无论如何, 他的遗产最终还是会为你服务 - 这意味着我不知不觉地执行了他的最后愿望。 相当精彩的故事。 ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.MysteryPortRoyal_Helena");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenDrinking_RobbedSvenson() {
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	if (!CheckAttribute(sld, "private1.items.chest")) { 
		return true;
	}
	
	if (sti(sld.private1.items.chest) < 2) {
		return true;
	}
	
	return false;
}