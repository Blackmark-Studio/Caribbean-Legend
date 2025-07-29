void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "你想要什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;

		//--> 相遇
		case "DiegoDeLanda_Meeting":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "很悲伤的故事, 不是吗? ";
				link.l1 = "你是谁? ";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "问候你, 船长。 ";
				link.l1 = "等等! 我们以前见过! ";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "一。 二。 三。 ";
				link.l1 = "让我们停止这场表演。 你到底是谁? ";
				link.l1.go = "DiegoDeLanda_Meeting_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
			DelLandQuestMark(npchar);
		break;
		
		case "DiegoDeLanda_Meeting_2":
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				dialog.text = "你知道这个地窖有什么特别之处吗? 这里安息着两个血脉相连的灵魂。 德.阿拉米达父子。 一个死于罪人之手, 另一个... 嗯, 找到了通往主的道路。 ";
				link.l1 = "费尔南多先生的日记带我来这里。 ";
				link.l1.go = "DiegoDeLanda_SantaMisericordia_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				dialog.text = "你见过毕晓普夫人吗? 悲惨的命运, 不是吗? 但恐怕那是她应得的。 ";
				link.l1 = "你认识伊丽莎白? ";
				link.l1.go = "DiegoDeLanda_LadyBeth_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				dialog.text = "莫蒂默.格林。 ";
				link.l1 = "你当然认识他? ";
				link.l1.go = "DiegoDeLanda_Memento_2";
			}
		break;

		case "DiegoDeLanda_Meeting_Third_2":
			dialog.text = "\n再数三个。 数到六时你就会知道一切。 ";
			link.l1 = "如果现在不从你这里得到明确答案, 那么我... ";
			link.l1.go = "DiegoDeLanda_Meeting_Third_3";
		break;

		case "DiegoDeLanda_Meeting_Third_3":
			dialog.text = "\n你做得很好, 船长。 你应该知道我的名字。 我是迭戈.德.兰达。 ";
			link.l1 = "你真的是神父吗? ";
			link.l1.go = "DiegoDeLanda_Meeting_Third_4";
		break;

		case "DiegoDeLanda_Meeting_Third_4":
			dialog.text = "首先, 我是个艺术家。 但我们不要着急... ";
			link.l1 = "... ";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		//< —相遇
		
		//--> 神圣慈悲
		case "DiegoDeLanda_SantaMisericordia_2":
			dialog.text = "啊... 那本日记。 非凡的东西 —文字。 它就像... 黑暗中的一条路。 引领你到启示等待的地方。 费尔南多先生经常访问我们的教区。 尤其是在最后一年。 ";
			link.l1 = "你在当地教区服务? 你认识费尔南多先生? ";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_3";
		break;

		case "DiegoDeLanda_SantaMisericordia_3":
			dialog.text = "... ";
			link.l1 = "... ";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_4";
		break;

		case "DiegoDeLanda_SantaMisericordia_4":
			dialog.text = "我... 观察过他的道路。 还有你拿走的那本书。 你知道它的特别之处吗? ";
			link.l1 = "看起来很旧。 ";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_5";
		break;

		case "DiegoDeLanda_SantaMisericordia_5":
			dialog.text = "旧? 哦不。 它是... 受启迪的。 老德.阿拉米达先生的圣经。 里面的每一个字都像黑暗中的灯塔。 拿着它。 帮助你基督里的弟兄, 然后, 也许... 它会引领你找到更伟大的事物。 ";
			link.l1 = "... ";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		//< —神圣慈悲
		
		//--> 贝丝夫人
		case "DiegoDeLanda_LadyBeth_2":
			dialog.text = "哦, 是的。 可怜的女人。 她的丈夫…不是最善良的人。 据说他的种植园是巴巴多斯产量最高的。 也是最残酷的。 你知道每个月有多少奴隶死在那里吗? 最近, 他打死了一位来自英格兰的真正医生 —一个极具智慧和才华的人。 但相信我, 她的命运也好不到哪里去。 ";
			link.l1 = "你似乎消息很灵通。 ";
			link.l1.go = "DiegoDeLanda_LadyBeth_3";
		break;

		case "DiegoDeLanda_LadyBeth_3":
			dialog.text = "人们来找我忏悔, 船长。 我听到他们甚至害怕告诉亲人的事情。 他们的恐惧, 他们的罪孽…他们的痛苦。 ";
			link.l1 = "你不怕被迫害吗? 在英格兰土地上做天主教神父不容易。 ";
			link.l1.go = "DiegoDeLanda_LadyBeth_4";
		break;

		case "DiegoDeLanda_LadyBeth_4":
			dialog.text = "与你刚从那扇门后留下的东西相比, 我的恐惧算不了什么。 还有你从那个不幸女人那里拿走的小书…如果恐惧有形状, 那一定就是那样。 \n" +
		"日安, 船长。 ";
			link.l1 = "... ";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		//< —贝丝夫人
		
		//--> 纪念号
		case "DiegoDeLanda_Memento_2":
			dialog.text = "老虎, 老虎, 燃烧的光芒\n" +
			"在黑夜的森林中, \n" +
			"怎样不朽的手或眼\n" +
			"才能勾勒出你可怕的对称? \n" +
			"我当然认识他, 船长。 但你认识吗? ";
			link.l1 = "我从未见过命运更悲惨的人。 ";
			link.l1.go = "DiegoDeLanda_Memento_3";
		break;

		case "DiegoDeLanda_Memento_3":
			dialog.text = "你见过, 只是还没意识到。 \n" +
			"那你就不了解格林。 即使你手中握着他的头骨。 ";
			link.l1 = "什么? ! ";
			link.l1.go = "DiegoDeLanda_Memento_4";
		break;

		case "DiegoDeLanda_Memento_4":
			dialog.text = "那样对待死者可不是基督徒的方式。 拿着, 这是死后的小指南。 我给你的礼物。 \n" +
			"日安, 船长。 ";
			link.l1 = "... ";
			link.l1.go = "DiegoDeLanda_leaving";
			SetAlchemyRecipeKnown("blade_SP_3low");	// 卡特拉斯的配方
			SetAlchemyRecipeKnown("blade_SP_3");
		break;
		
		//< —纪念号
		
		//--> 告别
		case "DiegoDeLanda_Leaving":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving");
		break;
		
		case "DiegoDeLanda_Leaving_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "告诉我... 为什么? 那既危险又愚蠢。 是什么驱使你, 船长? 你的火焰是什么? ";
				link.l1 = "这不关你的事。 ";
				link.l1.go = "DiegoDeLanda_leaving_First_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "第二次。 ";
				link.l1 = "上次你说话像谜一样。 你会再这样吗? ";
				link.l1.go = "DiegoDeLanda_leaving_Second_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "... ";
				link.l1 = "等等, 德.兰达。 我不能就让你那样拿走东西离开。 ";
				link.l1.go = "DiegoDeLanda_Leaving_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
		break;
		
		case "DiegoDeLanda_Leaving_First_2": // 第一次告别
			dialog.text = "我不明白。 其他人 —是的。 但不是你。 还不是。 ";
			link.l1 = "其他人? ";
			link.l1.go = "DiegoDeLanda_Leaving_First_3";
		break;

		case "DiegoDeLanda_Leaving_First_3":
			dialog.text = "比如, 一个寻求正义。 另一个…痴迷于死亡的黑暗之水。 人们很容易在欲望中迷失自我。 你不觉得吗? ";
			link.l1 = "你是个奇怪的神父, 神父。 ";
			link.l1.go = "DiegoDeLanda_Leaving_First_4";
		break;

		case "DiegoDeLanda_Leaving_First_4":
			dialog.text = "... ";
			link.l1 = "我该走了。 ";
			link.l1.go = "DiegoDeLanda_Leaving_First_5";
		break;

		case "DiegoDeLanda_Leaving_First_5":
			dialog.text = "当然。 你的工作才刚刚开始, 船长。 ";
			link.l1 = "... ";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_leaving_Second_2": // 第二次告别
			dialog.text = "\n真正的谜题就站在我面前。 你已经收集了两件…遗物。 你喜欢收集这类东西? 你是收藏家吗? ";
			link.l1 = "你怎么知道? ";
			link.l1.go = "DiegoDeLanda_leaving_Second_3";
		break;

		case "DiegoDeLanda_leaving_Second_3":
			dialog.text = "一个战利品猎人? ";
			link.l1 = "我重复我的问题: 你怎么知道? ";
			link.l1.go = "DiegoDeLanda_leaving_Second_4";
		break;
		
		case "DiegoDeLanda_leaving_Second_4":
			dialog.text = "一个寻求刺激的人? ";
			link.l1 = "... ";
			link.l1.go = "DiegoDeLanda_leaving_Second_5";
		break;

		case "DiegoDeLanda_leaving_Second_5":
			dialog.text = "\n啊。 当然。 自然。 那么, 船长, 我不耽误你了。 ";
			link.l1 = "等等, 神父。 你还没回答我的问题。 ";
			link.l1.go = "DiegoDeLanda_leaving_Second_6";
		break;

		case "DiegoDeLanda_leaving_Second_6":
			dialog.text = "哦, 船长。 我不能。 有时答案比无知更伤人。 平安地去吧。 照顾好你的收藏品…战利品。 它们可能对前方的旅程有用。 ";
			link.l1 = "... ";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_Leaving_Third_2": // 第三次告别
			dialog.text = "来吧, 船长。 这对你来说不有趣吗? 你不觉得好玩吗? 你的战利品够多吗? \n" +
			"那就是你的火焰, 船长。 你好奇接下来会发生什么。 你喜欢漂亮的船和迷人的小饰品。 \n" +
			"你就是忍不住要把它们都收集起来。 \n" +
			"\n" +
			"你现在可以开枪打死我。 ";
			link.l1 = "什么? ! ";
			link.l1.go = "DiegoDeLanda_Leaving_Third_3";
		break;

		case "DiegoDeLanda_Leaving_Third_3":
			dialog.text = "去吧。 但那样你就不会知道一切, 也不会得到完整的战利品套装。 不过你反正会得到所有的船…\n" +
			"日安, 船长。 ";
			link.l1 = "(让他走)";
			link.l1.go = "DiegoDeLanda_Leaving_End";
			link.l2 = "(开枪打他)";
			link.l2.go = "DiegoDeLanda_Leaving_Shoot";
		break;
		
		case "DiegoDeLanda_Leaving_End":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_End");
		break;
		
		case "DiegoDeLanda_Leaving_Shoot":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_Shoot");
		break;
		
		
		//<-- 告别
	}
}