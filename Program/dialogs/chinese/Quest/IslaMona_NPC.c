void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "你需要什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;
		
		// 罗德里戈.希梅内斯
		case "Himenes_exit":
			dialog.text = "还有别的事吗, 船长? ";
			link.l1 = "目前没有... ";
			link.l1.go = "Himenes_exit_1";
		break;
		
		case "Himenes_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
		break;
		
		case "Himenes":
			dialog.text = "哈-哈-哈! 赫苏克里斯托先生! 赞美圣地亚哥守护者! 赞美圣母玛利亚! 我们得救了! 哈-哈-哈! ";
			link.l1 = "西班牙人! 拿起武器! ";
			link.l1.go = "Himenes_1_1";
			link.l2 = "你好。 我知道你们有麻烦了? 你是谁? ";
			link.l2.go = "Himenes_2";
		break;
		
		case "Himenes_1_1":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "哈-哈-哈-哈-哈-哈-哈-哈! ";
			link.l1 = "好的-好的, 冷静点。 这只是个习惯。 ";
			link.l1.go = "Himenes_2";
		break;
		
		case "Himenes_2":
			dialog.text = "哈-哈! 先生, 我叫罗德里戈.希梅内斯。 我是一名测量员, 也是这些不幸之人的头儿, 这是命运的安排。 ";
			link.l1.go = "Himenes_3";
		break;
		
		case "Himenes_3":
			dialog.text = "我们... 被送到了这里。 但是, 先生, 我们不是罪犯! 哈-哈-哈-哈! ";
			link.l1 = "有什么好笑的? ";
			link.l1.go = "Himenes_4";
		break;
		
		case "Himenes_4":
			dialog.text = "啊... 对不起, 先生! 这是我的毛病, 从小我一紧张就会笑。 哈。 ";
			link.l1 = "然后你被选为领袖? .. 好吧。 人们不会无缘无故地来到无人岛, 先生。 愿意解释一下吗? 我只给你一次机会。 ";
			link.l1.go = "Himenes_5";
		break;
		
		case "Himenes_5":
			string nationManName[4];
			nationManName[0] = "English";
			nationManName[1] = "French";
			nationManName[2] = "If you are seeing this, it's a bug";
			nationManName[3] = "Spaniard";
			dialog.text = "抱歉, 恐怕我没听清你的名字, 先生。 你是英国人吗? ";
			link.l1 = nationManName[sti(pchar.BaseNation)] + "。 这很重要吗? 现在先别管我的名字了。 ";
			link.l1.go = "Himenes_6";
		break;
		
		case "Himenes_6":
			dialog.text = "的确, 作为被西班牙天主教会认定为异端的人, 我们必须出现在神圣宗教法庭的正义审判前。 这就是为什么你的国籍对我们如此重要。 一位西班牙船长有义务将我们交给当地当局。 我们再也无法承受那样的事了! 哈-哈! ";
			if (sti(pchar.BaseNation) == SPAIN) dialog.text = "哈-哈-哈-哈-哈-哈! 我们的运气就是如此, 好吧, 反正我们也没什么可失去的了。 " + dialog.text;
			link.l1 = "幸运的是, 宗教法庭的事务与我无关。 那又怎样? 你们是异教徒吗? ";
			link.l1.go = "Himenes_7";
		break;
		
		case "Himenes_7":
			dialog.text = "不, 我向你发誓! 我们的社区在光荣的加的斯市从事手工业和贸易已有五十年了。 一切都很顺利, 我们甚至买了一艘船, 并获得了与我们帝国殖民地贸易的许可证。 现在我明白了, 那时我们跨越了某种界限, 并且对新的竞争对手... 及其手段完全没有准备。 ";
			link.l1 = "你们没有与欧洲的某些人分享商业利益, 结果整个社区被困在加勒比海的一个荒岛上? 我还以为我的生活已经够麻烦了... ";
			link.l1.go = "Himenes_8";
		break;
		
		case "Himenes_8":
			dialog.text = "不幸的是, 情况就是如此。 我们的社区由皈依新信仰的犹太人建立, 并获得了返回西班牙家园的机会。 这段古老的历史足以成为指控和官方审查的理由。 ";
			link.l1 = "所以你们逃跑了... ";
			link.l1.go = "Himenes_9";
		break;
		
		case "Himenes_9":
			dialog.text = "是的! 哈-哈-哈! 坐着我们自己的船! 我们正前往库拉索岛建立新家园和新事业。 然而, 我们低估了宗教法庭的执着, 并为此付出了沉重代价。 他们的信使在离这里不远的地方截住了我们, 命令船长把我们送回家... ";
			link.l1 = "该死! ";
			link.l1.go = "Himenes_10";
		break;
		
		case "Himenes_10":
			dialog.text = "还有更多! 哈! 我们的船长既不想麻烦把我们带回大西洋彼岸, 也不想在最近的港口以他的责任释放我们。 于是, 他做出了一个真正像所罗门一样的决定, 给了我们食物, 把我们送到这里, 就这样了。 ";
			link.l1 = "这确实是一个悲惨的故事, 毫无疑问。 让我们总结一下: 你们不能回家, 友好的殖民地会举报你们, 外国港口也不会欢迎你们 --这个地区的战争没有尽头。 你们有什么计划? ";
			link.l1.go = "Himenes_11";
		break;
		
		case "Himenes_11":
			dialog.text = "你描绘了一幅如此黯淡的图景, 先生, 我不知该说什么。 好像对我们来说没有比这个岛更好的地方了。 ";
			link.l1 = "我不这么认为, 有一个更好的岛。 ";
			link.l1.go = "Himenes_12";
		break;
		
		case "Himenes_12":
			dialog.text = "真的吗? 是西班牙的吗? ";
			link.l1 = "是我的。 由于命运的安排, 我在一个无人岛上继承了一个前海盗的藏身之处。 现在它是我的基地, 我想扩展它, 探索这个岛, 如果可能的话, 在那里建一个工厂..";
			link.l1.go = "Himenes_13";
		break;
		
		case "Himenes_13":
			dialog.text = "你是海盗吗? ";
			link.l1 = "是的。 ";
			link.l1.go = "Himenes_14_1";
			link.l2 = "不是。 ";
			link.l2.go = "Himenes_14_2";
		break;
		
		case "Himenes_14_1":
			dialog.text = "新世界! 确实, 我们在这里。 在老家, 他们说海盗是真正的恶魔, 甚至不是人类。 吃孩子, 强奸妇女, 剥去好天主教徒的皮。 这是真的吗? ";
			link.l1 = "这取决于星期几。 我们改天再讨论这个。 我在找人。 愿意在远离文明的地方生活几年的勤劳能干的人。 你对这样的事情感兴趣吗? ";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_14_2":
			dialog.text = "太可惜了, 因为我已经是个罪犯了, 我想至少见一个海盗。 ";
			link.l1 = "也许你还有机会。 我们改天再讨论。 我在寻找愿意在远离文明的地方生活几年的勤劳能干的人。 你对这样的事情感兴趣吗? ";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_15":
			dialog.text = "我们别无选择。 但这实际上不是一个坏选择。 如果你允许我们和平地生活和工作, 我们就接受。 并承诺有一天送我们回家! 先生, 给我们你的承诺, 并告诉我们你的名字..";
			link.l1 = "我, 船长" +GetFullName(pchar)+ ", 向你承诺。 ? ";
			link.l1.go = "Himenes_16";
		break;
		
		case "Himenes_16":
			dialog.text = "哈-哈! 我们得救了! 就这样吧! 我们有几个家庭, 大约30人。 所有人都识字, 受过手工业和商业训练。 ";
			link.l1 = "命运已经决定... 请上船! ";
			link.l1.go = "Himenes_17";
		break;
		
		case "Himenes_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto1", "none", "", "", "", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			IslaMona_TerksHimenesOnBoard();
		break;
		
		case "Himenes_18":
			dialog.text = "很高兴见到你, 罗德加先生。 看来我们得在一起生活和工作很长时间了... 天哪, 你怎么忍受这炎热的? ";
			link.l1 = "";
			link.l1.go = "Himenes_19";
		break;
		
		case "Himenes_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_14";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_20":
			dialog.text = "如果你不介意, 我插句话: 船长, 给我们一天时间安顿下来, 并快速检查库存和土地。 我相信罗德加先生对如何利用这片土地有很多想法。 我认为我们会成为一个好团队。 ";
			link.l1 = "你其实没有选择, 希梅内斯。 哈-哈.! ";
			link.l1.go = "Himenes_21";
		break;
		
		case "Himenes_21":
			dialog.text = "哈-哈-哈-哈-哈-哈! ";
			link.l1 = "";
			link.l1.go = "Himenes_22";
		break;
		
		case "Himenes_22":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_23":
			dialog.text = "是的, 船长? ";
			link.l1 = "希梅内斯, 有什么好消息给我吗? ";
			link.l1.go = "Himenes_24";
		break;
		
		case "Himenes_24":
			dialog.text = "船长, 这是一场噩梦。 当然, 你的房子还不错。 但除此之外... 住在这些棚屋里, 被杂草包围, 罗德加先生甚至不知道岛的另一端发生了什么! 难以置信! 哈-哈! ";
			link.l1 = "你是紧张还是真的在笑? ";
			link.l1.go = "Himenes_25";
		break;
		
		case "Himenes_25":
			dialog.text = "当然, 这很有趣! 这些年他们都在做什么? 首先, 我们需要完成建造几座房子, 并将这些棚屋修复到可以接受的条件。 人们需要体面地生活才能勤奋工作。 此外, 我会要求海盗对岛屿进行全面侦察。 也许这个地方不仅有岩石和沙子。 当一切完成后, 我就能确切地告诉你如何利用这片土地。 ";
			link.l1 = "听起来很棒! 我需要做什么? ";
			link.l1.go = "Himenes_26";
		break;
		
		case "Himenes_26":
			AddQuestRecordInfo("IslaMonaData", "1");
			dialog.text = "建造房屋。 家具和临时住所的材料。 我已经计算好了。 给, 拿着清单。 ";
			link.l1 = "令人印象深刻... ";
			link.l1.go = "Himenes_27";
		break;
		
		case "Himenes_27":
			dialog.text = "真的吗? 先生, 我们建过大教堂! 那才叫令人印象深刻... .";
			link.l1 = "我倾向于相信你! 只是别不小心在这里建一座大教堂。 我每次都得运很多材料来吗? ";
			link.l1.go = "Himenes_28";
		break;
		
		case "Himenes_28":
			dialog.text = "不, 这些材料可以维持一段时间, 但我们以后仍然需要带一些东西来。 如果你想避免将来出现这样的麻烦, 就带两倍的材料。 ";
			link.l1 = "好吧, 你说服了我。 我会看看我能做什么。 有最后期限吗? ";
			link.l1.go = "Himenes_29";
		break;
		
		case "Himenes_29":
			dialog.text = "没有, 先生。 但我恳请你不要拖延 --这是推动事情进展需要做的工作。 人们也需要地方住。 把材料装进货仓, 准备好后别忘了通知我。 哦, 我差点忘了! 和罗德加先生谈谈探索岛屿的事。 ";
			link.l1 = "同意! ";
			link.l1.go = "Himenes_30";
		break;
		
		case "Himenes_30":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			pchar.questTemp.IslaMona = "stalk";
			AddQuestRecord("IslaMona", "6");
		break;
		
		case "Himenes_31":
			dialog.text = "是的, 船长? ";
			if (IslaMona_CheckBuild()) // 已运送建筑材料
			{
				link.l1 = "你好, 希梅内斯。 检查仓库。 ";
				link.l1.go = "Himenes_32_1";
			}
			else // 未运送建筑材料
			{
				link.l1 = "你好, 希梅内斯。 我的人已经搜遍了整个岛。 你觉得怎么样? ";
				if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_32_2"; // 已运送食物和药品
				else link.l1.go = "Himenes_32_3";
			}
		break;
		
		case "Himenes_32_1":
			IslaMona_RemoveBuild(); // 立即从仓库移除材料
			dialog.text = "你出色地完成了这项任务! 如果你 ever in Cadiz, 来给我当仓库管理员吧! ";
			link.l1 = "我在路上了! 告诉我, 朋友, 你现在打算做什么? ";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_34_1"; // 已运送食物和药品
			else link.l1.go = "Himenes_34_2";
		break;
		
		case "Himenes_32_2":
			dialog.text = "船长先生, 让我们先处理住房和供应问题。 之后我们会制定计划。 我在仓库等待你清单上的货物。 ";
			link.l1 = "好的, 我明白。 首先, 我们需要建造房屋并整理这个地方。 货物很快就会到。 ";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_32_3":
			dialog.text = "船长, 让我们先处理住房和供应问题。 我们可以稍后制定计划。 我在仓库等待你清单上的货物。 你的海盗朋友也在等待食物和药品。 ";
			link.l1 = "好的, 我明白。 首先, 我们需要建造房屋并整理这个地方。 货物很快就会到。 还有给我的海盗朋友的。 ";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_33":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_31";
		break;
		
		case "Himenes_34_1":
			dialog.text = "给我们六个月, 船长, 你会认不出这个地方的。 ";
			link.l1 = "你是说六个月后这里既没有你, 也没有定居点, 也没有材料? 回头见! ";
			link.l1.go = "Himenes_37"; // 全部完成
		break;
		
		case "Himenes_34_2":
			dialog.text = "一旦你和这个强盗解决了问题, 我们就开始工作。 他向你请求了食物和药品, 我同意他的看法 --这是一个合理的要求。 ";
			link.l1 = "我会把你的话转告给他。 ";
			link.l1.go = "Himenes_35";
			AddQuestRecord("IslaMona", "11");
		break;
		
		case "Himenes_35":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_36";
		break;
		
		case "Himenes_36":
			dialog.text = "那么, 船长? 你照你的海盗要求做了吗? ";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food"))
			{
				link.l1 = "我已经和罗德加解决了所有问题。 岛屿侦察已经开始, 食物和药品在仓库里。 现在轮到你了。 ";
				link.l1.go = "Himenes_34_1";
			}
			else
			{
				link.l1 = "别担心, 我们会解决的。 我正在处理。 ";
				link.l1.go = "Himenes_35";
			}
		break;
		
		case "Himenes_37":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			DeleteAttribute(pchar, "questTemp.IslaMona.Food");
			pchar.questTemp.IslaMona = "build";
			AddQuestRecord("IslaMona", "12");
			SetFunctionTimerCondition("IslaMona_BuildDone", 0, 0, 180, false);
		break;
		
		case "Himenes_38":
			dialog.text = "船长先生! 你觉得怎么样? 哈-哈-哈? ";
			link.l1 = "好多了。 报告, 希梅内斯! ";
			link.l1.go = "Himenes_39";
		break;
		
		case "Himenes_39":
			dialog.text = "现在你实际上可以住在这里了! 我们清理并重建了所有的房子, 当然除了你的。 不是很豪华, 但不比我们在伯利兹的差。 ";
			link.l1 = "伯利兹早就属于英国了, 希梅内斯。 ";
			link.l1.go = "Himenes_40";
		break;
		
		case "Himenes_40":
			dialog.text = "我不确定房子是否知道这一点, 船长, 哈-哈! ";
			link.l1 = "现在你有地方住了, 定居点看起来也像人住的地方了。 接下来做什么? ";
			link.l1.go = "Himenes_41";
		break;
		
		case "Himenes_41":
			dialog.text = "看看周围, 和扬森先生谈谈, 然后回到我这里。 我们将讨论岛屿侦察的结果和我们的计划。 ";
			link.l1 = "你什么时候开始叫罗德加那个名字的? 你们不是一直意见不合吗? ";
			link.l1.go = "Himenes_42";
		break;
		
		case "Himenes_42":
			dialog.text = "我们仍然有分歧。 但我们必须以某种方式建立工作关系。 ";
			link.l1 = "谢谢你, 罗德里戈。 我很快就回来。 ";
			link.l1.go = "Himenes_43";
		break;
		
		case "Himenes_43":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload6", "none", "", "", "", 10.0); // 在新地点可能会有不同的定位器
			pchar.questTemp.IslaMona = "village";
		break;
		
		case "Himenes_44":
			dialog.text = "船长。 扬森先生。 ";
			link.l1 = "来吧, 告诉我岛屿侦察的结果。 ";
			link.l1.go = "Himenes_45";
		break;
		
		case "Himenes_45":
			dialog.text = "是的, 船长。 有些地方我亲自和我们的勘探者一起检查过。 那么, 我能说什么呢... 莫纳岛是一个贫穷。 狭小且相当无趣的岛屿。 几乎没有建筑空间, 地形崎岖陡峭, 几乎没有肥沃的土地。 三个海滩, 一个被淹没的洞穴, 茂密的灌木丛, 几只鹦鹉, 一群山羊, 还有我们... ";
			link.l1 = "你是认真的吗? 你是说这个岛上最有价值的资产是一群山羊? ";
			link.l1.go = "Himenes_46";
		break;
		
		case "Himenes_46":
			dialog.text = "哈-哈-哈-哈! 我要问, 先生! 哈-哈! 你没让我说完! ";
			link.l1 = "";
			link.l1.go = "Himenes_47";
		break;
		
		case "Himenes_47":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_38";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_48":
			dialog.text = "";
			link.l1 = "好的, 好的, 冷静下来继续说。 你知道, 我在这个地方投入了很多。 ";
			link.l1.go = "Himenes_49";
		break;
		
		case "Himenes_49":
			dialog.text = "并非徒劳! 洞穴里有足够的淡水, 有足够的土壤种植果树, 山羊可以繁殖。 有了捕鱼和你同伴的努力, 食物问题很快就会解决。 ";
			link.l1 = "所以, 你不需要再带更多的食物来了? 不错。 我希望这个地方可以在没有我不断照顾的情况下生活。 我们继续。 ";
			link.l1.go = "Himenes_50";
		break;
		
		case "Himenes_50":
			dialog.text = "你说的都对, 先生。 但这还不是全部消息! 首先, 罗德加先生想出了建造酒馆的主意。 我不知道这会给你带来什么, 但这个流氓正在搞什么鬼。 ";
			link.l1 = "他想喝醉, 就是这样! ";
			link.l1.go = "Himenes_51";
		break;
		
		case "Himenes_51":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_40";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_52":
			dialog.text = "其次, 总督峡原来比我们最初想象的要深得多。 我们可以建造一个完整的码头。 ";
			link.l1 = "我不太明白这对我有什么好处, 但这已经是个好消息了。 我希望这不是全部? ";
			link.l1.go = "Himenes_53";
		break;
		
		case "Himenes_53":
			dialog.text = "我们发现了一片巴科特树林。 一个理想的工厂地点。 ";
			link.l1 = "你让我高兴, 罗德里戈! 确实是个好消息! ";
			link.l1.go = "Himenes_54";
		break;
		
		case "Himenes_54":
			dialog.text = "现在就这些了, 先生。 我们将来可能会有更多想法。 你明白, 最好的想法来自工作! 你想询问什么? ";
			link.l1 = "告诉我关于巴科特的事。 听起来很有希望。 ";
			link.l1.go = "Himenes_55";
		break;
		
		case "Himenes_55":
			dialog.text = "据我估计, 一个小工厂将能够提取这种有价值的木材数年。 储量不大, 但资源是战略性的。 我们可以在岛的中心清理一块场地, 并在那里建造一座带仓库的房子。 这是一个开始。 除了建筑材料, 我们还需要大约15副手铐和火枪。 ";
			link.l1 = "我们为什么需要手铐? 为什么正好十五副? ";
			link.l1.go = "Himenes_56";
		break;
		
		case "Himenes_56":
			dialog.text = "这是苦工, 先生。 我甚至会说, 这是奴隶劳动。 ";
			link.l1 = "我明白了。 他-他... ";
			link.l1.go = "Himenes_57_1";
			link.l2 = "你疯了吗? 我不会成为奴隶主! ";
			link.l2.go = "Himenes_57_2";
		break;
		
		case "Himenes_57_1":
			dialog.text = "";
			link.l1 = "我们为什么需要火枪? 为什么只有一把? ";
			link.l1.go = "Himenes_59";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Himenes_57_2":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_42";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Himenes_58":
			dialog.text = "我同意海盗的看法, 先生。 我不理解你, 船长。 这个地区的整个经济都建立在奴隶劳动的基础上, 而且还会持续很多年。 我们有什么不同? ";
			link.l1 = "我会做出决定。 同时, 告诉我你为什么需要火枪? 为什么正好一把? ";
			link.l1.go = "Himenes_59";
		break;
		
		case "Himenes_59":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_60":
			dialog.text = "当然, 工厂需要维护。 随着它的建设, 这个岛将有一个以你为主要贸易伙伴的经济。 我们自己会养活奴隶, 但你必须从自己的口袋里支付安全和生产费用。 定居者每批将收取一百杜布隆和五瓶葡萄酒。 关于安全问题, 与扬森先生协商。 ";
			link.l1 = "";
			link.l1.go = "Himenes_61";
		break;
		
		case "Himenes_61":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_62":
			dialog.text = "每月四十度量。 黄金是为将来准备的。 有一天你会把我们从这里带走, 记住你的承诺? 任何工作都必须得到报酬, 用你的杜布隆, 我们将支付猎人和工匠在定居点的工作。 这样我们就有了贸易, 随之而来的是文明! ";
			link.l1 = "这就是精神! 好吧! 目前, 一切听起来都很有说服力... ";
			link.l1.go = "Himenes_63";
		break;
		
		case "Himenes_63":
			dialog.text = "你还对什么感兴趣? ";
			link.l1 = "那么, 酒馆是怎么回事? 为什么不建一个剧院? ";
			link.l1.go = "Himenes_64";
		break;
		
		case "Himenes_64":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_65":
			dialog.text = "船长, 我警告过他你不会喜欢这个主意。 但这是唯一的选择。 你有... 呃, 镇上最大的房子, 我们会把一楼改造成大厅, 设置桌子和厨房。 我们会把饮料和食物储存在房子下面的洞穴里。 我们有人做饭和演奏音乐。 二楼仍然是你的, 我们不会碰它。 我们会自己把你一楼的东西搬到楼上。 ";
			link.l1 = "好吧。 那么酒馆到底会给我们带来什么? ";
			link.l1.go = "Himenes_66";
		break;
		
		case "Himenes_66":
			dialog.text = "我们会有一些文化生活, 你将有机会在加勒比海的中心地带拥有大约三百人的后备军。 ";
			link.l1 = "有趣... 我会考虑的。 ";
			link.l1.go = "Himenes_67";
		break;
		
		case "Himenes_67":
			dialog.text = "你还对什么感兴趣? ";
			link.l1 = "那么, 码头呢? ";
			link.l1.go = "Himenes_68";
		break;
		
		case "Himenes_68":
			dialog.text = "很简单。 我们会清除总督峡的礁石, 安装信号照明, 建造码头。 扬森先生声称你可以在海湾里停泊三艘船, 或者一艘一等船。 而且你回到这里会更愉快, 不必每次都沿着海滩拖小艇。 ";
			link.l1 = "那太好了。 ";
			link.l1.go = "Himenes_69";
		break;
		
		case "Himenes_69":
			dialog.text = "你想知道什么? ";
			link.l1 = "现在就这些。 我决定建什么后会回来。 ";
			link.l1.go = "Himenes_70";
		break;
		
		case "Himenes_70":
			dialog.text = "船长先生, 拿着这份文件。 我冒昧地写下了所有细节, 以免重复十几次。 研究一下, 带来材料, 并设定任务。 ";
			link.l1 = "谢谢你, 罗德里戈。 ";
			link.l1.go = "Himenes_71";
		break;
		
		case "Himenes_71":
			DialogExit();
			IslaMona_HouseDialogFin();
		break;
		
		case "Himenes_72": // 希梅内斯作为工厂建设者和管理者的节点
			if (CheckAttribute(pchar, "questTemp.IslaMona.RecordPart")) // 保护莫纳岛后 - 需要再10个奴隶
			{
				dialog.text = "船长先生, 我们需要10个奴隶在工厂工作 - 我告诉过你, 你没忘记吧? ";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 10)
				{
					link.l1 = "已经送达。 卸下他们并开始生产。 ";
					link.l1.go = "Himenes_plantation_12";
				}
				else
				{
					link.l1 = "我的记忆完好。 我很快就会带来。 ";
					link.l1.go = "Himenes_plantation_14";
				}
				break;
			}
			dialog.text = "那么, 船长先生, 你觉得怎么样? ";
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Harbour"))
			{
				link.l1 = "我想要一个干净的海湾和一个安全的码头。 它将是我舰队的基地。 ";
				link.l1.go = "Himenes_harbour";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Tavern"))
			{
				link.l2 = "继续建造酒馆。 每个人都会喜欢它, 我也可以在这里保留一支后备军。 ";
				link.l2.go = "Himenes_tavern";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Plantation"))
			{
				link.l3 = "开始建造种植园。 是时候收回投资了。 ";
				link.l3.go = "Himenes_plantation";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Slave") && IslaMona_CheckSlave())
			{
				link.l4 = "罗德里戈, 特别有价值的专家和设备已送达工厂。 你可以开始工作了。 ";
				link.l4.go = "Himenes_plantation_7";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory.Part") && sti(pchar.questTemp.IslaMona.Factory.Part) > 0)
			{
				link.l4 = "罗德里戈, 我来拿我的铁材。 ";
				link.l4.go = "Himenes_bacaut";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Factory") && !CheckAttribute(pchar, "questTemp.IslaMona.Church"))
			{
				link.l5 = "罗德里戈, 我们完成伟大的建设了吗? ";
				link.l5.go = "Himenes_church";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "start" && IslaMona_CheckChurch())
			{
				link.l5 = "罗德里戈, 我们来建你的教堂吧。 ";
				link.l5.go = "Himenes_church_10";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "Wait_candles" && IslaMona_CheckCandles())
			{
				link.l5 = "罗德里戈, 我带来了你要的教堂物品。 ";
				link.l5.go = "Himenes_church_10_3";
			}
			link.l10 = "目前没有... ";
			link.l10.go = "Himenes_73";
		break;
		
		case "Himenes_harbour":
			if (IslaMona_CheckHarbour())
			{
				dialog.text = "材料已备, 一切就绪。 建设将需要4个月。 ";
				link.l1 = "你不着急, 是吗! 好吧, 祝你好运, 罗德里戈。 ";
				link.l1.go = "Himenes_harbour_1";
			}
			else
			{
				dialog.text = "恐怕仓库里材料不够。 请再检查一下清单。 ";
				link.l1 = "我会处理的。 ";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_tavern":
			if (IslaMona_CheckTavern())
			{
				dialog.text = "材料已备, 一切就绪。 建设将需要3个月。 ";
				link.l1 = "你不着急, 是吗! 好吧, 祝你好运, 罗德里戈。 ";
				link.l1.go = "Himenes_tavern_1";
			}
			else
			{
				dialog.text = "恐怕仓库里材料不够。 请再检查一下清单。 ";
				link.l1 = "我会处理的。 ";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_plantation":
			if (IslaMona_CheckPlantation())
			{
				dialog.text = "材料已备, 一切就绪。 建设将需要6个月。 ";
				link.l1 = "你不着急, 是吗! 祝你好运, 罗德里戈。 ";
				link.l1.go = "Himenes_plantation_1";
			}
			else
			{
				dialog.text = "恐怕仓库里材料不够。 请再检查一下清单。 ";
				link.l1 = "我会处理的。 ";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_73":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_harbour_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveHarbour();
			pchar.questTemp.IslaMona.Harbour = "true";
			SetFunctionTimerCondition("IslaMona_BuildHarbour", 0, 0, 120, false);
		break;
		
		case "Himenes_harbour_2":
			dialog.text = "欢迎, 船长。 你觉得你的新港口怎么样? ";
			if (stf(environment.time) > 22.0 || stf(environment.time) < 5.0)
			{
				link.l1 = "天黑了, 罗德里戈! 我们差点撞坏了你称赞的码头! 至少你把它照亮了, 干得好! ";
				link.l1.go = "Himenes_harbour_3";
			}
			else
			{
				link.l1 = "不错, 罗德里戈! 看起来是小事, 但沿着这些木板走到岸边很舒服。 而且海湾也更容易导航了。 那么, 我猜现在我可以在这个小海湾里停泊更多的船了? ";
				link.l1.go = "Himenes_harbour_4";
			}
		break;
		
		case "Himenes_harbour_3":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_51";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_harbour_4":
			sld = characterFromId("Islamona_carpenter");
			sld.portman.info = "true"; // 如果到目前为止还没有谈论停泊条件
			pchar.questTemp.IslaMona.Harbour = "done"; // 标志 - 码头已建成并交付
			dialog.text = "是的, 船长。 我必须说, 这让人感到某种自豪。 请随时告诉我你想如何继续我们的大型建设项目。 ";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "complete") // 如果与工厂交付交叉
			{
				link.l1 = "说到建设。 我的工厂现在也应该完成了。 对吗, 罗德里戈? ";
				link.l1.go = "Himenes_plantation_2";
			}
			else
			{
				link.l1 = "... ";
				link.l1.go = "Himenes_harbour_5";
			}
		break;
		
		case "Himenes_harbour_5":
			DialogExit();
			IslaMona_HarbourClear();
		break;
		
		case "Himenes_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveTavern();
			pchar.questTemp.IslaMona.Tavern = "true";
			SetFunctionTimerCondition("IslaMona_BuildTavern", 0, 0, 90, false);
		break;
		
		case "Himenes_tavern_2":
			dialog.text = "喝-嗝! 船长! 我们在这里庆祝! ";
			link.l1 = "罗德加。 罗德里戈。 哦, 该死! ";
			link.l1.go = "Himenes_tavern_3";
		break;
		
		case "Himenes_tavern_3":
			dialog.text = "怎么了, 船-船-船长? 你不喜欢墙壁的颜色吗? ";
			link.l1 = "刚才我才意识到你们两个名字一样! 哈-哈-哈! 一个西班牙人和一个海盗, 同名, 在一个荒岛上建了一个酒馆, 一起喝酒, 好像印度神会吞噬所有人, 在日出前结束世界! 哈-哈! 我和你们一起! ";
			link.l1.go = "Himenes_tavern_4";
		break;
		
		case "Himenes_tavern_4":
			dialog.text = "哈-哈-哈! 太对了! 得分! ";
			link.l1 = "得分! ";
			link.l1.go = "Himenes_tavern_5";
		break;
		
		case "Himenes_tavern_5":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_ReloadTavern();
		break;
		
		case "Himenes_plantation_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemovePlantation();
			pchar.questTemp.IslaMona.Plantation = "true";
			SetFunctionTimerCondition("IslaMona_BuildPlantation", 0, 0, 180, false);
		break;
		
		case "Himenes_plantation_2":
			dialog.text = "一切就绪。 我们走吧? 让我带你看看你的工厂。 ";
			link.l1 = "带路。 ";
			link.l1.go = "Himenes_plantation_3";
		break;
		
		case "Himenes_plantation_3":
			DialogExit();
			pchar.questTemp.IslaMona.Plantation.Harbour = "true"; // 码头和工厂交付重叠
			IslaMona_PlantationGo();
		break;
		
		case "Himenes_plantation_4":
			dialog.text = "船长, 几乎一切都准备好开始运营了。 工人住房, 原材料仓库, 加工区 - 一座值得骄傲的工厂已经建成。 我们已经在丛林中标记了最有希望的树木用于砍伐。 带来十五名工人和约定的物资 - 15副手铐和火枪, 我们就开始工作。 ";
			link.l1 = "我们? 你是说奴隶? ";
			link.l1.go = "Himenes_plantation_5";
		break;
		
		case "Himenes_plantation_5":
			dialog.text = "哈! 奴... 奴隶会砍伐, 定居者会加工, 海盗会守卫。 每个人都有工作 - 你已经开始了一项严肃的事业, 船长。 ";
			link.l1 = "几乎就像应许之地, 是吧。 等待货物, 我该去打猎了。 ";
			link.l1.go = "Himenes_plantation_6";
		break;
		
		case "Himenes_plantation_6":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Plantation.Slave = "true"; // 运送奴隶。 手铐和火枪以启动工厂
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "IslaMona_factoria_residence", "sit", "sit1", "IslaMona_PlantationHouse", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5);
			pchar.questTemp.IslaMona.Plantation = "done"; // 标志 - 工厂已建成并交付
		break;
		
		case "Himenes_plantation_7":
			dialog.text = "悲惨的命运... 他们永远不会离开这个地方。 ";
			link.l1 = "罗德加... 我是说, 罗德里戈! 首先, 他们可能会离开。 其次, 如果你在特克斯遇到其他人, 你的命运也不会更好。 ";
			link.l1.go = "Himenes_plantation_8";
		break;
		
		case "Himenes_plantation_8":
			dialog.text = "我非常清楚这一点, 船长。 我不会忘记。 让我告诉你这个工厂的运营情况。 从下个月15日开始, 我们将交付四十根加工过的巴科特原木。 当然, 你不必每个月都来取货 - 所有批次都会存放在这里, 在工厂等你。 ";
			link.l1 = "那么, 我可以一次取几批? ";
			link.l1.go = "Himenes_plantation_9";
		break;
		
		case "Himenes_plantation_9":
			dialog.text = "当然是在合理范围内 - 不要离开太久。 人们不会在不知道唯一的顾客是否还活着的情况下工作多年。 我想我们会在暂停运营前交付六批。 ";
			link.l1 = "我必须一次取所有货物吗? 价格呢, 提醒我一下? ";
			link.l1.go = "Himenes_plantation_10";
		break;
		
		case "Himenes_plantation_10":
			dialog.text = "是的, 一次取完。 标准巴科特原木的价格是十杜布隆。 此外, 每批你必须给五瓶好朗姆酒和同样数量的葡萄酒瓶。 罗德加声称你在世界上任何其他地方都找不到这样的价格。 ";
			link.l1 = "确实, 我同意! 谢谢你, 罗德里戈。 我们开始工作吧! ";
			link.l1.go = "Himenes_plantation_11";
		break;
		
		case "Himenes_plantation_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Slave");
			AddQuestRecordInfo("Unique_Goods", "5");
			IslaMona_RemoveSlave();
		break;
		
		case "Himenes_plantation_12":
			dialog.text = "太好了! 现在我们将再次开始工作! ";
			link.l1 = "好的。 ";
			link.l1.go = "Himenes_plantation_13";
		break;
		
		case "Himenes_plantation_13":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_FactoryReActivar(); // 启动工厂
		break;
		
		case "Himenes_plantation_14":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_bacaut":
			dialog.text = "当然, 船长, 拿去吧。 我们为下一个日期准备了以下批次: "+sti(pchar.questTemp.IslaMona.Factory.Part)+", 也就是"+sti(pchar.questTemp.IslaMona.Factory.Goods)+"根原木。 因此, 你欠我们"+sti(pchar.questTemp.IslaMona.Factory.Dublon)+"杜布隆, "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+"瓶朗姆酒, 和"+sti(pchar.questTemp.IslaMona.Factory.Bottle)+"瓶葡萄酒, 你都有吗? ";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Factory.Dublon) && PCharItemsTotal("potionrum") >= sti(pchar.questTemp.IslaMona.Factory.Bottle) && PCharItemsTotal("potionwine") >= sti(pchar.questTemp.IslaMona.Factory.Bottle))
			{
				link.l1 = "当然。 这是你的付款。 ";
				link.l1.go = "Himenes_bacaut_1";
			}
			else
			{
				link.l1 = "看来我不是都有。 我马上带来。 ";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_1":
			if (IslaMona_CheckBacautSpace())
			{
				dialog.text = "太好了。 我们将把巴科特从工厂运到你的仓库, 你可以随时从那里取货。 ";
				link.l1 = "太好了。 准备下一批。 ";
				link.l1.go = "Himenes_bacaut_2";
			}
			else
			{
				dialog.text = "等等, 船长! 你的仓库满了 - 我们无法在那里装载所有收获的巴科特。 请清理仓库空间 - 然后再回来找我。 ";
				link.l1 = "好的, 我会处理的。 ";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_2":
			dialog.text = "当然, 船长! ";
			link.l1 = "... ";
			link.l1.go = "Himenes_73";
			IslaMona_FactoryTrade();
		break;
		
		case "Himenes_church":
			dialog.text = "哈! 船长, 恐怕再建造任何东西都是不必要的愚蠢和奢侈。 除非... ";
			link.l1 = "除非什么? ";
			link.l1.go = "Himenes_church_1";
		break;
		
		case "Himenes_church_1":
			dialog.text = "船长, 我不好意思问这个... 你已经在这个地方投入了巨额资金! ";
			link.l1 = "妓院? ";
			link.l1.go = "Himenes_church_2_1";
			link.l2 = "教堂? ";
			link.l2.go = "Himenes_church_2_2";
		break;
		
		case "Himenes_church_2_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "我以圣地亚哥的名义发誓, 那不会坏! 但在第一个晚上, 我们的女人会把它烧掉。 连同我们一起。 不, 船长, 我在说教堂。 是的, 我们有体面的住房和报酬, 有大海和娱乐, 有家人和朋友。 但仍然缺少一些东西, 你明白吗? ";
			link.l1 = "我可以想象。 ";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_2_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Defence", 500);
			dialog.text = "你看穿了我, 船长。 是的, 我们有体面的住房和报酬, 有大海和娱乐, 有家人和朋友。 但仍然缺少一些东西, 你明白吗? ";
			link.l1 = "我可以想象。 ";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_3":
			dialog.text = "正是。 没有你的帮助, 我们无法建造上帝的殿堂。 这样的地方必须是特殊的, 必须是超凡脱俗的。 因此, 它应该是昂贵的。 我们需要蜡烛。 金锭。 琥珀, 当然还有建筑材料, 而且不是便宜的材料。 这不会给你带来任何利润, 所以我不敢开口要求。 ";
			link.l1 = "那么, 你需要带一位牧师到这里来吗? ";
			link.l1.go = "Himenes_church_4";
		break;
		
		case "Himenes_church_4":
			dialog.text = "不。 ";
			link.l1 = "你们中间已经有牧师了吗? ";
			link.l1.go = "Himenes_church_5";
		break;
		
		case "Himenes_church_5":
			dialog.text = "没有, 船长。 我想你已经明白了一切。 ";
			link.l1 = "那么, 宗教法庭的神父们迫害你们有理由吗? 你们是异端吗? ";
			link.l1.go = "Himenes_church_6";
		break;
		
		case "Himenes_church_6":
			dialog.text = "根据教会法, 我们是最恶劣的异端。 我们不相信与上帝沟通必须通过这个世界的中介。 ";
			link.l1 = "通过这个世界? ";
			link.l1.go = "Himenes_church_7";
		break;
		
		case "Himenes_church_7":
			dialog.text = "船长, 我们不是撒旦教徒, 我们的社区也不是教派。 我们和你一样是基督徒, 但我们看待事物的视角非常广泛。 根据一些非常有学问和可敬的人说, 过于广泛了。 如果你心中有开放和理解的空间, 那么我会告诉你更多。 但现在, 先拿着这份清单。 以防万一。 ";
			link.l1 = "你应该早点告诉我这些, 罗德里戈。 我不想有一天回来, 看到在我的土地上举行女巫的安息日或诞生新的信仰! 在你等待的时候 --我会做出决定。 ";
			link.l1.go = "Himenes_church_8_1";
			link.l2 = "令人印象深刻的清单。 我开始明白为什么神父们需要这么多钱了! 我会考虑你的提议, 罗德里戈, 然后做出决定。 ";
			link.l2.go = "Himenes_church_8_2";
		break;
		
		case "Himenes_church_8_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "";
			link.l1 = "如果决定是肯定的, 我会把你清单上的所有货物都运到仓库, 并把珍宝摆在你面前的桌子上。 ";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_8_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			dialog.text = "";
			link.l1 = "如果决定是肯定的, 我会把你清单上的所有货物都运到仓库, 并把珍宝摆在你面前的桌子上。 ";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_9":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "start";
			AddQuestRecord("IslaMona", "14");
			AddQuestRecordInfo("IslaMonaData", "3");
		break;
		
		case "Himenes_church_10":
			dialog.text = "我代表我们整个社区感谢你, 船长。 你不会后悔的, 我发誓! ";
			link.l1 = "如果你建得太简陋, 我才会后悔。 ";
			link.l1.go = "Himenes_church_10_1";
		break;
		
		case "Himenes_church_10_1":
			dialog.text = "船长, 所有建筑材料都已入库! 一旦你带来清单上的奢侈品, 我们就开始建造。 它们将用于制作饰品和仪式工具。 再次非常感谢你, 船长! Muchas gracias! ";
			link.l1 = "不客气! ";
			link.l1.go = "Himenes_church_10_2";
		break;
		
		case "Himenes_church_10_2":
			DialogExit();
			IslaMona_RemoveChurch();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "Wait_candles";
			pchar.questTemp.IslamonaChurch.GoldNugget = 50;
			pchar.questTemp.IslamonaChurch.Candle = 100;
			pchar.questTemp.IslamonaChurch.Amber = 30;
			pchar.questTemp.IslamonaChurch.BlueAmber = 1;
		break;
		
		case "Himenes_church_10_3":
			IslaMona_RemoveCandles();
			string sAdd = "";
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Candle)+ " 蜡烛,";
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Amber)+ " 琥珀,";
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
			{
				sAdd += " "+ sti(pchar.questTemp.IslamonaChurch.GoldNugget) + " 金锭,";
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
			{
				sAdd += " 和一块蓝色琥珀";
			}
			if(sAdd == "")
			{
				dialog.text = "非常感谢你, 船长! 一切就绪, 我们开始建造。 两个月后回来参加第一次礼拜。 哦, 还有一件事, 葡萄熟了! 我们会酿自制葡萄酒, 举行庆祝活动, 为你设宴! ";
				link.l1 = "我想我们都值得庆祝一下。 两个月后我会回来。 ";
				link.l1.go = "Himenes_church_12";
			}
			else
			{
				dialog.text = "船长, 还剩下"+sAdd+"。 ";
				link.l1 = "当然, 请再给我一些时间。 老实说, 如果不是因为蜡烛, 我会以为你要埋藏宝藏。 ";
				link.l1.go = "Himenes_church_11";
			}
		break;
		
		case "Himenes_church_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_church_12":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "build";
			AddQuestRecord("IslaMona", "15");
			//IslaMona_RemoveChurch();
			SetFunctionTimerCondition("IslaMona_ChurchComplete", 0, 0, 60, false);
		break;
		
		case "Himenes_church_13":
			dialog.text = "哈-哈-哈-哈-哈-哈-哈-哈-哈-哈-哈! ";
			link.l1 = "我还以为你已经改掉了那个愚蠢的习惯。 ";
			link.l1.go = "Himenes_church_14";
		break;
		
		case "Himenes_church_14":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "我们不必在这里坐几个星期等待事件发展。 ";
			else sTemp = "不是每个人都必须参加战斗。 ";
			dialog.text = "哈-哈-哈-哈-哈... 哈。 我也这么想, 船长! 罗德加是对的, 你的存在已经意味着, " + sTemp + "";
			link.l1 = "我已经知道发生了什么。 有伤亡吗? ";
			if (GetCharacterIndex("Mirabella") != -1) link.l1.go = "Himenes_church_15";
			else link.l1.go = "Himenes_church_16";
		break;
		
		case "Himenes_church_15":
			DialogExit();
			sld = characterFromId("Mirabella"); 
			sld.dialog.currentnode = "mirabelle_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_16":
			dialog.text = "别这么担心, 罗德加。 这不是你的错, 燧发枪兵来得太快了。 我们无论如何也无法将他们挡在防线后面, 也没有时间把他们全部杀死。 ";
			link.l1 = "西班牙人呢? ";
			link.l1.go = "Himenes_church_17";
		break;
		
		case "Himenes_church_17":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) // 自己解决了问题
			{
				dialog.text = "他们只有三个人冲到了我们这里, 只有一个人幸存。 船长本人! 显然是个非常老练的海军士兵。 但他现在还帮不了我们 --他至少还得卧床几天。 顺便说一句, 船长, 我们听到了枪声, 从你的样子来看, 你也听到了。 ";
				link.l1 = "可以这么说。 不速之客显然没料到会受到如此意外的拜访, 被打回了海里。 ";
				link.l1.go = "Himenes_church_20";
			}
			else
			{
				dialog.text = "他们只有三个人冲到了我们这里, 只有一个人幸存。 船长本人! 显然是个非常老练的海军士兵。 但他现在还帮不了我们 --他至少还得卧床几天。 ";
				if (i >= 50) 
				{
					link.l1 = "上次我在这里留下了不少人站岗, 所以你们的人应该比燧发枪兵多得多。 为什么不直接把他们全部打回海里? ";
					link.l1.go = "Himenes_church_17_1";
				}
				else 
				{
					link.l1 = "好吧, 我们来解决这个问题。 计划是这样的: 我马上把他们引诱出来进行公开突袭。 没有必要拖延。 准备好霰弹和火枪, 海盗守在门口, 其他人待在家里 --坐稳了。 ";
					link.l1.go = "Himenes_church_18";
				}
			}
		break;
		
		case "Himenes_church_17_1":
			dialog.text = "船长, 他们都是职业士兵, 有指挥官。 而我们甚至没有合适的武器。 是的, 当然, 我们可以用人数压倒他们, 但我们至少会损失两倍的人, 而每个人在这里都很宝贵, 都很需要。 ";
			link.l1 = "好吧, 我们来解决这个问题。 计划是这样的: 我马上把他们引诱出来进行公开突袭。 没有必要拖延。 准备好霰弹和火枪, 海盗守在门口, 其他人待在家里 --坐稳了。 ";
			link.l1.go = "Himenes_church_18";
		break;
		
		case "Himenes_church_18":
			dialog.text = "船长, 我们准备战斗! ";
			link.l1 = "我知道, 罗德里戈。 但你没让我说完: 如果有一个敌人冲破大门, 你们必须从四面八方冲向他。 在战斗中, 你中弹或被碎片击中的机会正在减少。 还有问题吗? ";
			link.l1.go = "Himenes_church_19";
		break;
		
		case "Himenes_church_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_68";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_20":
			dialog.text = "干得好! 当然, 你的同胞遭遇如此不幸的命运令人不快。 但我很感激你再次站在我们这边。 ";
			link.l1 = "这并不容易, 罗德里戈。 普通人会称之为背叛, 他们是对的。 ";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "这是我的土地, 罗德里戈。 无论面对谁, 都必须始终捍卫它。 ";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20a":
			dialog.text = "是的, 老罗德里戈离开加的斯时, 没想到在新世界会遇到这样的冒险。 ";
			link.l1 = "别告诉我。 有时我仍然有完全相同的想法。 ";
			link.l1.go = "Himenes_church_20b";
		break;
		
		case "Himenes_church_20b":
			dialog.text = "当然, 你的同胞遭遇如此不幸的命运令人不快。 但我很感激你再次站在我们这边。 ";
			link.l1 = "这并不容易, 罗德里戈。 普通人会称之为背叛, 他们是对的。 ";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "这是我的土地, 罗德里戈。 无论面对谁, 都必须始终捍卫它。 ";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "我明白, 船长。 那么请允许我向你简要介绍一下你不在时我们定居点的情况。 ";
			link.l1 = "真的吗? 等等... 船长? ";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_20_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			dialog.text = "我明白, 船长。 那么请允许我向你简要介绍一下你不在时我们定居点的情况。 ";
			link.l1 = "真的吗? 等等... 船长? ";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_21":
			dialog.text = "无意冒犯。 只是罗德加把这个词说得太动听了, 我也想试试。 非常... 海盗风格。 ";
			link.l1 = "没问题, 只是惊讶。 那么这里发生了什么? ";
			link.l1.go = "Himenes_church_22";
		break;
		
		case "Himenes_church_22":
			dialog.text = "首先, 我们建了教堂。 只需要一分钟, 进来吧。 有东西给你看。 你做了一件伟大的事, 船长。 你可能不这么认为, 但能够与上帝沟通对我们来说非常非常重要。 从今天起, 我们称莫纳岛为我们的hogar。 ";
			link.l1 = "家, 甜蜜的家? 我一定会看看。 我带的那些蜡烛不是白拿的吧? ";
			link.l1.go = "Himenes_church_23";
		break;
		
		case "Himenes_church_23":
			dialog.text = "不是白拿的! 其次, 工厂被毁了 --我们失去了所有劳动力。 你得带一批新的奴隶来。 幸运的是, 在重新评估工作效率后, 我们得出结论, 十个奴隶就足够了。 所以, 你少点麻烦。 ";
			link.l1 = "好吧。 还有别的吗? ";
			link.l1.go = "Himenes_church_24";
		break;
		
		case "Himenes_church_24":
			dialog.text = "庆祝活动一切就绪。 嗯, 差不多: 我们需要在这里打扫一下, 埋葬那些不幸灵魂的尸体... 所以明天来教堂, 我们开始。 ";
			link.l1 = "去教堂? 开始派对的奇怪地方。 你打算求婚吗, 罗德里戈? ";
			link.l1.go = "Himenes_church_25";
		break;
		
		case "Himenes_church_25":
			dialog.text = "哈-哈! 不, 船长, 尽管我们有些女孩不会介意。 如果你愿意, 我们也不介意。 ";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				link.l1 = "";
				link.l1.go = "Himenes_church_25_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")))
				{
					link.l1 = "";
					link.l1.go = "Himenes_church_25_2";
				}
				else
				{
					link.l1 = "同意, 我们明天去教堂。 当然是去祈祷。 ";
					if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common") || CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) link.l1.go = "Himenes_church_28";
					else link.l1.go = "Himenes_church_26";
				}
			}
		break;
		
		case "Himenes_church_25_1":
			DialogExit();
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_25_2":
			DialogExit();
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_26":
			dialog.text = "还有一件事, 船长。 庆祝活动前, 先去处理囚犯。 必须做出决定, 我知道这无论如何都令人不快。 ";
			link.l1 = "好吧。 我现在就去。 ";
			link.l1.go = "Himenes_church_27";
		break;
		
		case "Himenes_church_27":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefFraPrisoner"); /// 确定定位器
		break;
		
		case "Himenes_church_28":
			DialogExit();
			WaitDate("", 0, 0, 0, 3, 5); //转动时间
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			IslaMona_DefBattleLightClear();
			DoQuestReloadToLocation("IslaMona_town", "quest", "detector1", "");
		break;
		
		case "Himenes_church_29":
			dialog.text = "大家都在! 先生, 我们不知道你最初想从这个地方得到什么, 也不知道你现在如何看待它。 对我们来说, 这里首先是一个被迫的避难所, 现在它已成为一个真正的家。 你的水手。 海盗和逃亡的西班牙异端住在这里。 在世界上任何其他地方, 我们早就互相割喉了。 但在这里, 我们是朋友, 一起工作, 享受生活。 莫纳岛对我们任何人来说都不是这个世界地图上的终点, 但也许我们会在这里度过生命中最快乐。 最有成效的岁月。 这是你的功劳, 你的土地, 你的人民。 非常感谢你, " +pchar.name+ "! ";
			link.l1 = "";
			link.l1.go = "Himenes_church_30";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_30":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_86";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "Himenes_church_31":
			dialog.text = "好了, 好了。 船长, 我们为你收集了礼物 --许多有用和令人愉快的东西。 有些是我们带来的, 有些是我们自己做的。 请真诚地接受这份礼物, 其余的我们将用辛勤工作来回报。 ";
			link.l1 = "谢谢你... 我没想到会这样。 在我的冒险中, 如此光明的时刻和简单的人性太少了... 这对我意义重大, 相信我。 ";
			link.l1.go = "Himenes_church_32";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_32":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "GunEchin", 10);
			TakeNItems(pchar, "slave_01", 10);
			TakeNItems(pchar, "grenade", 10);
			TakeNItems(pchar, "obereg_7", 1);
			TakeNItems(pchar, "purse3", 1);
			TakeNItems(pchar, "jewelry47", 1);
			TakeNItems(pchar, "jewelry52", 1);
			TakeNItems(pchar, "berserker_potion", 1);
			TakeNItems(pchar, "potion5", 10);
			TakeNItems(pchar, "cannabis7", 1);
			dialog.text = "现在 --回去工作! ";
			link.l1 = "不, 现在 --去酒馆! 罗德里戈, 我们走! ";
			link.l1.go = "Himenes_church_33_1";
			link.l2 = "是的, 让我们再享受一下这美好的时刻。 ";
			link.l2.go = "Himenes_church_33_2";
		break;
		
		case "Himenes_church_33_1":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// 确定定位器
		break;
		
		case "Himenes_church_33_2":
			DialogExit();
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_terrain");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("IslaMona_ChurchTavernExit", 45.0);
		break;
		
		case "Himenes_74":
			dialog.text = "哈-哈! 嗝! ";
			link.l1 = "顺便说一句, 我看到你几乎不再对任何事情疯狂大笑了。 加勒比的新鲜空气? ";
			link.l1.go = "Himenes_75";
		break;
		
		case "Himenes_75":
			dialog.text = "更像是罗德加的腐蚀性影响。 看着他, 我学会了把一切都搞砸。 ";
			link.l1 = "";
			link.l1.go = "Himenes_76";
		break;
		
		case "Himenes_76":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_90";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_77":
			dialog.text = "我认识那里很多受人尊敬的人。 ";
			link.l1 = "";
			link.l1.go = "Himenes_78";
		break;
		
		case "Himenes_78":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_93";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_79":
			dialog.text = "不, 我宁愿继续喝朗姆酒, 盯着你。 ";
			link.l1 = "";
			link.l1.go = "Himenes_80";
		break;
		
		case "Himenes_80":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_96";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_81":
			dialog.text = "船长! 嗝! ";
			link.l1 = "你也好, 罗德里戈。 看来你昨晚很热闹? ";
			link.l1.go = "Himenes_82";
		break;
		
		case "Himenes_82":
			dialog.text = "更好... 别问。 一个月... 不喝酒。 哦。 我有消息! 船长... 醒了。 ";
			link.l1 = "唯一幸存的西班牙人? ";
			link.l1.go = "Himenes_83";
		break;
		
		case "Himenes_83":
			dialog.text = "嗝! 哎哟! 是的, 他们把他安置在工厂里, 一间看守的房子里。 ";
			link.l1 = "好的。 我去找他。 注意别喝过头了。 ";
			link.l1.go = "Himenes_84";
		break;
		
		case "Himenes_84":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10); /// 他走向出口, 设置正确的定位器
			IslaMona_ChurchSetHispanos();
		break;
		
		case "Himenes_85":
			dialog.text = "我游了个泳, 现在完全好了! 我们会生活和工作。 我会尽力让工厂尽可能长时间地运转。 嗯, 还有修理, 小规模建设。 也许甚至和我的妻子决定要孩子。 ";
			link.l1 = "为你们所有人高兴! 这是一次非常紧张。 代价高昂... 但精彩的冒险, 我很高兴我们成功了。 祝大家好运, 对我们中那些即将起航的人, 祝你们更多好运! ";
			link.l1.go = "Himenes_86";
		break;
		
		case "Himenes_86":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_Final", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// 士兵在海湾
		case "Capral":
			dialog.text = "站住! 下士" + GetFullName(npchar) + "。 你已进入战斗区域! 立即表明身份并说明你在这里的目的! ";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "下士, 退下! " +GetFullName(pchar)+ ", 法国海军船长。 我命令你护送我去见你们的高级军官。 执行命令! ";
				link.l1.go = "Capral_1";
			}
			else
			{
				link.l1 = "" +GetFullName(pchar)+ ",'"+ pchar.ship.name +"'号船长。 完全偶然来到这个岛 --可能进行维修和补充淡水供应。 ";
				link.l1.go = "Capral_3";
			}
		break;
		
		case "Capral_1":
			if(IsUniformEquip())
			{
				dialog.text = "是, 先生, 船长! 请跟我来。 我只是恳求你, 小心点! 这个岛到处都是强盗。 ";
				link.l1 = "";
			}
			else
			{
				dialog.text = "请原谅, 船长。 你没有穿制服, 所以我有义务检查你的军官专利。 ";
				link.l1 = "看。 满意了吗? 现在 --赶紧执行命令, 下士! ";
			}
			link.l1.go = "Capral_2";
		break;
		
		case "Capral_2":
			DialogExit();
			AddQuestRecord("IslaMona", "16");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 20.0);
		break;
		
		case "Capral_3":
			dialog.text = "你必须跟我来, 船长。 我们的高级军官会和你谈谈。 从现在起, 你的船被视为暂时被法国海军征用。 立即通知当前值班人员并跟我来。 ";
			link.l1 = "征用'查理王子'号? 我不这么认为! ";
			link.l1.go = "Capral_5";
			link.l2 = "看来我别无选择。 我会照你说的做。 ";
			link.l2.go = "Capral_4";
		break;
		
		case "Capral_4":
			DialogExit();
			AddQuestRecord("IslaMona", "18");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 5.0);
		break;
		
		case "Capral_5":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_DefKillCapral", 1.0);
		break;
		
		case "Capral_6":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "船长先生, 通往敌人营地的路在我们右边。 我会护送你。 ";
				link.l1 = "退下, 下士。 我宁愿一个人去。 ";
			}
			else
			{
				dialog.text = "船长, 通往敌人营地的路在我们右边。 你不会迷路的。 ";
				link.l1 = "谢谢你的关心。 ";
			}
			link.l1.go = "Capral_7";
		break;
		
		case "Capral_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			IslaMona_DefGotoMarch();
			pchar.quest.islamona_def_killslaves.win_condition.l1 = "location";
			pchar.quest.islamona_def_killslaves.win_condition.l1.location = "IslaMona_town";
			pchar.quest.islamona_def_killslaves.function = "IslaMona_DefKillSlaves";
		break;
		
		case "FraOfficer":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = ""+ GetFullName(pchar) + "船长! 感谢上帝! 请允许我介绍自己 --" + GetFullName(npchar) + "中尉。 您的忠实崇拜者! 我不知道您在这片贫瘠的土地上做什么, 但您来得正是时候! \n我必须说, 船长, 您在我们军官中非常受欢迎。 尽管许多人对您的...'特殊'服务风格感到恼火, 但每个人都同意, 您的专利使我们的舰队更强大。 我们目前处于完全僵局的境地, 因此像您这样的人的协助将是不可估量的! ";
				link.l1 = "我能做什么? 这里发生了什么? ";
				link.l1.go = "FraOfficer_1";
			}
			else
			{
				dialog.text = ""+ GetFullName(pchar) + "船长。 您的名字在舰队报告中被多次提及。 而且总是以非常可疑的方式。 然而, 现在您有机会中断这种不太光彩的趋势, 为祖国服务。 ";
				link.l1 = "我能做什么? 这里发生了什么? ";
				link.l1.go = "FraOfficer_8";
			}
		break;
		
		case "FraOfficer_1":
			dialog.text = "我们在'勇士'号上, 执行常规任务 --追捕特别大胆的西班牙袭击者。 事情很简单: 间谍提供区域和目标数据, 你从地平线下抓住它。 没有什么特别可说的, 结果非常糟糕: 西班牙人先发现了我们并发动了攻击, 尽管他们自己也在一艘护卫舰上。 如果我们有更强大的武器, 我们就不会和他们一起沉没... 但至少我们设法炸毁了他们的整个船体。 只有我的小队幸存下来。 然而, 卡斯蒂利亚人也有幸存者。 但不会太久, 哈哈! ";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "'勇士'号护卫舰? 肖克船长死了? ";
				link.l1.go = "FraOfficer_1_1";
			}
			else
			{
				link.l1 = "";
				link.l1.go = "FraOfficer_2";
			}
		break;
		
		case "FraOfficer_1_1":
			dialog.text = "我并不惊讶你会问起他, 船长。 我听说过你参与拦截'阿尔坎塔拉'号的事。 伟大的功绩, 即使在那时你就为你的专利奠定了基础! 肖克指挥官没有死, 恰恰相反! 他得到了晋升, 并应他的要求被派往地中海服役。 在我们现在的情况下, 我们只能羡慕他。 所以, 实际上, 关于我们的情况... ";
			link.l1 = "";
			link.l1.go = "FraOfficer_2";
		break;
		
		case "FraOfficer_2":
			dialog.text = "我们在岛上发现了一个定居点 --一个相当有人居住的强盗巢穴 --你听着 --海盗和西班牙人。 难以置信! 你知道, 通常这些混蛋只会互相砍杀和绞死, 但在这里 --看: 在群岛的中心, 他们像一家人一样一起工作, 开采海盗木材。 你见过他们为自己建造的码头吗? 这种人不会坐划艇来拜访。 我们的任务非常明确: 在你的帮助下, 我们占领定居点, 夺取海盗木材和囚犯, 你把所有人带到卡普斯特堡。 与此同时, 当局会自己解决... 当他们解决的时候, 我们会处理海盗木材, 并与我家乡中队的其他军官好好庆祝一番! ";
			link.l1 = "到目前为止, 是什么阻止了你自己占领定居点? ";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_3":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "可能强盗比我们多得多 --我们在岸边看到了帐篷。 此外, 除了帐篷, 他们还有墙。 大门。 大炮! ";
			else sTemp = "可能强盗不多, 否则他们早就把我们赶出去了, 但他们仍然有墙。 大门。 大炮和充足的时间! ";
			dialog.text = "什么阻止了我们? ! 我们只有十二名燧发枪兵和七名水手。 所有人都疲惫不堪。 我们只救了五支火枪, 每支最多只有一发子弹! " +sTemp+ "";
			link.l1 = "但你有计划吗? ";
			link.l1.go = "FraOfficer_4";
		break;
		
		case "FraOfficer_4":
			dialog.text = "听着, 我们没有浪费时间。 首先, 我们占领了这个工厂, 从而夺取了一些食物和水供应, 最重要的是 --一个满是海盗木材的仓库和十多名奴隶! 反正我们也无法看守奴隶, 所以我们立即在火枪的掩护下派他们去攻击他们的前主人, 进行战斗侦察。 这就是我们发现强盗有武器库存的方式。 ";
			link.l1 = "我的理解是否正确, 现在你想派我和我的人代替奴隶去处理这些武器? ";
			link.l1.go = "FraOfficer_5";
		break;
		
		case "FraOfficer_5":
			dialog.text = "不, 但你可以作为谈判代表去见强盗。 你的到来意味着他们的巢穴已经暴露, 现在国王的士兵有了一艘船和增援。 嗯, 当他们在考虑自己的处境时, 你要尽可能接近大炮, 在它下面扔一枚手榴弹, 在我们的人和你的人接近之前不要让自己被杀。 如果你不确定自己能处理, 可以派你的一个人代替你去。 ";
			link.l1 = "让我先不带炸弹去见他们, 提议他们投降。 我会四处看看, 了解他们的情绪和实力, 在他们心中播下怀疑的种子。 如果他们不投降, 那么我会再去, 但带着炸弹。 ";
			if (CheckCharacterItem(pchar, "patent_fra")) link.l1.go = "FraOfficer_6";
			else link.l1.go = "FraOfficer_6_1";
		break;
		
		case "FraOfficer_6":
			GiveItem2Character(pchar, "grenade");
			//Log_Info("你获得了手榴弹");
			PlaySound("interface\important_item.wav");
			dialog.text = "... 到那时, 他们已经习惯了你, 所以更容易进行破坏! 聪明! 嗯, 我没指望你会有别的做法, 船长。 准备好后就出发。 但还是拿着这个... 可能会有用。 ";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_6_1":
			dialog.text = "... 到那时, 他们已经习惯了你, 所以更容易进行破坏。 我们就这么办。 出发吧! ";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_7":
			DialogExit();
			AddQuestRecord("IslaMona", "19");
			chrDisableReloadToLocation = false;
			pchar.quest.islamona_def_goout.win_condition.l1 = "location";
			pchar.quest.islamona_def_goout.win_condition.l1.location = "IslaMona_Jungle_01";
			pchar.quest.islamona_def_goout.function = "IslaMona_DefCapralTalk";
		break;
		
		case "FraOfficer_8":
			dialog.text = "在这个地区与西班牙人进行了长时间的战斗。 双方船只都沉没了, 幸存者来到了这里。 大部分是法国人, 但也有一些敌人幸存下来。 你不需要知道更多, 抱歉, 船长。 秘密信息, 你明白。 ";
			link.l1 = "明白。 ";
			link.l1.go = "FraOfficer_9";
		break;
		
		case "FraOfficer_9":
			dialog.text = "我们在岛上发现了一个定居点 --一个相当有人居住的强盗巢穴 --你听着 --海盗和西班牙人。 难以置信! 你知道, 通常这些混蛋只会互相砍杀和绞死, 但在这里 --看: 在群岛的中心, 他们像一家人一样一起工作, 开采海盗木材。 你见过他们为自己建造的码头吗? 这种人不会坐划艇来拜访。 我们的任务非常明确: 在你的帮助下, 我们占领定居点, 夺取海盗木材和囚犯, 你把所有人带到卡普斯特堡。 与此同时, 当局会自己解决... 而在他们解决的时候, 我甚至可能准备给你机会为你的需求获取一些有价值的木材。 ";
			link.l1 = "到目前为止, 是什么阻止了你自己占领定居点? ";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_10":
			dialog.text = "你来了! 有什么消息吗? ";
			link.l1 = "这是荣誉卫队吗? ";
			link.l1.go = "FraOfficer_11";
		break;
		
		case "FraOfficer_11":
			dialog.text = "显然, 很快就会做出关于我们进一步行动的决定。 我不想在整个岛上寻找我的人来发布新命令。 ";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "出色的主动性! 你会收到命令的。 我已经进行了侦察: 敌人很弱, 大炮没有弹药。 我命令你立即攻击强盗巢穴, 中尉。 别再犹豫不决了。 只是舰队中的又一天。 执行! ";
				link.l1.go = "FraOfficer_12";
			}
			else
			{
				link.l1 = "在我看来, 你本可以在'奴隶'侦察后强行拿下他们。 他们的防御可笑, 只有几个认真的战士。 不必过度思考 --我们本可以坐在一堆铁材上喝战利品酒。 ";
				link.l1.go = "FraOfficer_14";
			}
		break;
		
		case "FraOfficer_12":
			dialog.text = "遵命, 船长! ";
			link.l1 = "... ";
			link.l1.go = "FraOfficer_13";
		break;
		
		case "FraOfficer_13":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -25);
			AddQuestRecord("IslaMona", "22");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_14":
			dialog.text = "这些是你的侦察结果吗? 我明白, 期望一个非军事人员做得太多可能很奇怪, 但我需要事实! 事实, 船长, 不是你的意见! ";
			link.l1 = "你冒犯我了, 中尉。 报告! ";
			link.l1.go = "FraOfficer_15";
		break;
		
		case "FraOfficer_15":
			dialog.text = "";
			link.l1 = "现在, 有一个你击沉的西班牙船只的幸存船长。 一位经验丰富的指挥官, 很快就会康复。 如果你拖延, 他会康复并按照军事科学手册组织防御, 然后我们就会有麻烦。 我们需要快点 --我重复, 他们很弱, 士气低落。 ";
			link.l1.go = "FraOfficer_15_1";
			link.l2 = "增援部队很快就会到来 --夺取海盗木材。 我不认为这是虚张声势: 你自己看到了码头和工厂仓库里一堆准备交付的货物。 我们需要快点 --我重复, 他们很弱, 士气低落。 如果你拖延, 你会等待海盗船的到来。 ";
			link.l2.go = "FraOfficer_15_2";
			link.l3 = "这个洞里将近一半的居民是妇女。 你一直在对抗的甚至不是民兵: 一直以来对抗你的战士不超过十几个。 他们很弱, 士气低落。 ";
			link.l3.go = "FraOfficer_15_3";
			link.l4 = "大炮没有弹药。 我这辈子见过足够多的枪, 能分辨出船员是否准备开火。 没有他们的大炮, 他们只不过是可怜的战士; 他们很弱, 士气低落。 ";
			link.l4.go = "FraOfficer_15_4";
			link.l5 = "想想战利品和荣耀吧, 中尉! 独自战胜西班牙袭击者, 占领强盗巢穴和独特的海盗木材来源 --所有这些都需要指挥你自己的船! 我重复, 他们很弱, 士气低落, 是时候粉碎他们了! ";
			link.l5.go = "FraOfficer_15_5";
		break;
		
		case "FraOfficer_15_1":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				notification("技能检查通过", SKILL_LEADERSHIP);
				dialog.text = "谢谢你, 船长。 这是有价值的信息, 你是对的, 这里没有必要拖延。 我的人都在这里, 我们强大。 训练有素。 准备就绪。 一切将在半小时内结束。 船长, 请准备好在你的船上接收人员。 囚犯和货物。 我们不会在这里久留。 ";
				link.l1 = "一切就绪, 中尉。 我们只等你了。 回头见! ";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("技能检查失败 (80)", SKILL_LEADERSHIP);
				dialog.text = "谢谢你, 船长。 这是有价值的信息。 在这种情况下, 前往码头并准备你的登船队。 我们将立即一起突袭强盗巢穴。 我和你最好的人将领导先锋队 --他们将是占领大门的人。 我们一起检查我们的部队后再讨论其余的。 不要让我和你的国家失望, " + GetFullName(pchar) + "。 ";
				link.l1 = "... 就这样吧。 回头见, 中尉。 ";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_2":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("声誉检查通过", "None");
				notification("技能检查通过", SKILL_LEADERSHIP);
				dialog.text = "谢谢你, 船长。 这是有价值的信息, 你是对的, 这里没有必要拖延。 我的人都在这里, 我们强大。 训练有素。 准备就绪。 一切将在半小时内结束。 船长, 请准备好在你的船上接收人员。 囚犯和货物。 我们不会在这里久留。 ";
				link.l1 = "一切就绪, 中尉。 我们只等你了。 回头见! ";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("声誉太低! (" + XI_ConvertString(GetReputationName(42)) + ")", "None");
				notification("技能检查失败 (60)", SKILL_LEADERSHIP);
				dialog.text = "谢谢你, 船长。 这是有价值的信息。 在这种情况下, 前往码头并准备你的登船队。 我们将立即一起突袭强盗巢穴。 我和你最好的人将领导先锋队 --他们将是占领大门的人。 我们一起检查我们的部队后再讨论其余的。 不要让我和你的国家失望, " + GetFullName(pchar) + "。 ";
				link.l1 = "... 就这样吧。 回头见, 中尉。 ";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 70 && sti(pchar.reputation.nobility) > 41)
			{
				notification("声誉检查通过", "None");
				notification("技能检查通过", SKILL_LEADERSHIP);
				dialog.text = "谢谢你, 船长。 这是有价值的信息, 你是对的, 这里没有必要拖延。 我的人都在这里, 我们强大。 训练有素。 准备就绪。 一切将在半小时内结束。 船长, 请准备好在你的船上接收人员。 囚犯和货物。 我们不会在这里久留。 ";
				link.l1 = "一切就绪, 中尉。 我们只等你了。 回头见! ";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("声誉太低! (" + XI_ConvertString(GetReputationName(42)) + ")", "None");
				notification("技能检查失败 (70)", SKILL_LEADERSHIP);
				dialog.text = "谢谢你, 船长。 这是有价值的信息。 在这种情况下, 前往码头并准备你的登船队。 我们将立即一起突袭强盗巢穴。 我和你最好的人将领导先锋队 --他们将是占领大门的人。 我们一起检查我们的部队后再讨论其余的。 不要让我和你的国家失望, " + GetFullName(pchar) + "。 ";
				link.l1 = "... 就这样吧。 回头见, 中尉。 ";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("声誉检查通过", "None");
				notification("技能检查通过", SKILL_LEADERSHIP);
				dialog.text = "谢谢你, 船长。 这是有价值的信息, 你是对的, 这里没有必要拖延。 我的人都在这里, 我们强大。 训练有素。 准备就绪。 一切将在半小时内结束。 船长, 请准备好在你的船上接收人员。 囚犯和货物。 我们不会在这里久留。 ";
				link.l1 = "一切就绪, 中尉。 我们只等你了。 回头见! ";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("声誉太低! (" + XI_ConvertString(GetReputationName(42)) + ")", "None");
				notification("技能检查失败 (60)", SKILL_LEADERSHIP);
				dialog.text = "谢谢你, 船长。 这是有价值的信息。 在这种情况下, 前往码头并准备你的登船队。 我们将立即一起突袭强盗巢穴。 我和你最好的人将领导先锋队 --他们将是占领大门的人。 我们一起检查我们的部队后再讨论其余的。 不要让我和你的国家失望, " + GetFullName(pchar) + "。 ";
				link.l1 = "... 就这样吧。 回头见, 中尉。 ";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_5":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 90)
			{
				notification("技能检查通过", SKILL_LEADERSHIP);
				dialog.text = "谢谢你, 船长。 这是有价值的信息, 你是对的, 这里没有必要拖延。 我的人都在这里, 我们强大。 训练有素。 准备就绪。 一切将在半小时内结束。 船长, 请准备好在你的船上接收人员。 囚犯和货物。 我们不会在这里久留。 ";
				link.l1 = "一切就绪, 中尉。 我们只等你了。 回头见! ";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("技能检查失败 (90)", SKILL_LEADERSHIP);
				dialog.text = "谢谢你, 船长。 这是有价值的信息。 在这种情况下, 前往码头并准备你的登船队。 我们将立即一起突袭强盗巢穴。 我和你最好的人将领导先锋队 --他们将是占领大门的人。 我们一起检查我们的部队后再讨论其余的。 不要让我和你的国家失望, " + GetFullName(pchar) + "。 ";
				link.l1 = "... 就这样吧。 回头见, 中尉。 ";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_16": // 法国人自己攻击
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			AddQuestRecord("IslaMona", "24");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_17": // 联合攻击
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -7);
			AddQuestRecord("IslaMona", "23");
			IslaMona_DefAttackCommon();
		break;
		
		case "FraOfficer_18":
			if (CheckCharacterItem(pchar, "patent_fra")) dialog.text = "而我, 白痴, 崇拜你! 啊-啊! 法国的骄傲, " +GetFullName(pchar)+ "船长!! 你不配拥有你的专利!!! ";
			else dialog.text = "" +GetFullName(pchar)+ ", 人渣, 叛徒, 该死的海盗! 我早该猜到这个可怜的巢穴是你肮脏的地盘! 法国既不忘记也不原谅像你这样的人! ";
			link.l1 = "";
			link.l1.go = "FraOfficer_19";
		break;
		
		case "FraOfficer_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_75";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FraOfficer_20":
			dialog.text = "你准备好了吗, 船长? 你的小队看起来很有价值! ";
			link.l1 = "谢谢你, 中尉。 我们开始吧? ";
			link.l1.go = "FraOfficer_21";
		break;
		
		case "FraOfficer_21":
			dialog.text = "是的, 我们立即出发! ";
			link.l1 = "... ";
			link.l1.go = "FraOfficer_22";
		break;
		
		case "FraOfficer_22":
			DialogExit();
			IslaMona_DefAttackCommonRun();
		break;
		
		// 被冒犯的海盗
		case "Pirate":
			dialog.text = "哈! " +GetFullName(pchar)+ "! 真是个会面。 嘿, 抓住他! 这个混蛋拥有这里的一切! 这是他的岛! ";
			link.l1 = "今天真是... ";
			link.l1.go = "Pirate_1";
		break;
		
		case "Pirate_1":
			DialogExit();
			IslaMona_DefCheckJungleFight();
		break;
		
		// 阿隆索
		case "Alonso":
			dialog.text = "船长, 有什么命令? 有信号要求待命并派出登船队。 ";
			link.l1 = "命令不变。 孩子们, 跟我来, 我们需要把不速之客从我们的家园清除出去。 战利品是我的, 所有的奖杯都是你们的! ";
			link.l1.go = "Alonso_1";
		break;
		
		case "Alonso_1":
			dialog.text = "万岁! ";
			link.l1 = "战斗! ";
			link.l1.go = "Alonso_2";
		break;
		
		case "Alonso_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_our_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common"))
			{
				pchar.quest.islamona_attack_common1.win_condition.l1 = "location";
				pchar.quest.islamona_attack_common1.win_condition.l1.location = "IslaMona_Jungle_01";
				pchar.quest.islamona_attack_common1.function = "IslaMona_DefAttackCommonPrepare";
			}
			else
			{
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
				pchar.quest.islamona_attack_force.win_condition.l1 = "location";
				pchar.quest.islamona_attack_force.win_condition.l1.location = "IslaMona_factoria";
				pchar.quest.islamona_attack_force.function = "IslaMona_DefAttackForce";
			}
		break;
		
	// 西班牙军官
		case "SpaOfficer":
			dialog.text = "您好, 先生。 您是这片土地的主人吗? 请允许我自我介绍, 弗朗西斯科.德.阿尔瓦大人, 前'海狗'号护卫舰船长。 ";
			link.l1 = "是的, 这是我的土地。 我是" +GetFullName(pchar)+ ",'" + pchar.ship.name + "'号船长。 大人? 我们这儿可从没接待过如此尊贵的客人。 ";
			link.l1.go = "SpaOfficer_1";
		break;
		
		case "SpaOfficer_1":
			dialog.text = "哦, " +GetFullName(pchar)+ "先生! 久仰大名。 您看, 最近您的名字频繁出现在贸易之家的报告里, 我甚至以为会接到对付您的命令。 ";
			link.l1 = "对付我? ";
			link.l1.go = "SpaOfficer_2";
		break;
		
		case "SpaOfficer_2":
			dialog.text = "我觉得没必要装了。 我的职责是在全球所有海域搜寻并消灭西班牙和菲利普国王的敌人。 ";
			link.l1 = "幸好这样的命令还没到。 您显然是位技艺精湛的海军军官。 ";
			link.l1.go = "SpaOfficer_3";
		break;
		
		case "SpaOfficer_3":
			dialog.text = "如今我成了这座海盗盘踞的小岛的半死囚犯, 同胞们四处逃亡, 这恰恰证明了您的结论, 哈哈! 任务极其危险, 但军令如山。 我们差点就成功了! 真为我的部下们惋惜 --我能叫出他们所有人的名字, 我们并肩作战多年。 但我的祖国必须牺牲更多儿女来维持帝国地位, 我们家族对此再清楚不过。 ";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "";
				link.l1.go = "SpaOfficer_4";
			}
			else
			{
				link.l1 = "先回到更紧迫的问题上吧。 大人, 我该怎么处置您? ";
				link.l1.go = "SpaOfficer_5";
			}
		break;
		
		case "SpaOfficer_4":
			dialog.text = "顺便说一句, 德.莫尔先生,'勇士'号 --那艘小船您很熟悉, 对吧? 您在贝洛港的大胆行动可不是秘密。 太冒险了, 甚至有些 suicidal。 您当时急需用钱, 对吗? 哈! ";
			link.l1 = "您对我了解不少, 大人。 但还是谈谈您的命运吧。 ";
			link.l1.go = "SpaOfficer_5";
		break;
		
		case "SpaOfficer_5":
			dialog.text = "这有什么好考虑的? 就像所有精彩故事一样, 您有三个选择: 杀了我, 把我留在这里, 或者放了我。 如果您放了我, 我以德.阿尔瓦家族的名义发誓, 绝不会向任何人透露这个地方以及您参与我这次不幸遭遇的事。 此外, 我会欠您一个人情, 在还清人情之前, 绝不会与您为敌。 ";
			link.l1 = "我不能冒这个险, 大人。 ";
			link.l1.go = "SpaOfficer_6";
			link.l2 = "您要在这儿待一段时间, 和您的同胞们一样平等地生活和工作。 ";
			link.l2.go = "SpaOfficer_7";
			link.l3 = "欢迎登上我的船, 大人。 时机成熟时我会在圣地亚哥灯塔让您下船。 希望您信守诺言。 ";
			link.l3.go = "SpaOfficer_8";
		break;
		
		case "SpaOfficer_6":
			dialog.text = "我理解, 先生。 无论如何, 我已经和部下们一起在那场战斗中'牺牲'了, 这是个不错的结局。 ";
			link.l1 = "";
			link.l1.go = "SpaOfficer_6_1";
		break;
		
		case "SpaOfficer_6_1":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_KillSpanish", 1.0);
		break;
		
		case "SpaOfficer_7":
			dialog.text = "我承认, 我不喜欢做事半途而废。 但当囚犯并不丢人, 所以我接受您赐予的生命, 会和这些善良且显然非常幸福的人们和平共处。 不过, 如果我离开这里, 就不再欠您任何东西。 ";
			link.l1 = "";
			link.l1.go = "SpaOfficer_7_1";
		break;
		
		case "SpaOfficer_7_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			AddQuestRecord("IslaMona", "27");
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_8":
			dialog.text = "我以我的名誉和德.阿尔瓦家族的名誉发誓! 船上见! ";
			link.l1 = "";
			link.l1.go = "SpaOfficer_8_1";
		break;
		
		case "SpaOfficer_8_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("IslaMona", "28");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			pchar.quest.islamona_final_mayak.win_condition.l1 = "location";
			pchar.quest.islamona_final_mayak.win_condition.l1.location = "Mayak9";
			pchar.quest.islamona_final_mayak.function = "IslaMona_FinalMayakSpanish";
			pchar.questTemp.IslaMona.Mayak = "true";
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_9":
			dialog.text = ""+ GetFullName(pchar) + "船长! 您救了我的命, 还把我送回故乡。 我知道冒这样的风险有多难 --换作是我绝不敢这么做。 我欠您一个人情, 先生。 我发誓绝不会向任何人透露那场不幸战斗的详情。 等您回到旧大陆, 一定要来找我, 马德里的家族庄园永远欢迎您。 现在, 请收下这个... ";
			link.l1 = "一张地图碎片? ";
			link.l1.go = "SpaOfficer_10";
		break;
		
		case "SpaOfficer_10":
			AddMapPart();
			dialog.text = "这是我身上唯一值钱的东西了。 相信您很快就能找到另一块碎片。 再见了! 祝你好运, 我的朋友。 ";
			link.l1 = "再见, 大人。 记住您的诺言, 也祝您好运! ";
			link.l1.go = "SpaOfficer_11";
		break;
		
		case "SpaOfficer_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.IslaMona.Mayak = "done";
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddQuestRecord("IslaMona", "29");
			CloseQuestHeader("IslaMona");
		break;
		
		// 伊斯莱莫纳岛居民对话
		// 男性居民
		case "island_man":
			dialog.text = LinkRandPhrase("您好! 最近如何, 船长? 我们这儿一切顺利。 ", "为集体劳动是最大的快乐! ", "船长, 您的小岛太棒了, 我们会为它的繁荣全力以赴。 ");
			link.l1 = LinkRandPhrase("听着真不错。 ", "很高兴一切顺利。 ", "很欣赏您的热情, 朋友。 ");
			link.l1.go = "island_man_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = RandPhraseSimple(RandPhraseSimple("请别介意, 先生, 但住在这里实在太艰难了。 ", "但总比坐在宗教法庭的牢房里强... "),
						                               RandPhraseSimple("感谢您救了我们, 船长。 ", "这些... 海盗是您的朋友吗? "));
						link.l1 = "... ";
						link.l1.go = "island_man_1";
					break;
					
					case 1:
						dialog.text = RandPhraseSimple(RandPhraseSimple("这儿还不错! 就是有点无聊。 ", "船长, 很高兴见到您。 有空来坐坐! "),
						                               RandPhraseSimple("有人在海滩上发现了头骨, 还在晨会上展示。 这儿总是这样吗? ", "告诉您个秘密, 希梅内斯先生显然很享受这里的新鲜空气和安全感。 "));
						link.l1 = "... ";
						link.l1.go = "island_man_1";
					break;
					
					case 2:
						dialog.text = RandPhraseSimple(RandPhraseSimple("这儿还不错! 就是有点无聊。 ", "船长, 很高兴见到您。 有空来坐坐! "),
						                               RandPhraseSimple("有人在海滩上发现了头骨, 还在晨会上展示。 这儿总是这样吗? ", "告诉您个秘密, 希梅内斯先生显然很享受这里的新鲜空气和安全感。 "));
						link.l1 = "... ";
						link.l1.go = "island_man_1";
					break;
					
					case 3:
						dialog.text = RandPhraseSimple(RandPhraseSimple("上帝保佑您, 船长! ", "我们每周在海滩和酒馆举办表演, 有空来看看。 "),
						                               RandPhraseSimple("您的水手们总是拿各种小玩意儿换新鲜食物, 感谢您鼓励他们这么做。 ", "真神奇, 这地方居然还没被发现, 希望能一直这样。 "));
						link.l1 = "... ";
						link.l1.go = "island_man_1";
					break;
				}
			}
		break;
		
		case "island_man_1":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
		break;
		
		case "island_man_2":
			dialog.text = "谢谢您, 先生。 多亏了您, 我们才见识了真正的新世界。 上帝保佑您! ";
			link.l1 = "";
			link.l1.go = "island_man_3";
			locCameraFromToPos(1.64, 1.58, -5.11, false, 2.66, 0.20, -5.74);
		break;
		
		case "island_man_3":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
			sld = characterFromId("Himenes_companion_12");
			sld.dialog.currentnode = "island_woman_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// 女性居民
		case "island_woman":
			dialog.text = LinkRandPhrase("安全与和平 --这就是我喜欢这里的原因! ", "简直是天堂! 嗯, 差不多... ", "经历了这么多苦难, 能在这里安家我们很开心。 ");
			link.l1 = LinkRandPhrase("为您和您的族群感到高兴。 ", "我也喜欢这个小岛。 ", "很高兴您感到满意。 ");
			link.l1.go = "island_woman_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = LinkRandPhrase("哦... 您好。 ", "先生, 那些... 带武器的粗野男人是谁? ", "感谢您救了我们, 船长。 ");
						link.l1 = "... ";
						link.l1.go = "island_woman_1";
					break;
					
					case 1:
						dialog.text = LinkRandPhrase("我们的男人干得很棒 --房子建得很好。 但我们也没闲着! ", "船长先生, 别担心: 我们小族群的女人不怕困难和暂时的不便。 ", "这儿的空气! 还有大海! 感觉离上帝更近了! ");
						link.l1 = "... ";
						link.l1.go = "island_woman_1";
					break;
					
					case 2:
						dialog.text = LinkRandPhrase("我们的男人干得很棒 --房子建得很好。 但我们也没闲着! ", "船长先生, 别担心: 我们小族群的女人不怕困难和暂时的不便。 ", "这儿的空气! 还有大海! 感觉离上帝更近了! ");
						link.l1 = "... ";
						link.l1.go = "island_woman_1";
					break;
					
					case 3:
						dialog.text = LinkRandPhrase("常回来看看, 船长先生。 见到您总是很高兴。 ", "罗德里加先生讲故事太精彩了, 能听他讲一整天。 ", "呵呵。 听说我们族群里有人快要添丁进口了。 即使在伊斯莱莫纳岛, 生活也在继续! ");
						link.l1 = "... ";
						link.l1.go = "island_woman_1";
					break;
				}
			}
		break;
		
		case "island_woman_1":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
		break;
		
		case "island_woman_2":
			dialog.text = "您... 非常感谢, 先生! 常来啊... ";
			link.l1 = "";
			link.l1.go = "island_woman_3";
			locCameraFromToPos(-1.86, 1.18, 4.51, true, -1.49, 0.20, 6.13);
		break;
		
		case "island_woman_3":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// 罗德里加的海盗
		case "fort_pirate":
			if(npchar.location == "islamona_factoria")
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("一切正常, 船长! ", "奴隶都在控制中, 别担心。 "),
						                                 RandPhraseSimple("您不必担心, 不会发生叛乱。 ", "感谢您的朗姆酒! 我们这就干活! "));
			}
			else
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("西班牙人? 真没想到您会这么做。 ", "现在我们得一路走到海滩才能安心睡觉! "),
						                                 RandPhraseSimple("您为什么要这么做 --嗯, 船长? ", "当时老大信任您 --果然没错。 我们会再次相信您。 "));
			}
			link.l1 = "... ";
			link.l1.go = "fort_pirate_1";
		break;
		
		case "fort_pirate_1":
			DialogExit();
			npchar.dialog.currentnode = "fort_pirate";
		break;
		
		// 酒馆顾客
		case "citizen_tavern":
			dialog.text = LinkRandPhrase("辛苦劳作后, 喝上一两杯不算罪过... ", "我快干完了, 这就回家; 妻子肯定在等我... ", "啊, 下班后在我们的酒馆放松真好! 我们都很感激您, 船长! ");
			link.l1 = LinkRandPhrase("喝得开心, 兄弟, 哈哈! ", "放松点, 伙计, 别喝过头, 不然老婆要骂了, 哈哈! ", "悠着点, 兄弟, 生活不只有工作! ");
			link.l1.go = "citizen_tavern_1";
		break;
		
		case "citizen_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "citizen_tavern";
		break;
		
		case "sailor_tavern":
			if (GetCharacterIndex("Mirabella") != -1) sTemp = "住在这儿的那个漂亮混血女人是谁? ";
				else sTemp = "船长, 您这地方真不错! ";
			dialog.text = RandPhraseSimple(RandPhraseSimple("船长, 您这地方真不错! ", "试想一下, 如果我们突然没了朗姆酒, 您肯定会再弄来, 对吧? "), RandPhraseSimple("我梦想这样的假期很久了。 不过要是有个妓院就好了... 只是随便想想, 船长。 ", sTemp));
			link.l1 = "... ";
			link.l1.go = "sailor_tavern_1";
		break;
		
		case "sailor_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_tavern";
		break;
		
		case "sailor_town":
			dialog.text = RandPhraseSimple(RandPhraseSimple("感谢您给的假期, 船长。 ", "您把这儿建设得真好 --船长, 您很擅长管理。 "), RandPhraseSimple("新鲜食物。 美酒。 脚下是坚实的土地。 这就是梦想。 ", "我想在这儿多待一段时间。 "));
			link.l1 = "... ";
			link.l1.go = "sailor_town_1";
		break;
		
		case "sailor_town_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_town";
		break;
		
		// 奴隶
		case "slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("太累了 --累得站都站不住。 ", "再也没力气这样活下去了! "), RandPhraseSimple("这工作对我来说太辛苦了。 ", "监工把我浑身都打遍了! "));				
			link.l1 = "";
			link.l1.go = "slave_1";
		break;
		
		case "slave_1":
			DialogExit();
			npchar.dialog.currentnode = "slave";
		break;
		
		// 房屋中的定居者
		case "HouseMan":
			dialog.text = LinkRandPhrase("有什么能为您效劳吗, 船长? ", "进来尝尝当地的肉菜饭吧。 看在上帝的份上, 别问是用什么做的! ", "欢迎, 船长。 您觉得这儿怎么样? ");
			link.l1 = "... ";
			link.l1.go = "HouseMan_1";
		break;
		
		case "HouseMan_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseMan";
		break;
		
		case "HouseWoman":
			dialog.text = LinkRandPhrase("先生, 欢迎! ", "您好, 船长。 要留下来吗? ", "您是来找我的吗? 请进, 别介意这儿乱, 先生。 ");
			link.l1 = "... ";
			link.l1.go = "HouseWoman_1";
		break;
		case "HouseWoman_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseWoman";
		break;
	}
}