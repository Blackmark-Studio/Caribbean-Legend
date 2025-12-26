void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold, NextMonth;
	string attrL, sStr, Month;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "你找我有事吗? ";
			link.l1 = "没有, 什么都没有。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// диалоги в ПУ
		case "SharlieEpilog_Pikar_1":
			dialog.text = "哟, 这不是谁来了嘛!  "+GetTitle(NPChar,true)+" "+pchar.lastname+" 活生生地出现在这里! ";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				link.l1 = ""+npchar.name+"! 说真的, 真没想到还能见到你…… 老实说, 我都以为你早就死了! ";
				link.l1.go = "SharlieEpilog_Pikar_2";
			}
			else
			{
				link.l1 = "我简直不敢相信自己的眼睛…… 帅气? 可是…… 怎么可能? ";
				link.l1.go = "SharlieEpilog_PikarResurrected_1";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\LE\Rocur\Rocur_03.wav");
		break;
		
		case "SharlieEpilog_Pikar_2":
			if (IsStateTitle())
			  {
				dialog.text = "哈哈! 你真不该担心。你看, 我不是好好的吗。决定犒劳自己一艘漂亮又 “干净” 的船。 可你呢…… 说说看, 你怎么会变成这样啊, 我的朋友? ";
			  }
			  else 
			  {
				dialog.text = "哈哈! 你看, 根本不用担心嘛。\n如你所见, 我活得好好的。\n决定犒劳自己一艘“干净”的小船。\n那你呢…… 说说看, 是什么风把你吹到这儿来的, 朋友? ";
			  }
			link.l1 = "别在这里。咱们去酒馆吧——正事可以等一等。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_1":
			dialog.text = "嘘…… 别喊了。那个小白脸已经走了, 就像王子一样, 对吧? ";
			link.l1 = "但是我亲眼看见的…… ";
			link.l1.go = "SharlieEpilog_PikarResurrected_2";
		break;

		case "SharlieEpilog_PikarResurrected_2":
			dialog.text = "我是怎么被收拾掉的? 要真有那么简单就好了, 朋友。相信我。";
			link.l1 = "咱们去酒馆吧。你可以把一切都告诉我。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_Captain_1":
			dialog.text = "...";
			link.l1 = "所以, 你就是那艘平纳斯船‘’的新主人"+GetShipName("Ulysse")+"“? ”";
			link.l1.go = "SharlieEpilog_Captain_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\z_arest_02.wav");
		break;
		
		case "SharlieEpilog_Captain_2":
			dialog.text = "我。 "+GetFullName(npchar)+", 既然你这么好奇。你又是谁啊? ";
			link.l1 = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+", 而且我想从你这里买下这艘船。";
			link.l1.go = "SharlieEpilog_Captain_3";
		break;
		
		case "SharlieEpilog_Captain_3":
			dialog.text = "当然, 当然, 我听说过你。我还以为终于甩掉了所有想抢这艘船的人。恐怕我要让你失望了,  "+GetTitle(NPChar,true)+" - '"+GetShipName("Ulysse")+"“'现在归我了, 很快我就要开着她去波尔多。我可不是为了砸掉第一笔生意才做买卖的, 这可不吉利, 你知道吧。”";
			link.l1 = "波尔多, 你说的? 有意思…… 也许我有个赚钱的提议要给你。我们要不要边喝朗姆酒边聊聊? ";
			link.l1.go = "SharlieEpilog_Captain_4";
		break;
		
		case "SharlieEpilog_Captain_4":
			dialog.text = "拒绝朗姆酒或者好机会可不是我的风格。走吧。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		// диалоги в таверне
		case "SharlieEpilog_Pikar_5":
			if (IsStateTitle())
			  {
				dialog.text = "那么, 敬你,  "+GetTitle(npchar,false)+" "+pchar.lastname+"…… 我就知道你这种人不会一直给Tirax跑腿。可没想到你能混成这么大的角色…… 真是让我大吃一惊, 见鬼了。";
				link.l1 = "哈哈。你看看是谁在说话。怎么, 你决定当商人了? ";
			  }
			  else 
			  {
				dialog.text = "为我们的重逢干杯! 我就觉得咱们还会再见面的。";
				link.l1 = "哈哈。敬她! 所以, 你决定当商人了? ";
			  }
			
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;

		case "SharlieEpilog_Pikar_6":
			dialog.text = "嗯, 你总不能一辈子为了几枚达布隆把脑袋别在裤腰带上吧。打点好该打点的人, 堵住不该说话的嘴——就这样, 我不再是小偷或海盗, 而是个体面的商人了。";
			link.l1 = "哎呀, 这可真是出乎意料。现在我都不知道该怎么把原本要提给这位新晋双桅帆船船长的提议说出口了。"+GetShipName("Ulysse")+"'。";
			link.l1.go = "SharlieEpilog_Pikar_7";
		break;

		case "SharlieEpilog_Pikar_7":
			dialog.text = "哎呀, 别拐弯抹角了, 直接说吧。咱们认识这么久了。";
			link.l1 = "你知道吗…… 我是乘着你买下的那艘平克船来到加勒比的。听说它要被拍卖时, 我本来想去竞拍, 然后把它开回法国。";
			link.l1.go = "SharlieEpilog_Pikar_8";
		break;

		case "SharlieEpilog_Pikar_8":
			dialog.text = "哈哈哈哈哈! 等等…… 啊哈哈哈哈哈! ..";
			link.l1 = "所以, 有什么好笑的? ";
			link.l1.go = "SharlieEpilog_Pikar_9";
		break;

		case "SharlieEpilog_Pikar_9":
			dialog.text = "我刚拍下拍卖品, 这个花花公子就凑上来了——一个年轻、打扮得体的小子——开口就让我带他和他的行李去波尔多, 还愿意付一大笔钱。可不只是钱, 是一整袋该死的金币啊。\n";
			link.l1 = "是吗? 哈哈, 真有趣。那你怎么做的? 你答应了吗? ";
			link.l1.go = "SharlieEpilog_Pikar_10";
		break;

		case "SharlieEpilog_Pikar_10":
			dialog.text = ""+pchar.name+"嗯, 老子可不是傻子, 怎么会拒绝一大堆黄金, 就为了横渡大西洋这么点小事呢。好吧, 接下来几个月只能啃硬饼干、嚼咸肉了。可你知道吗, 我以前为了更少的东西都豁出过命。所以嘛, 当然要干了。";
			link.l1 = "那样的话, 我也可以给你同样的条件。带我去波尔多, 你也能拿到同样多的钱。";
			link.l1.go = "SharlieEpilog_Pikar_11";
		break;

		case "SharlieEpilog_Pikar_11":
			dialog.text = "你准备好当乘客了吗? 你知道规矩——一艘船上只能有一个船长。在我的船上, 那个人就是我。";
			link.l1 = "为什么不呢? 我可以喘口气, 想想人生。也许我真的该安定下来, 让那颗不安分的心平静下来。现在很难想象, 但或许这也有点道理。毕竟, 连你都决定远离战斗了。";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Pikar_12_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Pikar_12";
			}
		break;
		
		case "SharlieEpilog_Pikar_12_wife":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				dialog.text = "啊, 要是我也有你这么美的妻子, 也许我也会放弃大海, 在某个安静的地方安顿下来——盖个房子, 做点小酒生意。现在我也负担得起了——自从你把我从西班牙人手里救出来后, 我可是一点时间都没浪费。";
			}
			else
			{
				dialog.text = "唉, 要是我也有你这么漂亮的妻子, 也许我早就离开大海, 找个安静的地方安顿下来: 盖个房子, 做点葡萄酒生意。再加上那个种植园主遗孀的遗产, 你的生活绰绰有余了。";
			}
			link.l1 = "老婆! 该死,  "+npchar.name+", 我还没跟她谈过这件事。";
			link.l1.go = "SharlieEpilog_Pikar_13_wife";
		break;
		
		case "SharlieEpilog_Pikar_13_wife":
			dialog.text = "你有的是时间去办那些事。我得把我的破船好好整修一番。等你把自己的事都搞定了, 就赶紧滚过来。咱们在起航前好好庆祝一番。";
			link.l1 = "这才像话嘛! 别担心, 你很快就不用等了。";
			link.l1.go = "SharlieEpilog_Pikar_14_wife";
		break;
		
		case "SharlieEpilog_Pikar_14_wife":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_1");}
			else {AddQuestRecord("SharlieEpilog", "11_5");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_12":
			dialog.text = "唉, 要是我有个妻子, 也许我会离开大海, 找个安静的地方安顿下来——盖个房子, 卖点葡萄酒。\n不过现在…… 大海才是我的家。";
			link.l1 = "哈哈, 俺自家庄园的葡萄酒! 在波尔多, \n "+npchar.name+", 那些姑娘可真是养眼极了! 说不定你还能在那里找到个心上人——她们在情场可有一套。你想啊, 接下来的几个月, 我们能见到的也就是你那些水手的脸了。咱们起航前, 真的该在当地的妓院好好办一场宴会才对。\n";
			link.l1.go = "SharlieEpilog_Pikar_13";
		break;
		
		case "SharlieEpilog_Pikar_13":
			dialog.text = "你啊, 先生, 真知道怎么讨人欢心。等你把自己的事处理好了, 就赶紧滚回来。然后咱们一起去妓院——说到做到。";
			link.l1 = "那好吧, 我就不浪费时间了。我们赶紧开始吧! ";
			link.l1.go = "SharlieEpilog_Pikar_14";
		break;
		
		case "SharlieEpilog_Pikar_14":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_2");}
			else {AddQuestRecord("SharlieEpilog", "11_6");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_3":
			dialog.text = "为了自由! ";
			link.l1 = "也敬你, Jean! 敬你死而复生! 我到现在还不敢相信。怎么做到的? ";
			link.l1.go = "SharlieEpilog_PikarResurrected_4";
		break;

		case "SharlieEpilog_PikarResurrected_4":
			dialog.text = "他们把我从战场上拖了下来——几乎只剩一口气, 浑身上下全是血。把我扔进兵营, 任我像死尸一样等死。奴隶里有个挺机灵的小子——莫科。他救了我一命: 用我的衬衫撕成布条帮我包扎伤口, 还给我水喝。";
			link.l1 = "你是说西班牙人做了那些事之后还放你一条生路? ";
			link.l1.go = "SharlieEpilog_PikarResurrected_5";
		break;

		case "SharlieEpilog_PikarResurrected_5":
			dialog.text = "如你所见。不过他们可不是出于好心。他们想要报复——审讯、拷打。他们烧、打、割。还威胁要把我的眼睛烧瞎——全都是因为他们对我“深厚的感情”。但后来有人散布谣言, 说海盗们打算为我报仇, 刀子都已经磨好了。种植园主一听就开始紧张得直哆嗦。他没等我们的兄弟们上门, 就匆忙逃回了他在坎佩切的庄园。他把我、莫科和其他人都带走了, 这样就不会留下目击者。剩下的人被告知我已经死了——事情就这样结束了。";
			link.l1 = "然后呢? 你是怎么出来的? 你到底怎么会跑到这里来的? ";
			link.l1.go = "SharlieEpilog_PikarResurrected_6";
		break;

		case "SharlieEpilog_PikarResurrected_6":
			dialog.text = "运气啊, 朋友。瞎猫碰上死耗子一样的运气。\n他们把我送去了种植园——折磨还在继续。那混蛋决定要细细品味我受苦的每一秒, 可他自己却一天比一天虚弱…… 直到最后被热病夺了命。\n之后, 再也没人管我了。他们像赶牲口一样把我赶到田里, 逮着机会就用鞭子抽我。";
			link.l1 = "我还是不明白你是怎么从那里逃出来的? ";
			link.l1.go = "SharlieEpilog_PikarResurrected_7";
		break;

		case "SharlieEpilog_PikarResurrected_7":
			dialog.text = "听说过Christopher Myngs吗? ";
			link.l1 = "阿隆索提过一件事…… 劫掠坎佩切! 那次他们可真把西班牙人打惨了。原来是他们救了你? ";
			link.l1.go = "SharlieEpilog_PikarResurrected_8";
		break;

		case "SharlieEpilog_PikarResurrected_8":
			dialog.text = "不完全是。我们是自己逃出来的。就在守卫们和英国海盗打得不可开交的时候, Moko和我从兵营的屋顶找到了出路, 还发动了一场暴动。我们夺下了军械库, 还有那个死鬼种植园主老婆的金库。\n";
			link.l1 = "金库? ! 这还真是出乎意料呢。";
			link.l1.go = "SharlieEpilog_PikarResurrected_9";
		break;

		case "SharlieEpilog_PikarResurrected_9":
			dialog.text = "我们没多想就行动了——拿起武器和补给, 直接钻进了丛林。我们在灌木丛中艰难前行了两天, 直到偶然发现了坎佩奇印第安人的村庄。他们的萨满表面上顺从西班牙人, 其实根本不在乎。Moko很快就和他打成一片——我们用一半的武器库和承诺帮他们打未来的仗作为交换, 他们收留了我们。就这样, 我在那里住了一年半。";
			link.l1 = "让, 你已经不是从前的你了。从现在起, 你就是“幸运儿”。";
			link.l1.go = "SharlieEpilog_PikarResurrected_10";
		break;

		case "SharlieEpilog_PikarResurrected_10":
			dialog.text = "哈哈。我不介意。然后呢, 有个法国传教士被送到了我们的巴塔比尔。我们很快就明白了: 这是我们脱身、不戴镣铐的机会。我们贿赂了押送他的人——很快我们就驶向了托尔图加。\n接下来, 你大概也猜到了, 我决定不再和死神玩捉迷藏了。我放弃了老本行…… 运气不错, 还买下了一艘“"+GetShipName("Ulysse")+"'。\n"+"那你呢? 你怎么会变成现在这样? 我早就知道像你这么大胆的人, 绝不会一直当Tyraks的跑腿, 对吧? 可没想到你能混到这么大的人物…… 你总是能让我大吃一惊, 真是的。";
			link.l1 = "哈哈。你看看是谁在说话。怎么, 你决定当商人了? ";
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;
		
		case "SharlieEpilog_Captain_5":
			dialog.text = "“敬海上的人! ”";
			link.l1 = "“敬女神好运! ”";
			link.l1.go = "SharlieEpilog_Captain_6";
		break;

		case "SharlieEpilog_Captain_6":
			dialog.text = "好吧, 咱们开门见山。你想给我什么条件? ";
			link.l1 = "你要去波尔多…… 你看, 其实我也正要去那里。";
			link.l1.go = "SharlieEpilog_Captain_7";
		break;

		case "SharlieEpilog_Captain_7":
			dialog.text = "你想让我带你上船吗? 据我所知, 你应该有自己的船, 甚至可能有一整支舰队。可你却选择了搭别人的船。对吧? ";
			link.l1 = "没错。最近发生的事让我开始思考, 是不是该抛锚安定下来了…… 我觉得, 先在你的船上当个乘客, 或许能让我看看自己能不能适应新的生活节奏。\n";
			link.l1.go = "SharlieEpilog_Captain_8";
		break;

		case "SharlieEpilog_Captain_8":
			dialog.text = "嗯…… 所以, 你也厌倦了白白拿命冒险了? 我懂这种感觉。我自己嘛…… 算了, 不说了。船上有你的位置, 你的随从们也都能上。船票已经被某位年轻花花公子付过了——他还额外付了加速费, 所以我不会装任何货物。至于报酬嘛…… ";
			link.l1 = "别担心, 船长。我跟你的雇主一样大方, 也愿意付同样的价钱。";
			link.l1.go = "SharlieEpilog_Captain_9";
		break;

		case "SharlieEpilog_Captain_9":
			dialog.text = "太好了! 那我们算是说定了, 对吧? ";
			link.l1 = "成交! 这值得喝一杯! ";
			link.l1.go = "SharlieEpilog_Captain_10";
		break;

		case "SharlieEpilog_Captain_10":
			dialog.text = "嗯, 这朗姆酒真不错…… 我要两周时间把船修好, 还得把需要的东西都补齐。之后我们就能起航了。";
			link.l1 = "那我们就两周后在这里再见吧。\n那么, 下次见, 船长。";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Captain_11_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Captain_11";
			}
		break;
		
		case "SharlieEpilog_Captain_11_wife":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_3");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Captain_11":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_4");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "那么, 伙计, 你都搞定了吗? 咱们要不要让这群家伙见识一下什么叫真正的狂欢? ";
				link.l1 = "还没有,  "+npchar.name+", 我还有几件事要处理。";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "船长, 你准备好登船了吗? ";
				link.l1 = "唉, 我的朋友, 我还有些事情要处理。";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_Pikar_WaitInTavern";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				// только если знаком с Пикаром и поговорил с женой
				link.l2 = "嘿, 店主! 所有人都来喝一杯, 算我的! 别拿那些劣酒来——把你最好的酒拿出来! ";
				link.l2.go = "SharlieEpilog_Pikar_WaitInTavern_2";
			}
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern_2":
			dialog.text = "...";
			link.l1 = "为我们, 朋友。为咸咸的海风, 无尽的大海, 还有那永远在呼唤、永远无法触及的地平线…… ";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_FrameInSea":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_FrameInSea");
		break;
		
		case "SharlieEpilog_Mary_1":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", 亲爱的, 我想跟你谈谈我父亲的事。";
			link.l1.go = "SharlieEpilog_Mary_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_2":
			dialog.text = "发生什么事了, 亲爱的? 我希望他没事, 对吧? ";
			link.l1 = "嗯, 情况并没有人们希望的那么好。他可能时日无多了, 而且他非常忧虑, 担心在踏上最后旅途之前见不到我。";
			link.l1.go = "SharlieEpilog_Mary_3";
		break;

		case "SharlieEpilog_Mary_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "我知道, 亲爱的, 我知道…… 但这就是人生。我真希望你能见到他, 让他看看我有多出色的妻子, 给我们祝福。";
			link.l1.go = "SharlieEpilog_Mary_4";
		break;

		case "SharlieEpilog_Mary_4":
			dialog.text = "要是他不喜欢我怎么办, 对吧? 我又不是贵族出身…… ";
			link.l1 = "胡说,  "+npchar.name+", 你说他怎么可能不喜欢你呢? 你这么棒! 既然你能俘获我的心, 也一定能赢得他的心。";
			link.l1.go = "SharlieEpilog_Mary_5";
		break;

		case "SharlieEpilog_Mary_5":
			dialog.text = "你真的这么想吗, 亲爱的? 那我们就得尽快去找他了。";
			link.l1 = "这正是我打算做的事。我甚至已经给咱们找好了一艘船。两周后我们就启航。";
			link.l1.go = "SharlieEpilog_Mary_6";
		break;

		case "SharlieEpilog_Mary_6":
			dialog.text = "一艘船? 我们不是乘自己的船出海吗? ";
			link.l1 = "不, 亲爱的。我们要乘坐那艘小帆船‘"+GetShipName("Ulysse")+"'。我是乘这艘船来到加勒比海的——也要乘这艘船离开。";
			link.l1.go = "SharlieEpilog_Mary_7";
		break;

		case "SharlieEpilog_Mary_7":
			dialog.text = "你就不当船长了吗? ";
			link.l1 = "迟早我都得放弃这个角色。\n我希望这只是暂时的。\n不过, 提前感受一下未来会怎样, 也没什么坏处。";
			link.l1.go = "SharlieEpilog_Mary_8";
		break;

		case "SharlieEpilog_Mary_8":
			dialog.text = "那我们的军官们怎么办? 我们不可能把他们全都带走吧。再说, 我也怀疑他们会在这里等你。";
			link.l1 = "咳咳…… 嗯, 你说得对。我得和他们每个人谈谈, 很可能要永远告别了。虽然这并不容易——毕竟我们一起经历了那么多。";
			link.l1.go = "SharlieEpilog_Mary_9";
		break;
			
		case "SharlieEpilog_Mary_9":
			dialog.text = "也许我们应该在酒馆办个小小的告别派对吧? \n";
			link.l1 = "我也想过这个, 亲爱的。你知道吗…… 我觉得你说得对。其实这是个好主意。";
			link.l1.go = "exit";
			link.l2 = "我觉得这不是个好主意。\n我们还是别搞什么隆重的告别仪式了…… \n这样对大家可能都更好。\n也许我们只邀请最亲近的朋友就行了…… ";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		case "SharlieEpilog_Helena_1":
			dialog.text = "...";
			link.l1 = "亲爱的, 我想和你谈谈我父亲的事。";
			link.l1.go = "SharlieEpilog_Helena_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_2":
			dialog.text = "“当然, ” "+pchar.name+"…… 我希望他没事吧? ";
			link.l1 = "不完全是。他已经病了很长一段时间了, 我担心这场病很快就会夺走他的生命…… 父亲一直很坚强地承受着。唯一真正让他痛苦的, 是想到也许再也见不到我了。我想去看望他…… 还想把你介绍给他。希望能得到他对我们婚姻的祝福。";
			link.l1.go = "SharlieEpilog_Helena_3";
		break;

		case "SharlieEpilog_Helena_3":
			dialog.text = "我很乐意见见他, 亲爱的。我们什么时候启航? ";
			link.l1 = "两周后。不过还不止这些。我们不会乘自己的船航行。一艘轻舟会带我们回到旧大陆。 "+GetShipName("Ulysse")+"“——就是那个曾经把我带到这里的人。”";
			link.l1.go = "SharlieEpilog_Helena_4";
		break;

		case "SharlieEpilog_Helena_4":
			dialog.text = ""+pchar.name+", 不过长途航行前换船可是不吉利的。";
			link.l1 = "我们不会换船的, 亲爱的。我们只是乘客。";
			link.l1.go = "SharlieEpilog_Helena_5";
		break;

		case "SharlieEpilog_Helena_5":
			dialog.text = "但是…… 亲爱的, 我不明白…… ";
			link.l1 = "“只能这样了, ” "+npchar.name+"迟早我都得卸下船长的职位。\n我想提前知道, 到时候我会面对什么样的感受。";
			link.l1.go = "SharlieEpilog_Helena_6";
		break;

		case "SharlieEpilog_Helena_6":
			dialog.text = "如果这是你的决定…… 可是我们的军官怎么办? 我们不可能把他们全都带走。我也怀疑他们会愿意在这里等你。";
			link.l1 = "咳咳…… 嗯, 你说得对。我得和他们每个人谈谈, 很可能要永远告别了。虽然这并不容易——毕竟我们一起经历了那么多。";
			link.l1.go = "SharlieEpilog_Helena_7";
		break;
			
		case "SharlieEpilog_Helena_7":
			dialog.text = "要不要在酒馆办个小型的告别派对啊? ";
			link.l1 = "我也一直这么想, 亲爱的。你知道吗…… 我觉得我们就该这么做。真是个好主意。";
			link.l1.go = "exit";
			link.l2 = "我觉得这不是个好主意。\n还是别搞什么隆重的告别仪式了…… \n这样对大家可能都更好。\n也许我们只邀请最亲近的朋友就行了…… ";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		// Диалог с Алонсо в таверне Сен-Пьера
		case "SharlieEpilog_AlonsoInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				dialog.text = "船长…… 我已经和店主说好了——他准备了最好的酒。咱们什么时候开喝? ";
				link.l1 = "现在! 嘿, 店主! 所有人都来喝一杯, 我请客! ";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_1";
			}
			else
			{
				dialog.text = "船长, 你答应过要告诉我你是怎么发现“尤利西斯号”的。";
				link.l1 = "我记得, 我记得。嘿, 店主! 把最好的朗姆酒拿到这桌来。";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_3";
			}
			link.l2 = "“太早了, ” "+npchar.name+"…… 我还有紧急的事情要处理。";
			link.l2.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_AlonsoInTavern";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_1":
			dialog.text = "...";
			link.l1 = "那就这样吧, 朋友, 把其他人都叫来——让圣皮埃尔见识一下真正的海狗是怎么庆祝的! ";
			link.l1.go = "SharlieEpilog_AlonsoInTavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_AlonsoInTavern_2":
			dialog.text = "哈哈! 船长, 你不会信的——我已经把他们叫来了, 对吧? ";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_FrameInSea";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_3":
			dialog.text = "...";
			link.l1 = "为我们,  "+npchar.name+"“为幸运女神, 为鼓满我们风帆的海风! ”";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		// На пинасе Улисс
		case "SharlieEpilog_Alonso_1":
			dialog.text = "咱们可真是闹翻天了, 船长。哈哈。看来唯一让酒馆没被彻底毁掉的, 就是老板那点可怜的朗姆酒存货。";
			link.l1 = "“别提了, ” "+npchar.name+", 我才刚开始觉得好一点。";
			link.l1.go = "SharlieEpilog_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "SharlieEpilog_Alonso_2":
			dialog.text = "如您所愿, 先生 "+pchar.lastname+"哈哈。不过至少咱们是以皇家排场离开马提尼克的。他们肯定会在那里谈论你的离开很久很久。";
			link.l1 = "我觉得我们可能有点过分了, 把旅店老板塞进小艇, 送去勒弗朗索瓦再去拿酒。";
			link.l1.go = "SharlieEpilog_Alonso_2_1";
		break;
		
		case "SharlieEpilog_Alonso_2_1":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2)
				{
					dialog.text = "哈哈哈。别担心他。这几天他赚的金币够买下一座种植园了——说不定还能顺便弄个头衔呢。";
				}
			else
				{
					dialog.text = "哈哈哈。别担心他。这几天他赚了足够的钱, 买下一座种植园和一份头衔。只是可惜你从没和那些军官聊过天。我们会想念他们的。";
				}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;
		
		case "SharlieEpilog_Alonso_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
				{
					sld = CharacterFromID("Helena");
					locCameraFromToPos(-8.97, 6.39, -12.78, true, -8.54, 4.94, -13.90);
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
				{
					sld = CharacterFromID("Mary");
					locCameraFromToPos(-3.62, 4.03, 2.30, true, -4.98, 2.62, 3.26);
					// locCameraFromToPos(-4.13, 4.23, 2.55, true, -5.71, 2.54, 3.58);
				}
				dialog.text = "看起来,  "+sld.name+" 还在生你的气呢, 因为你半夜消失了大半。";
			}
			else
			{
				dialog.text = "至于那个商人…… 你那次可真是做得太过分了, 船长。";
			}
			link.l1 = "见鬼, 干嘛我和Jean非得去那家本地小店瞎逛啊…… ";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;
		
		case "SharlieEpilog_Alonso_4":
			dialog.text = "你怎么没被抓住啊? 那可真要笑死人了—— "+GetTitle(PChar,true)+" 偷几瓶葡萄酒时被抓住了。";
			link.l1 = "你觉得这很好笑,  "+npchar.name+", 而且我连一半都记不清了。上一次喝这么多还是…… 呃…… 其实从来没有过。";
			link.l1.go = "SharlieEpilog_Alonso_5";
			locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
		break;
		
		case "SharlieEpilog_Alonso_5":
			dialog.text = "那好吧, 祝咱们开个好头, 船长。哈哈, 我还挺喜欢刚才那一出呢。要是能再来一次我也愿意。对了, 你刚才说咱们什么时候回去来着? ";
			link.l1 = "去看看我们的行李, 好吗? 我们是不是全都带齐了? 我一会儿再下去——现在船舱里的空气对我可没什么好处。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_UlysseInSea_8");
		break;
		
		// диалог с Алонсо у горы золота
		case "SharlieEpilog_Alonso_11": // этап 1
			dialog.text = "...";
			link.l1 = "你看看…… 这船真是被打得够呛。";
			link.l1.go = "SharlieEpilog_Alonso_12";
			SharlieEpilog_GoldInTheDeck_1_1();
		break;
		
		case "SharlieEpilog_Alonso_12":
			dialog.text = "这里有一大堆金子啊, 船长! ";
			link.l1 = "我明白了,  "+npchar.name+"…… 我们得赶紧把这些东西都藏进箱子里, 趁船员们还没看见。他们可不需要这种诱惑。";
			link.l1.go = "SharlieEpilog_Alonso_13";
		break;
		
		case "SharlieEpilog_Alonso_13":
			dialog.text = "不, 我无法抗拒…… ";
			link.l1 = "什么? ";
			link.l1.go = "exit";
			locCameraFromToPos(-1.28, 7.70, -10.26, true, 0.74, 5.42, -9.49);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_2");
		break;
			
		case "SharlieEpilog_Alonso_21": // этап 2
			dialog.text = "...";
			link.l1 = "嘿, 你怎么了? ";
			link.l1.go = "SharlieEpilog_Alonso_22";
			// SharlieEpilog_GoldInTheDeck_6();
		break;
		
		case "SharlieEpilog_Alonso_22":
			dialog.text = "...";
			link.l1 = "快点, 起来。你挑了个好时候…… ";
			link.l1.go = "SharlieEpilog_Alonso_23";
		break;
		
		case "SharlieEpilog_Alonso_23":
			dialog.text = "加入我们吧, 船长。";
			link.l1 = "起来, 别闹了。";
			link.l1.go = "SharlieEpilog_Alonso_24";
		break;
		
		case "SharlieEpilog_Alonso_24":
			dialog.text = "放轻松。你只需要去感受就好了。";
			link.l1 = "好吧, 随你怎么说。现在, 让开。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_7");
		break;
		
		case "SharlieEpilog_Alonso_31": // этап 3
			dialog.text = "我一直梦想着做这件事…… ";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_32";
			SharlieEpilog_GoldInTheDeck_10();
		break;
		
		case "SharlieEpilog_Alonso_32":
			dialog.text = "很棒的感觉, 对吧, 船长? ";
			link.l1 = "哈哈哈。原本只是来加勒比海看看我亲爱的哥哥, 结果却变成这样。父亲肯定没想到会是这样的结局。哈哈! ";
			link.l1.go = "SharlieEpilog_Alonso_33";
		break;
		
		case "SharlieEpilog_Alonso_33":
			dialog.text = "Sir "+GetTitle(NPChar,false)+" "+pchar.lastname+"…… 哈哈! 你还记得你刚到群岛时是什么样子的吗? \n";
			link.l1 = "我当然记得。哈哈。真难以相信我曾经也是个像现在在甲板上趾高气扬的花花公子。该死的加勒比海上发生了太多事…… 阴谋、亡灵, 还有库库尔坎兄弟…… ";
			link.l1.go = "SharlieEpilog_Alonso_34";
		break;
		
		case "SharlieEpilog_Alonso_34":
			dialog.text = "你真是走了狗屎运, 船长。能赚这么一大笔钱, 还能活着讲出来…… 不是谁都有这本事的。";
			link.l1 = "行了行了, 别再磨蹭了。可别真让人发现我们啊。";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_11");
		break;
		
		// диалоги в катсцене с брашпилем
		case "SharlieEpilog_windlass_1":
			dialog.text = "...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "听着, 朋友, 我不喜欢这艘船上的锚机保险装置。它太不靠谱了, 谁都可能一不小心就把它碰掉。";
			}
			else
			{
				link.l1 = "听着, 船长, 我不喜欢这艘船上的锚机保险装置。它太不靠谱了, 谁都可能一不小心就把它碰掉。";
			}
			link.l1.go = "SharlieEpilog_windlass_2";
			locCameraFromToPos(-7.57, 9.68, -21.21, true, -9.79, 7.76, -20.01);
		break;
		
		case "SharlieEpilog_windlass_2":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "哎呀, 别这样,  "+pchar.name+", 在船上, 大家都知道…… ";
			}
			else
			{
				dialog.text = "哎呀, 船长。谁会想到呢…… ";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_windlass_3");
		break;
		
		case "SharlieEpilog_windlass_3": // диалог Пикара и дворянина
			dialog.text = "喂, 你这蠢货…… 你到底在胡闹什么? 没人教过你别把你那笨脚伸到不该去的地方吗? ";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_4";
			locCameraFromToPos(-10.28, 9.94, -22.90, true, -9.29, 7.86, -21.36);
			NPCsLookEachOther("SharlieEpilog_Pikar", "SharlieEpilog_Bernard_Clone");
			CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_Bernard_Clone"));
		break;
		
		case "SharlieEpilog_windlass_4":
			dialog.text = "...";
			link.l1 = "冷静点, 别太放肆! 我是贵族, 可不会容忍这种事…… ";
			link.l1.go = "SharlieEpilog_windlass_5";
		break;
		
		case "SharlieEpilog_windlass_5":
			dialog.text = "在我的船上, 你什么都不是。我的船员在这里的权利比你大得多。要么你闭嘴别碍事, 要么我亲自把你扔下海。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_6";
		break;
		
		case "SharlieEpilog_windlass_6": // диалог Пикара и Шарля
			dialog.text = "...";
			link.l1 = "哈哈哈。就像我刚刚从外面看到了自己一样。";
			link.l1.go = "SharlieEpilog_windlass_7";
			SharlieEpilog_windlass_9_1();
		break;
		
		case "SharlieEpilog_windlass_7":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "你在说什么? ";
				link.l1 = "“好吧, 没关系, ” "+npchar.name+"别对我们的乘客那么苛刻。他对这一切还很陌生呢。毕竟, 我们也不是一天就成了老海狼的, 对吧? ";
			}
			else
			{
				dialog.text = "你在说什么? ";
				link.l1 = "别在意,  "+npchar.name+"。还有, 别太苛刻地评判你的乘客。这一切对他来说都是新鲜事。毕竟, 我们当初也不是天生的海盗。";
			}
			link.l1.go = "SharlieEpilog_windlass_8";
		break;
		
		case "SharlieEpilog_windlass_8":
			dialog.text = "以他的本事, 他更可能被绞盘缠住, 也成不了什么水手。你想想看, 居然能想到这种事…… ";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "谁知道呢, 谁知道。我刚到群岛的时候, 还是和以前一样无忧无虑、好奇又自负的年轻人。";
			}
			else
			{
				link.l1 = "谁知道呢。我刚到群岛的时候, 也是个一样无忧无虑、好奇又自负的年轻人。";
			}
			link.l1.go = "SharlieEpilog_windlass_9";
		break;
		
		case "SharlieEpilog_windlass_9":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "对吧, 真是没法比啊。\n"+"等等\n"+"所以你在他身上看到了自己? 哈哈哈。那你就罩着他吧。我可不会替他当保姆。";
				link.l1 = "我会盯着他。至少等你把他活剥了再说。\n不过, 他得把锚的钱全都付清。";
			}
			else
			{
				dialog.text = "所以你在他身上看到了自己? 哈哈。那么, 船长, 他现在归你管了。我可不会替你照看他。";
				link.l1 = "我会盯着他。至少等你把他活剥了再说。\n不过锚的事——就让他自己好好付钱吧。";
			}
			link.l1.go = "SharlieEpilog_windlass_10";
		break;
		
		case "SharlieEpilog_windlass_10":
			dialog.text = "抛锚。等风。保持航向。";
			link.l1 = "...";
			link.l1.go = "exit";
			SharlieEpilog_windlass_10();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_1");
		break;
		
		// диалоги Старшего матроса и Алонсо		
		case "SharlieEpilog_AlonsoTrollingHighSailor_2": // Алонсо
			dialog.text = "";
			link.l1 = "起锚。扬帆。航向东北。";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_3";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_3": // Старший матрос
			dialog.text = "";
			link.l1 = "起锚! 降下前帆——让我们迎风起航。都动起来…… ";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_4";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_4": // Алонсо
			dialog.text = "";
			link.l1 = "你在干什么? ";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_5";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_5": // Старший матрос
			dialog.text = "";
			link.l1 = "你在干什么? ";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_6";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_6": // Алонсо
			dialog.text = "";
			link.l1 = "不, 你在干什么? ";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_7";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_7": // Старший матрос
			dialog.text = "";
			link.l1 = "唉…… 你在干什么? 老水手正在重复船长的命令。";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_8";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_8": // Алонсо
			dialog.text = "";
			link.l1 = "于是老水手就跟着他们重复一遍。";
			link.l1.go = "exit";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_2");
		break;
		
		// Шарль ругает Алонсо
		case "SharlieEpilog_AlonsoTrollingHighSailor_9":
			dialog.text = "...";
			link.l1 = "退下吧, Alonso。我们只是这里的乘客。你忘了吗? ";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_10";
			locCameraFromToPos(-8.00, 4.49, -1.91, true, -9.97, 2.64, -1.90);
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_10":
			dialog.text = "咳咳…… 抱歉, 船长。俺实在忍不住啊\n不过值了, 感觉就像回到了过去。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_5");
		break;
		
		// Диалог Шарля с Пикаром о всяком (можно попасть в Поместье де Монпе)
		case "SharlieEpilog_PikarOnUliss":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"…… 你找我有什么事? ";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A"))
				{
					link.l1 = "那么, 我的朋友, 你感觉怎么样? ";
					link.l1.go = "SharlieEpilog_PikarOnUliss_A_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_B"))
				{
					if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
					{
						link.l2 = "“承认吧, ” "+npchar.name+", 你当初决定脱离Tirax的时候, 就已经打算当商人了, 对吧? ";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
					else
					{
						link.l2 = "“承认吧, ” "+npchar.name+", 那时候你在种植园里就已经想着要当商人了? ";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_C"))
				{
					link.l3 = "我清楚地记得有个信使曾经想跟我说话。\n可我怎么都想不起来是关于什么的。你知道点什么吗? ";
					link.l3.go = "SharlieEpilog_PikarOnUliss_C_1";
				}
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_E"))
				{
					link.l1 = "船长, 你去过波尔多吗? ";
					link.l1.go = "SharlieEpilog_PikarOnUliss_E_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_F"))
				{
					link.l2 = "船长, 说实话, 我几乎不记得我们是怎么离开马提尼克的了。有人本来要给我送一些重要的信件, 但好像我一直没收到。有人跟你提过这事吗? ";
					link.l2.go = "SharlieEpilog_PikarOnUliss_F_1";
				}
			}
			link.l4 = "看来起了点微风。该扬帆出海了。 (出海) ";
			link.l4.go = "SharlieEpilog_PikarOnUliss_D_1";
			link.l5 = "还没有消息。我这就去。";
			link.l5.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_A_1":
			dialog.text = "哈哈…… 从没这么好过! 精力充沛, 身体倍儿棒。";
			link.l1 = "真的吗? 你看起来像是刚被鲨鱼咬过一样。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_A = true;
		break;

		case "SharlieEpilog_PikarOnUliss_A_2":
			dialog.text = "看你说的。你自己还不是一副被揍过的样子。";
			link.l1 = "我也是这么觉得。哈哈。该死, 我都记不清我们是怎么、什么时候起航的了。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_3";
		break;

		case "SharlieEpilog_PikarOnUliss_A_3":
			dialog.text = "啊, 那真是一场好宴会。就是花钱如流水, 贵得要命。我的那帮蠢货差点把青楼都烧了——我不得不掏了一袋金币来平息丑闻。现在那些白痴可欠我一辈子了。\n那么, 你觉得当乘客怎么样? 还没无聊到嚎叫吧? ";
			link.l1 = "我感觉自己的命运已经不再掌握在自己手里了。\n但与此同时, 我又感到一种奇怪的轻松。就好像我刚刚把一箱炮弹从肩上卸下来一样。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_4";
		break;

		case "SharlieEpilog_PikarOnUliss_A_4":
			dialog.text = "哈哈。那好吧, 要是哪天你觉得无聊了, 我随时欢迎你来当我的副官。";
			link.l1 = "你真是太慷慨了, 不过我还是得拒绝。整个加勒比海的朗姆酒都不够我们狂欢用的。";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_1":
			if (IsStateTitle()) 
			{
				dialog.text = "不完全是这样, 朋友。这个念头我偶尔会想起, 但从没太在意。后来我又听到一个传闻——Tyrax那帮忠心的狗腿子全都神秘消失了, 一个不剩——Cleaver、Baldy, 甚至连那条又老又臭的Leprechaun也没落下。\n等我听说你干下的那些大事时, 我终于觉得够了。你不能永远为了几枚金币拿命去拼。\n我现在有足够的金子, 再也不用在那些满脸粉的混蛋面前低声下气。但要彻底离开大海…… 我还没准备好。所以我换了个活法。";
			} 
			else 
			{
				dialog.text = "不完全是这样, 朋友。这个念头偶尔会在我脑海里闪过, 但我从没太在意。后来我听说了个传闻——Tyrax那帮忠心耿耿的狗全都神秘消失了, 一个不剩——Cleaver、Baldy, 甚至连那条又老又臭的Leprechaun也没落下。\n还有一次战斗里, 敌人的炮弹差点两次把我的脑袋炸飞, 那时候我终于觉得够了。你不能一辈子为了点钱把命搭上。\n我现在有足够的金币, 再也不用对那些戴假发的混蛋点头哈腰。但要我彻底离开大海…… 我还没做好准备。所以我决定试点新花样。";
			}
			link.l1 = "“Cleaver、光头、矮子…… 你知道他们都去哪儿了吗? ”";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_B = true;
		break;

		case "SharlieEpilog_PikarOnUliss_B_2":
			dialog.text = "不, 我不知道。说实话——那些混蛋最后去哪儿我一点都不关心。就算他们直接下地狱, 老子也无所谓。";
			link.l1 = "大致就是我把他们送去的地方。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_3";
		break;

		case "SharlieEpilog_PikarOnUliss_B_3":
			dialog.text = "原来是你把他们全船的人都干掉了? 哎呀, 我的天! Marcus还原谅你了? ";
			link.l1 = "他并不知道这件事。很可能, 他永远也不会知道。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_4";
		break;

		case "SharlieEpilog_PikarOnUliss_B_4":
			dialog.text = "所以, 见鬼, 我还真是及时离开他们了, 哈哈。你大概也不会放过我的脑袋吧\n不过有件事我一直想不明白——你到底图啥啊? ";
			link.l1 = "你说得对——这些混蛋为了区区一点金子都能互相掐死, 背叛或者杀掉任何人。我们被引诱进南大陆的某个地牢里, 被灌输了什么无尽财富的鬼话。这是个精心布置的陷阱, 那帮蠢货毫不犹豫就上钩了。他们不想平分战利品, 觉得没必要分赃——干脆把我干掉, 独吞所有东西。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_5";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_5":
			dialog.text = "结果他们根本没成功, 想都别想, 哈哈! 等等, 最开始是谁设的那个陷阱啊? \n";
			if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l1 = "有个佐罗, 是个西班牙的民间复仇者——为了卡塔赫纳寻仇。那场屠杀后, 幸存的人本该永远烂在地牢里——所有出口都被封死了。可那家伙没那么走运——我的军官把他耍了。";
			}
			else
			{
				link.l1 = "有个叫佐罗的家伙, 是西班牙的民间复仇者——为了卡塔赫纳寻仇。凡是从那场地狱般的大屠杀中活下来的人, 都注定要永远被关在地牢里——所有出口都被封死了。\n我侥幸逃了出来。但付出的代价极其惨重。";
			}
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_6";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_6":
			dialog.text = "至少你还活着出来了。还有, 我猜你也把那些差点用命换来的黄金都带出来了吧? ";
			link.l1 = "那里根本没有黄金。只是镀金的铅而已…… ";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_7";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_7":
			dialog.text = "...";
			link.l1 = "经历了这一切后, 我决定离开Tirax。你是第一个知道这件事的人。嗯, 除了我的军官们。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_8";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_8":
			dialog.text = "我不喜欢说“早就提醒过你”, 但是…… 我确实警告过你。";
			link.l1 = "我从来不擅长适可而止。\n所以你得多教教我。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_9";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_9":
			dialog.text = "你了解我的——要是有几杯好朗姆酒, 我连我的金子藏哪儿都会告诉你, 嘿嘿。";
			link.l1 = "哈哈哈, 别指望我会这么大方。你得靠你自己的补给了。";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_C_1":
			dialog.text = "没错。他试图递给你几封信——好像是某个Ben, 或者也许叫Benedict的人写的。但你当时直接回怼, 说你根本不认识什么Ben, 还威胁说要是他再搅和我们的乐趣, 就把他赶出酒馆。";
			link.l1 = "见鬼…… 看起来这些是贝努瓦修道院长的信。重要的信件。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_C = true;
		break;

		case "SharlieEpilog_PikarOnUliss_C_2":
			dialog.text = "那我拿走它们还真是做对了。嘿嘿。俺就有预感, 那小子找对人了。给你。";
			link.l1 = "你真的帮了我大忙,  "+npchar.name+", 谢谢你。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_3";
		break;

		case "SharlieEpilog_PikarOnUliss_C_3":
			dialog.text = "一句“谢谢”可不够啊, 朋友。你欠我一杯酒——还不是随便什么酒, 得是波尔多最好的那种。";
			link.l1 = "你会喝到酒的, 乞丐。我们的朗姆酒也许比不上加勒比的, 但葡萄酒嘛…… 那可是真正你从未尝过的好东西。";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_E_1":
			dialog.text = "从来没必要…… ";
			link.l1 = "我真羡慕你。真希望我也能第一次再见到波尔多。你大概更喜欢朗姆酒, 不过我还是建议你去市政厅附近的葡萄酒集市看看。加勒比的行家们愿意为我们的克莱雷红酒花大价钱。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_E = true;
		break;

		case "SharlieEpilog_PikarOnUliss_E_2":
			dialog.text = "谢谢你的建议。我可以问你一件事吗? ";
			link.l1 = "当然。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_3";
		break;

		case "SharlieEpilog_PikarOnUliss_E_3":
			dialog.text = "这么多年一直当船长, 现在变成乘客是什么感觉? 你习惯你的新身份了吗? ";
			link.l1 = "嗯…… 我总觉得自己的命运已经不再掌握在自己手里了。\n但与此同时, 我又感到一种奇怪的轻松。\n就好像刚把一箱炮弹从肩上卸下来一样。\n我想现在下结论还为时过早。";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_4";
		break;

		case "SharlieEpilog_PikarOnUliss_E_4":
			dialog.text = "碰上这该死的无风带, 你可有的是时间了。";
			link.l1 = "有好伙伴作伴, 即使风平浪静的大海也不会觉得无聊。得承认, 船长, 我很幸运能有这样的同伴。";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_F_1":
			dialog.text = "是的, 确实有个信使来过。是某个修道院院长派来的。我总是忘了把这些信交给你。来, 拿去吧。";
			link.l1 = "太棒了。你真的帮了我大忙, 船长。谢谢你。";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_F = true;
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A")){dialog.text = "你说得对。";}
			else {dialog.text = "你说得对。";}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_D_2";
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_2":
			dialog.text = "右舷来风! 所有帆都给我扬起来, 从前帆到后桅帆! 全速前进! \n";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InEstateDeMonpe";
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(CharacterFromID("SharlieEpilog_Pikar"), "quest", "quest10");
		break;
		
		case "SharlieEpilog_InEstateDeMonpe":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe");
		break;
		
		//Матрос 1 на верхней палубе
		case "SharlieEpilog_Sailor_1":
			dialog.text = "好刀,  "+GetTitle(NPChar,true)+"。可以让我看看吗? ";
			link.l1 = "也许下次吧。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_1";
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer05.wav");
		break;
		
		//Матрос 2 на верхней палубе
		case "SharlieEpilog_Sailor_2":
			dialog.text = "那些沙漏什么时候才会响啊? 老子都快咬断自己舌头了。";
			link.l1 = "耐心点, 水手。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-07.wav");
		break;
		
		//Матрос 3 на орудийной палубе
		case "SharlieEpilog_Sailor_3":
			dialog.text = "你看到那只老鼠跑过去了吗? 我发誓, 我这辈子从没见过那么大的老鼠! ";
			link.l1 = "“嗯…… ”";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_3";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-04.wav");
		break;
		
		//Матрос 4 на орудийной палубе
		case "SharlieEpilog_Sailor_4":
			dialog.text = "我现在该怎么办, 先生? 我喝得烂醉如泥, 连怎么上了这艘船都不记得了。\n我根本不是水手…… 而且我家里还有老婆和两个孩子。";
			link.l1 = "早知道就该少喝点。现在晚了——你得去当水手了。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_4";
			PlaySound("Voice\" + LanguageGetLanguage() + "\Ransack_2.wav");
		break;
		
		//Старший матрос
		case "SharlieEpilog_HighSailor_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"。能有您登上我们的船, 是我们的荣幸。";
			link.l1 = "您真是太有礼貌了, 先生老水手。礼貌可不是老海狗们最常见的品质。\n不过咱们别让船员们尴尬——毕竟这里不是陛下的宫廷。\n直接叫我船长就行。";
			link.l1.go = "SharlieEpilog_HighSailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;

		case "SharlieEpilog_HighSailor_2":
			dialog.text = "嗯, 其实我当水手的时间不长。以前我是Levasseur先生的书记。可他被…… 咳, 被清除了之后, 新总督上任了。很快, 某些圈子里就传开了, 说René de Boisdufle de Lestre先生是个大坏蛋。那时候我才明白: 我再也找不到正经工作了。人们会以为我什么都知道——只是装作不说而已。";
			link.l1 = "“难道不是这样吗? ”";
			link.l1.go = "SharlieEpilog_HighSailor_3";
		break;

		case "SharlieEpilog_HighSailor_3":
			dialog.text = "当然没有。我从来没有插手别人事情的习惯。再说了, 勒瓦瑟对好奇心可从不手软。";
			link.l1 = "这个我完全信得过。";
			link.l1.go = "SharlieEpilog_HighSailor_4";
		break;

		case "SharlieEpilog_HighSailor_4":
			dialog.text = "所以, 在你把他解决掉之后, 我就登上了我能找到的第一艘海盗船当水手。\n说来也奇怪, 我很快就适应了, 还变得不一样了。\n甚至连最狠的亡命之徒都开始尊重我。\n但他们干的那些事…… 真的不适合我。\n所以我才会来到这里。";
			link.l1 = "所以, 你早就知道我参与了Levasseur的命运? ";
			link.l1.go = "SharlieEpilog_HighSailor_5";
		break;

		case "SharlieEpilog_HighSailor_5":
			dialog.text = "当然了, 船长。我也很高兴你让那个怪物从世上消失了。与此同时, 你把我从那间闷得要命的小屋里带了出来。让我用全新的眼光看待自己的人生。";
			link.l1 = "这个世界真是小得惊人啊…… ";
			link.l1.go = "SharlieEpilog_HighSailor_6";
		break;

		case "SharlieEpilog_HighSailor_6":
			dialog.text = "听起来或许矛盾, 但这个世界既辽阔又渺小。";
			link.l1 = "有趣。我从来没认真想过这个问题。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
		break;
		
		case "SharlieEpilog_HighSailor_7":
			dialog.text = "Captain "+pchar.lastname+"…… 今晚不是很美好吗? ";
			link.l1 = "也许吧。要是能来一阵温和的西北风就更好了。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;
		
		//Диалог с боцманом Моко
		case "SharlieEpilog_Moko_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Captain "+pchar.lastname+"...";
				link.l1 = "其实…… 算了。我记得你! 你叫Moko。那次一口气喝光一整桶朗姆酒的人, 不就是你吗? ";
				link.l1.go = "SharlieEpilog_Moko_2";
			}
			else
			{
				dialog.text = "你想要什么…… 先生? ";
				link.l1 = "像你这么高大的人可不常见。你叫什么名字? ";
				link.l1.go = "SharlieEpilog_Moko_4";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Kapitani Korabley-07.wav");
		break;

		case "SharlieEpilog_Moko_2":
			dialog.text = "我…… 然后我直到两天后才醒过来。";
			link.l1 = "换做别人, 撑不过几个小时。你要是打架也像喝酒那么厉害——Jean能有你当大副, 真是走了狗屎运。";
			link.l1.go = "SharlieEpilog_Moko_3";
		break;

		case "SharlieEpilog_Moko_3":
			dialog.text = "就像我遇到了我的船长那么幸运。多亏了他, 我才找回了自由。也多亏了你。要不是你帮了让, 我现在还在种植园里受苦呢。\n";
			link.l1 = "这真是一场大冒险。幸好结局比我预想的要好得多。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_4":
			dialog.text = ""+npchar.name+"。我是这艘船的大副。";
			link.l1 = "哈哈, 我倒想看看谁敢惹你。你跟着船长干了多久了? ";
			link.l1.go = "SharlieEpilog_Moko_5";
		break;

		case "SharlieEpilog_Moko_5":
			dialog.text = "几年了。我欠他很多。如果不是他, 我早就烂在…… ";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Moko_6";
		break;

		case "SharlieEpilog_Moko_6":
			dialog.text = "...";
			link.l1 = "你是说在种植园里? ";
			link.l1.go = "SharlieEpilog_Moko_7";
		break;

		case "SharlieEpilog_Moko_7":
			dialog.text = "...";
			link.l1 = "快点,  "+npchar.name+", 当然, 你不用跟我说什么, 不过你要是还没发现的话, 我可不是那些戴假发的花花公子。船长把你救出来了吗? ";
			link.l1.go = "SharlieEpilog_Moko_8";
		break;

		case "SharlieEpilog_Moko_8":
			dialog.text = "我们是一起逃出来的。\n从马拉开波的种植园。\n要不是让, 我们根本逃不出来。\n从那以后, 我就一直在他的船上。\n一开始是水手, 现在——我是大副。";
			link.l1 = "船长竟然当过奴隶? 真没看出来啊。其实我自己也有点不可告人的秘密呢。你能从西班牙人的魔爪下逃出来, 真让人高兴,  "+npchar.name+"“。那么, 当水手是什么感觉? ”";
			link.l1.go = "SharlieEpilog_Moko_9";
		break;

		case "SharlieEpilog_Moko_9":
			dialog.text = "感觉以前从未真正活过。现在, 大海才是我的家。";
			link.l1 = "在这里, 我最能理解你, 朋友。没有人比我更懂你。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_repeat":
			dialog.text = "Captain "+pchar.lastname+"…… 我能帮你什么忙? ";
			link.l1 = "“谢谢你, ” "+npchar.name+", 现在我什么都不需要。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		//Диалог с дворянином Бернардом
		case "SharlieEpilog_Bernard_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"! 能在这艘船上看到至少一张明事理的脸, 我真是太高兴了。这些…… 水手…… 简直就是野人。";
			link.l1 = "要是我啊, 我可不会在别人的船上这么说话。\n我不知道你怎么跑到加勒比来的, 不过这里的规矩可不一样, 你懂吧。\n你最好还是给船员们点面子。";
			link.l1.go = "SharlieEpilog_Bernard_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;

		case "SharlieEpilog_Bernard_2":
			dialog.text = "尊重? 尊重他们? 他们就是野蛮人! 我是贵族,  "+GetTitle(NPChar,true)+", 我习惯了有条理, 习惯了被人伺候, 习惯了…… 文明! 谁敢惹我试试——我父亲一定会…… ";
			link.l1 = "你父亲会听说你在路上死于热病。他也很难证明不是这样。";
			link.l1.go = "SharlieEpilog_Bernard_3";
		break;

		case "SharlieEpilog_Bernard_3":
			dialog.text = "该死的Fox上校! 全都是他的错! 为了他女儿, 我横跨大洋, 放弃了舒适的生活, 忍受那些异样的眼光, 那可怕的食物, 还有这…… 没完没了的颠簸! 现在我还得在别人的船上航行! \n";
			link.l1 = "福克斯上校…… ";
			link.l1.go = "SharlieEpilog_Bernard_4";
		break;

		case "SharlieEpilog_Bernard_4":
			dialog.text = "你认识他吗,  "+GetTitle(NPChar,true)+"?";
			link.l1 = "咳咳…… 我听说过他。";
			link.l1.go = "SharlieEpilog_Bernard_5";
		break;

		case "SharlieEpilog_Bernard_5":
			dialog.text = "那你也没错过什么。那个人就是盲目军人固执和偏见的化身。";
			link.l1 = "他是个士兵…… ";
			link.l1.go = "SharlieEpilog_Bernard_6";
		break;

		case "SharlieEpilog_Bernard_6":
			dialog.text = "没错! 这就说明了一切。我去找他, 希望见见他女儿, 你知道他怎么做的吗? 你知道吗? 他直接把我赶了出去! 一句话都没说! ";
			link.l1 = "但是你没有退缩, 对吧? ";
			link.l1.go = "SharlieEpilog_Bernard_7";
		break;

		case "SharlieEpilog_Bernard_7":
			dialog.text = "当然啦! 我为了见他, 整整折腾了一周! 我都低声下气了! 甚至…… 还试过贿赂守卫! 最后, 我还是没请帖偷偷混了进去。我只是想聊聊而已! ";
			link.l1 = "我觉得他对此并不太高兴。";
			link.l1.go = "SharlieEpilog_Bernard_8";
		break;

		case "SharlieEpilog_Bernard_8":
			dialog.text = "见到我很开心吧? 哎呀, 他可真是大发雷霆! 我被赶了出来, 不准靠近宅邸, 父亲的船也被没收了, 后来甚至还下令所有英国船长都不许让我上船! 我只好去马提尼克找法国船…… 简直是一场噩梦。";
			link.l1 = "看起来你真的把他惹怒了。";
			link.l1.go = "SharlieEpilog_Bernard_9";
		break;

		case "SharlieEpilog_Bernard_9":
			dialog.text = "他一直都和我作对。他最爱说的一句话就是: “军官的女儿就是军官的妻子。”你,  "+GetTitle(NPChar,true)+", 他觉得这是一个更合适得多的婚配。";
			link.l1 = "也许这一次, 他还有其他原因…… ";
			link.l1.go = "SharlieEpilog_Bernard_10";
		break;

		case "SharlieEpilog_Bernard_10":
			dialog.text = "...";
			link.l1 = "所以, 你是来见你的心上人的。";
			link.l1.go = "SharlieEpilog_Bernard_11";
		break;

		case "SharlieEpilog_Bernard_11":
			dialog.text = "是的。自从她离开欧洲后, 我一封她的信都没收到。\n我敢肯定是她父亲在拦截信件。她不可能忘了我! \n当然, 她对我一直很矜持…… 甚至有些冷淡…… \n但我无法相信她会把我从她的生活中抹去。";
			link.l1 = "请节哀, 先生。心灵的伤口比肉体的要愈合得慢得多。\n不过等等…… 你, 作为一个英国人, 为什么要前往波尔多? ";
			link.l1.go = "SharlieEpilog_Bernard_12";
		break;

		case "SharlieEpilog_Bernard_12":
			dialog.text = "我可不打算灰溜溜地回家。等风头过去, 我得先去波尔多投奔我叔叔。\n不过, 他的庄园比我们家宽敞得多, 也更气派。还有, 他的仆人训练得也比我们家的好多了。";
			link.l1 = "嗯, 我想这也不算最糟的结果。说不定你还能再找一个情人呢。波尔多满是年轻美人, 相信我。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
		break;
		
		case "SharlieEpilog_Bernard_repeat":
			dialog.text = "“我们到底什么时候才能到啊, ” "+GetTitle(NPChar,true)+"? 被这些…… 先生们包围着, 真是让我难以忍受。我现在必须立刻去洗个澡。";
			link.l1 = "恐怕接下来的两个月, 你只能在梦里想她了。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;
		
		//Диалог с Книппелем на корабле Улисс
		case "SharlieEpilog_Knippel_1":
			dialog.text = "该死的无风带, 真希望链弹把它轰了。";
			link.l1 = "别抱怨,  "+npchar.name+", 迟早风会起来的。";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "那在那之前我该干什么, 先生? 连火炮都不能检查…… 毕竟这不是咱们自己的船。";
			link.l1 = "试着放松一下。你不用一直忙个不停。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		case "SharlieEpilog_Knippel_repeat":
			dialog.text = "该死的无风…… ";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		//Диалог с Лонгвэем на корабле Улисс
		case "SharlieEpilog_Longway_1":
			dialog.text = "不错的船, 船长。你也这么觉得吧? ";
			link.l1 = "比美凤还要好吗? ";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = "For "+npchar.name+" 没有哪艘船能比美凤号更好。这艘船再也不会像以前那样迎风疾行了。";
			link.l1 = "“冷静点, ” "+npchar.name+", 我只是开玩笑啦。美凤当然是独一无二的。不过尤利西斯号也是艘好船, 对吧? 很结实。";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = ""+npchar.name+" 掌舵。感受船只随你的操控而回应…… ";
			link.l1 = "唉, 朋友, 这艘船是别人的。你还是去找那边那个大个子陪你练练吧。对你们俩都有好处。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		case "SharlieEpilog_Longway_repeat":
			dialog.text = "如果顺风的话, 我们能跑多快? ";
			link.l1 = "我也说不准,  "+npchar.name+"。最好去问他们的领航员。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		//Диалог с Тонзагом на корабле Улисс
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "你看到他们这里的那个巨人水手长了吗? 听说他一只手就能捏碎椰子。";
			link.l1 = "哈哈。看来你有点怕他, 对吧? ";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "那有什么关系? 大小又不是全部。我以前可对付过更大的呢。";
			link.l1 = "那你要不要跟他打一架? 单挑——光明正大地来一场。";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "“唉…… ”";
			link.l1 = "你脸色有点发白啊。哈哈。行吧, 不行就不行。咱们还是别折腾你这不算年轻的骨头了。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		case "SharlieEpilog_Tonzag_repeat":
			dialog.text = "这片海里的鱼多得用船都能舀起来, 可这些懒鬼连网都懒得撒。";
			link.l1 = "去跟他们的大副聊聊吧。我觉得他会喜欢你的评论, 嘿嘿。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		//Диалог с Тичингиту, охраняющим золото
		case "SharlieEpilog_Tichingitu_21":
			dialog.text = "金子很安全, 船长 "+pchar.name+"Tichingitu会好好守护他的。";
			link.l1 = "谢谢你, 我的朋友。Alonso很快就会来接替你。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tichingitu_21";
		break;
		
		//Диалог с Книппелем, охраняющим золото
		case "SharlieEpilog_Knippel_21":
			dialog.text = "见鬼, 先生, 这破船上的老鼠比我这辈子见过的都多。";
			link.l1 = "这艘船在港口搁置太久了, 也没人好好照料。\n新船员很快就会把他们清理掉。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_21";
		break;
		
		//Диалог с Лонгвэем, охраняющим золото
		case "SharlieEpilog_Longway_21":
			dialog.text = "Longway听到了铁链的响声。船长, 你下锚了吗? ";
			link.l1 = "是我们的乘客点燃了导火索。\n现在风还很弱, 不过我希望不会持续太久。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_21";
		break;
		
		//Диалог с Тонзагом, охраняющим золото
		case "SharlieEpilog_Tonzag_21":
			dialog.text = "是啊, 见鬼…… 现在来一大杯烈朗姆酒我可一点都不介意。";
			link.l1 = "晚餐很快就好, 撑住。Alonso会来接替你。";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_21";
		break;
		
		//Диалог с Мэри перед походом в каюту
		case "SharlieEpilog_Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", 亲爱的, 你感觉怎么样? ";
			link.l1.go = "SharlieEpilog_Mary_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_12":
			dialog.text = "...";
			link.l1 = "来嘛, 亲爱的, 你不会真的因为我去店里买点酒就生气了吧? ";
			link.l1.go = "SharlieEpilog_Mary_13";
		break;

		case "SharlieEpilog_Mary_13":
			dialog.text = "你是去商店买酒了吗? 你至少也该跟我说一声吧! 我要怎么知道你不是在妓院——和哪个女人…… 还是和一群女人一起? ! ";
			link.l1 = "亲爱的, 我会冒这么大的险吗? 我可是整个群岛里最美丽、最聪明、还特别爱吃醋的老婆的男人。你真的觉得我会把时间浪费在那些廉价的码头姑娘身上吗? ";
			link.l1.go = "SharlieEpilog_Mary_14";
		break;

		case "SharlieEpilog_Mary_14":
			dialog.text = "你至少也该跟我说句话吧, 对吧! 我当时就坐在那里, 然后…… ";
			link.l1 = "我保证, 下次我不会只是跟你说说——我会带你一起去的。\n不过现在嘛…… 我突然有点好奇船长舱里的家具是不是都还好, 特别是那张床。要不要一起去检查一下? ";
			link.l1.go = "SharlieEpilog_Mary_15";
		break;

		case "SharlieEpilog_Mary_15":
			dialog.text = ""+pchar.name+"“…… 要是有人进来怎么办? \n哼…… 现在我反而更想要了。”";
			link.l1 = "那我们就一秒都别浪费。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Элен перед походом в каюту
		case "SharlieEpilog_Helena_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", 亲爱的, 你感觉怎么样? ";
			link.l1.go = "SharlieEpilog_Helena_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_12":
			dialog.text = "...";
			link.l1 = "来嘛, 亲爱的, 你不会真的因为我去店里买了点酒就生气了吧? ";
			link.l1.go = "SharlieEpilog_Helena_13";
		break;

		case "SharlieEpilog_Helena_13":
			dialog.text = "你本可以带上我一起走的。还是说你觉得我会比你那些小同伙更糟糕? ";
			link.l1 = "我觉得你肯定能轻松把他们比下去。\n不过到时候, 我可就顾不上葡萄酒了。";
			link.l1.go = "SharlieEpilog_Helena_14";
		break;

		case "SharlieEpilog_Helena_14":
			dialog.text = "那是什么事呢? ";
			link.l1 = "就像那时候和你一起偷偷溜走一样…… 现在我脑子里全是这个念头, 怎么都甩不掉。";
			link.l1.go = "SharlieEpilog_Helena_15";
		break;

		case "SharlieEpilog_Helena_15":
			dialog.text = "是吗? 那你打算具体躲到哪里去, 避开那些好奇的眼睛呢? ";
			link.l1 = "在船长的船舱里。\n我觉得我们应该试试他床的结实程度。";
			link.l1.go = "SharlieEpilog_Helena_16";
		break;

		case "SharlieEpilog_Helena_16":
			dialog.text = "哈哈。要是船长抓到我们怎么办? \n不过…… 光是想想就让我心跳加速。";
			link.l1 = "那我们就别浪费时间了! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Мэри в каюте
		case "SharlieEpilog_Mary_21":
			dialog.text = "太美妙了, 我的船长…… \n我有些消息要告诉你。";
			link.l1 = "消息? 我洗耳恭听。";
			link.l1.go = "SharlieEpilog_Mary_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Mary_22":
			dialog.text = ""+pchar.name+"…… 我们要有孩子了。我怀孕了, 对吧。";
			link.l1 = "亲爱的…… 这是真的吗? ";
			link.l1.go = "SharlieEpilog_Mary_23";
		break;

		case "SharlieEpilog_Mary_23":
			dialog.text = "“你要当爸爸了, ” "+pchar.name+"!";
			link.l1 = ""+npchar.name+"…… 这太不可思议了! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Mary_31":
			dialog.text = "你开心吗, 亲爱的? ";
			link.l1 = "开心? 你在开玩笑吗? 该死, 老子现在是世界上最幸福的人! 不过…… 你怎么不早点告诉我? ";
			link.l1.go = "SharlieEpilog_Mary_32";
		break;

		case "SharlieEpilog_Mary_32":
			dialog.text = "“要耽误我们的启程吗? 我可真想见见你父亲, " "+pchar.name+".";
			link.l1 = ""+npchar.name+"…… 我爱你! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		//Диалог с Элен в каюте
		case "SharlieEpilog_Helena_21":
			dialog.text = "你一如既往地表现得最棒, 亲爱的。我有些消息要告诉你。";
			link.l1 = "消息? 我洗耳恭听。";
			link.l1.go = "SharlieEpilog_Helena_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Helena_22":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", Monpe骑士——你要当父亲了。";
			link.l1 = "“这…… 是真的吗? ”";
			link.l1.go = "SharlieEpilog_Helena_23";
		break;

		case "SharlieEpilog_Helena_23":
			dialog.text = "就像我所承载的名字一样真实 "+npchar.name+"不到六个月, 我们就会有个孩子了——一个小小的德·莫尔先生…… 或者, 也许是位小姐。";
			link.l1 = "海伦…… 这真是难以置信! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Helena_31":
			dialog.text = "...";
			link.l1 = "所以你才没和我们一起喝酒庆祝启航啊! 但是…… 你怎么之前没告诉我呢? ";
			link.l1.go = "SharlieEpilog_Helena_32";
		break;

		case "SharlieEpilog_Helena_32":
			dialog.text = "我还担心你会决定不冒险, 留在群岛里呢。\n我希望你能完成你父亲的请求。\n还有…… 我真的很想亲自见见他。";
			link.l1 = ""+npchar.name+"…… 我爱你! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		// Диалог с Пикаром
		case "SharlieEpilog_PikarInCabin_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "哟哟…… 咱们在这儿干嘛呢? 是在造小加斯科尼人吗? ";
				link.l1 = "哈哈哈! 我要有儿子啦,  "+npchar.name+"! 我要当爸爸了! ";
				link.l1.go = "SharlieEpilog_PikarInCabin_1_1";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"。就算你地位再高, 没经过船长同意就用他的船长舱, 是不是也有点过分了? ";
				link.l1 = "对不起, 船长。但是我有个很好的理由! 我要当爸爸了! ";
				link.l1.go = "SharlieEpilog_PikarInCabin_12";
			}
			SharlieEpilog_PikarInCabin_camera_2();
		break;
		
		case "SharlieEpilog_PikarInCabin_1_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_2":
			dialog.text = "或者是女儿! ";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_2_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_2_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_3", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_3":
			dialog.text = "你竟然瞒着我, 混蛋? 我还以为你是我朋友呢! ";
			link.l1 = "我也是刚刚才知道的! 你敢信吗? 是我! 我要当爸爸了! ";
			link.l1.go = "SharlieEpilog_PikarInCabin_4";
		break;

		case "SharlieEpilog_PikarInCabin_4":
			dialog.text = "哈哈哈! 你真是开心啊, 朋友! 我从没见过你这么高兴过\n你们俩慢慢聊, 我去把大炮准备好, 等着鸣礼炮庆祝。你们准备好下命令的时候告诉我一声。";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;

		case "SharlieEpilog_PikarInCabin_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				sld = CharacterFromID("Mary");
			}
			dialog.text = "哈…… 相信我, 我早就感觉到你为什么会来这里了。";
			link.l1 = "当然不是!  "+sld.name+" 我怀孕了! 我要生个儿子了! ";
			link.l1.go = "SharlieEpilog_PikarInCabin_12_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_12_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_13":
			dialog.text = "或者是女儿! ";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_13_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_13_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_14", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_14":
			dialog.text = "咳咳…… 嗯, 衷心祝贺你! \n我会安排好——所有火炮都会齐射庆祝。你准备下令的时候只要告诉我就行。\n另外…… 船舱随时为你开放。";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;
		
		// Диалог с Пикаром после интима с женой
		case "SharlieEpilog_PikarZalp_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "咳咳…… 嗯, 父亲…… 我看您是急着再造一个继承人啊? ";
				link.l1 = "哈哈! 要是让我来, 我一次能造出一打! 那么, 伙计, 我们要不要来一轮全炮齐射? ";
				link.l1.go = "SharlieEpilog_PikarZalp_2";
				link.l2 = "恐怕事情不是这么运作的, 朋友。\n不过我们已经尽力了。";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"...";
				link.l1 = "那么, 船长, 我们要全炮齐射一轮吗? ";
				link.l1.go = "SharlieEpilog_PikarZalp_3";
				link.l2 = "现在不行。";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_PikarZalp_1";
		break;
		
		case "SharlieEpilog_PikarZalp_2":
			dialog.text = "船员们都在等你的命令呢! 只要你一声令下,  "+GetTitle(NPChar,true)+".";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_3":
			dialog.text = "船员们已经准备好了。请下令。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_final":
			dialog.text = "...";
			link.l1 = "炮手们! 开火! 全体开火! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_ZalpInSea");
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(pchar, "quest", "quest10");
			CharacterTurnToLoc(npchar, "quest", "quest10");
		break;
		
		// Диалог с отцом в поместье де Монпе
		case "SharlieEpilog_HenriDeMonper_1":
			NextMonth = GetDataMonth() + 2;
			if (NextMonth == 13) NextMonth = 1;
			else if (NextMonth == 14) NextMonth = 2;
			Month = XI_ConvertString("MonthVoc_" + NextMonth);
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"…… 孩子, 见到你我真高兴! ";
			if (GetDataMonth() >= 4 && GetDataMonth() <= 10)
			{
				link.l1 = "父亲…… 真不敢相信我又回到家了…… 我都快忘了雪是什么样子了。这里好像什么都没变过…… ";
			}
			else
			{
				link.l1 = "父亲…… 真不敢相信我又回到家了…… 连雪都特意为这一天落下来了。 "+month+"…… 这里一点都没变…… ";
			}
			link.l1.go = "SharlieEpilog_HenriDeMonper_2";
			locCameraFromToPos(-8.76, 7.86, 0.75, true, -7.41, 6.11, 0.18);
			Achievment_Set("ach_CL_202");
		break;
		
		case "SharlieEpilog_HenriDeMonper_2":
			dialog.text = "可你可不是这样啊! 你的气质, 你走路的样子, 还有那些伤疤\n"+"不, 现在站在我面前的, 已经不再是当年我送去远方的那个被宠坏的孩子了。";
			link.l1 = "在加勒比海, 人会很快长大, 父亲。\n不过这些以后再聊也不迟。\n告诉我, 您的身体怎么样? 既然您穿着盛装站在我面前, 我希望病情已经好转了吧? ";
			link.l1.go = "SharlieEpilog_HenriDeMonper_3";
		break;
		
		case "SharlieEpilog_HenriDeMonper_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				dialog.text = "唉,  "+pchar.name+", 她只是抱得我更紧了。可我怎么能穿着普通的衣服去迎接我心爱的儿子呢? 对我来说, 这是个大日子,  "+pchar.name+"\n"+"看起来你有个人要介绍给我。";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_10");
			}
			else
			{
				dialog.text = "“唉, ” "+pchar.name+", 这些年她的掌控只会越来越强。但我怎能穿着平常的衣服去见我心爱的儿子呢? 对我来说, 这是个重要的日子,  "+pchar.name+"\n"+"我看你不是一个人来的\n"+"你路上一定饿了吧? Suzanne已经按你喜欢的方式做了鹅肝! \n"+"来桌边吧——你可以一路上给我们介绍一下! ";
				link.l1 = "我得承认, 刚靠近庄园的时候我就闻到那股味道了! ";
				link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "...";
			link.l1 = "父亲, 请允许我介绍一下我的妻子—— "+sld.name+" "+pchar.lastname+". "+sld.name+", 这位是我父亲——骑士 "+GetCharacterName("Henri")+" "+GetCharacterName("德·蒙佩")+".";
			link.l1.go = "SharlieEpilog_HenriDeMonper_5";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
				dialog.text = ""+pchar.name+", 我真是被迷住了! 你的新娘可一点都不像我们这里那些被宠坏的上流小姐。我敢说, 她驾船的本事, 和驾驭我儿子的心一样高明。";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_1";
				CharacterTurnByChr(npchar, sld);
			}
			else
			{
				sld = CharacterFromID("Mary");
				dialog.text = "很高兴见到您, 夫人。请相信, 我儿子的眼光非常出色! ";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_1";
				CharacterTurnByChr(npchar, sld);
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2":
			dialog.text = "您太抬举我了, 骑士先生! 您说得对, 我确实能在最猛烈的风暴中掌舵。\n不过, 至于您儿子的心——根本无需引导。我们的目标和理想早已一致。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_2_1";
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_3":
			dialog.text = "贝努瓦院长称你为聪明又勇敢的年轻女子——看来他并没有夸大其词。我很高兴 "+pchar.name+" 我在你身上找到的, 不仅仅是妻子, 更是灵魂的真正伴侣\n"+"你旅途劳累, 肯定饿了吧。Suzanne已经按你喜欢的方式准备好了鹅肝! \n"+"那么, 各位, 请一起到桌边来吧! \n路上也希望大家能更好地了解彼此。";
			link.l1 = "我得承认, 刚靠近庄园的时候我就闻到那股味道了! ";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2":
			dialog.text = "很高兴见到你, 骑士先生!  "+pchar.name+" 我听说了好多关于你的事, 我想象中的你就是这样, 对吧! ";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_2_1";
			CharacterTurnByChr(pchar, npchar);
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_3":
			sld = CharacterFromID("Mary");
			dialog.text = ""+pchar.name+", 我太着迷了! 你的新娘可不像那些沙龙里涂脂抹粉的贵妇——这才是她真正的价值\n"+"我觉得你选择了一朵美丽的玫瑰, 而不是那些被宠坏、善变的百合。";
			link.l1 = "“野玫瑰号, 父亲…… ” "+sld.name+"  ——她可是个真正的宝藏。等你更了解她之后, 一定会同意我的看法。";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_4";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_4":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "ты познакомишь меня с остальными";
			else sStr = "ты представишь меня нашему гостю";
			dialog.text = "那我们就别再耽搁了! 你一路赶来肯定饿坏了。Suzanne已经按你喜欢的方式准备好了鹅肝! \n"+"大家, 开饭啦! 路上我希望\n "+sStr+"";
			link.l1 = "我得承认, 刚走近庄园的时候我就闻到那股味道了! ";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			CharacterTurnByChr(CharacterFromID("HenriDeMonper"), pchar);
		break;
		
		case "SharlieEpilog_HenriDeMonper_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_14");
		break;
		
		case "SharlieEpilog_HenriDeMonper_7":
			dialog.text = "...";
			link.l1 = "亲爱的, 你一定得尝尝这个——用我们家族秘方做的鹅肝, 简直无与伦比! 这秘方是祖父传下来的——他是从某个地中海国家得来的。";
			link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_15");
		break;
		
		// диалог на ужине в поместье де Монпе
		case "SharlieEpilog_InKitchenDeMonpe":
			dialog.text = "";
			link.l1 = "我不想让我们的宴会以沉重的气氛开始, 但作为一家人, 我们必须铭记先人。请大家举杯, 为米歇尔致敬。愿上主赐予他的灵魂安宁。";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_2":
			dialog.text = "";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "добрых друзей";
				else sStr = "соратника";
				dialog.text = "";
				link.l1 = "“我有好多问题想问你, ” "+pchar.name+"…… 不过, 先让你妻子说说她的想法, 然后\n "+sStr+"。请告诉我你是怎么遇到Charles的。";
			}
			else
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "твоих добрых друзей";
				else sStr = "твоего друга";
				dialog.text = "";
				link.l1 = "“我有好多问题想问你, ” "+pchar.name+"…… 不过, 先让我说一句\n "+sStr+"。请告诉我, 你是怎么遇到Charles的? ";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		// if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
		
		case "SharlieEpilog_InKitchenDeMonpe_4":
			dialog.text = "";
			link.l1 = "我也跟你一样迫不及待想听听这个! ";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "我的生命曾经危在旦夕……  "+pchar.name+"像个真正的绅士一样, 他什么坏事都没让发生! 他为我挺身而出, 把那些混蛋都收拾了, 对吧! ";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = ""+pchar.name+" 把我从那个敢于…… 绑架我的英国恶棍手里救了出来。如果你晚来哪怕一个小时, 我们就永远不会相遇了。";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5_1":
			dialog.text = "";
			link.l1 = "我从未怀疑过他会像真正的贵族那样行事。对我们家来说, 荣誉不仅仅是一个词。我为你感到骄傲, 孩子。";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = ""+sld.name+" 偷偷溜进白人的房子找吃的。被白人抓住 "+sld.name+" ——然后被关进了监狱。船长 "+pchar.name+" 来救我 "+sld.name+" 从监狱出来。自那以后 "+sld.name+" 为船长效劳 "+pchar.name+" 直到我最后一口气也会忠诚于你。";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6_1":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = "得知我的儿子不仅是个贵族, 还是个善良的人, 这让我感到十分欣慰。他身边有像你这样忠诚的朋友, 我很高兴。 "+sld.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "那位船长曾经来我家找工作。我给了他个差事, 他也干得不错。老板看上了他, 一直把他拉进自己的事里, 而我则被派到他的船上——去盯着点…… 然后那个…… 先生悄悄起锚, 炮弹差点擦到我的胡子, 连招呼都没打就离开了群岛, 把船长一个人丢在他自己搅出来的烂摊子里。我向船长自荐帮忙, 虽然理查德对他很刻薄——炮弹都打到他屁股上了——可船长并没有把我赶走。";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Longway和那位好船长曾为同一个人效力。\n可那个人背叛了Longway。\n于是Longway决定: 再也不为那个人卖命了。\n好船长把我带上了他的船, 让我当军官, 还为Longway做了很多事。";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "我们第一次相遇是在布里奇顿的酒馆里:  "+pchar.name+" 他在寻找一个目标, 而我正需要一个可靠的帮手。那次相遇只是开始——很快, 一连串的事件让我们的命运紧紧相连。我成了他的副官, 现在我可以毫不犹豫地称他为朋友——一个我愿意为之拼命的人。";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7_2":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "能透过表象看清本质, 是一种难得的天赋。我想这说明我的儿子并非毫无见识。";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "我很高兴我的儿子不仅仅是个冷酷无情的士兵, 而是真正懂得照顾同伴的领袖。";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "不是每天都能听到这样的话。我想, 这正是最好的证明, 说明我的儿子不仅是个出色的水手, 也是个真正的朋友。";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8":
			dialog.text = "";
			link.l1 = "我们在波尔多相遇。船长以乘客的身份登上了我们的船, 我们把他送到了马提尼克。从那以后——直到我们被送到这里——我一直是他船员的代言人, 并且目睹了\n "+GetFullName(pchar)+" 一步一步, 他成就了今天的自己。";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8_1":
			dialog.text = "";
			link.l1 = "那么, 你认识查尔斯还是我坚持让他离开我们家的那个讨人嫌的小子的时候? 我想, 先生, 你我之间会有很多话要聊。";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_9";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_9":
			dialog.text = "";
			link.l1 = "亲爱的 "+pchar.name+", 你已经走过了一段漫长而辉煌的旅程…… 你本只是为了猎取一张兔皮才踏入荒野大草原, 结果却与狮子搏斗, 并最终凯旋归来, 肩上披着狮皮。现在, 我比以往任何时候都更加安心, 不再为我们的庄园和所有土地的命运担忧了。";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_10";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_10":
			dialog.text = "";
			link.l1 = "我迫不及待想尽快把我们家族的事务交到你手上。\n工作肯定少不了, 但我相信主必定垂青于你, 你不仅会守护好托付给你的家业, 还会让蒙佩家族的荣耀和财富更上一层楼。";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_11";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_11": //выбор Шарля
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = "能成为您的儿子和继承人, 是我莫大的荣幸。我会欣然承担起我们家族的一切责任。我相信我的妻子一定会成为我坚强的后盾。我承诺会尽我所能, 让我们的家族更加荣耀…… 而我们家族繁荣的第一步, 就是迎来一个孩子的诞生! \n";
				link.l1.go = "SharlieEpilog_ChooseEstate_HaveWife_1";
			}
			else
			{
				link.l1 = "能成为您的儿子和继承人, 是我莫大的荣幸。我会欣然承担起我们家族的一切责任, 并承诺竭尽全力让我们的家族更加荣耀。";
				link.l1.go = "SharlieEpilog_ChooseEstate_Single_1";
			}
			link.l2 = "父亲, 我在新世界的这些年已经改变了我。恐怕我再也无法适应欧洲这里那种安稳的生活节奏了。";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_HaveWife_1";
			}
			else
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_Single_1";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		// --> Выбрал остаться в поместье с женой
		case "SharlieEpilog_ChooseEstate_HaveWife_1":
			dialog.text = "";
			link.l1 = ""+pchar.name+", 难道…… ";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_HaveWife_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "“是的, 父亲。” "+sld.name+" 怀孕了。";
			link.l1.go = "SharlieEpilog_HaveWife_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_13":
			dialog.text = "";
			link.l1 = "这真是天大的好消息啊, 我亲爱的孩子! 主已经听到了我的祈祷! 在座的各位都要作证: 为了庆祝新生儿的到来, 我要在我们的庄园举办史上最盛大的舞会! 让我们举杯——为继承人干杯! ";
			link.l1.go = "SharlieEpilog_HaveWife_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_HaveWife_14":
			dialog.text = "";
			link.l1 = "或者是个女继承人! ";
			link.l1.go = "SharlieEpilog_HaveWife_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_15":
			dialog.text = "";
			link.l1 = "为我们家族故事的新篇章干杯! ";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_16":
			dialog.text = "";
			link.l1 = "敬未来的战士或好女儿! ";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_HaveWife_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "为新生儿的健康干杯! ";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "为把你们带到一起的机缘干杯! ";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "敬你们家族光明的未来! ";
			}
			link.l1.go = "SharlieEpilog_HaveWife_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_HaveWife_18":
			dialog.text = "";
			link.l1 = "“敬未来的Alonso de Mor, 或者小Alonsita de Mor! ”";
			link.l1.go = "SharlieEpilog_HaveWife_19";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_HaveWife_19":
			dialog.text = "";
			link.l1 = "“啊哈哈! ”";
			link.l1.go = "SharlieEpilog_HaveWife_20";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_20":
			dialog.text = "";
			link.l1 = "“哈哈! ”";
			link.l1.go = "SharlieEpilog_HaveWife_21";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_21":
			dialog.text = "";
			link.l1 = "“哈哈哈! ”";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_toast":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_toast");
		break;
		// <-- Выбрал остаться в поместье с женой
		
		// --> Выбрал остаться в поместье будучи холостяком
		case "SharlieEpilog_ChooseEstate_Single_1":
			dialog.text = "";
			link.l1 = "能成为您的儿子和继承人, 是我莫大的荣幸。我会欣然承担起家族的一切责任, 并承诺竭尽全力让我们的家族更加荣耀。";
			link.l1.go = "SharlieEpilog_ChooseEstate_Single_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_ChooseEstate_Single_2":
			dialog.text = "";
			link.l1 = "“告诉我, ” "+pchar.name+", 你有没有考虑过我提出让你娶伊冯的建议? ";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_13":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseCaribbean"))
			{
				link.l1 = "我承认, 父亲…… 伊冯从未真正走进我的心里。不过, 新大陆有许多出色的女人。我向您保证——等我遇到对的人, 我绝不会犹豫。";
			}
			else
			{
				link.l1 = "我承认, 父亲…… Yvonne从来没有走进我的心里。不过法国有很多出色的姑娘。我向您保证——等我遇到真正值得的人, 我绝不会犹豫。";
			}
			link.l1.go = "SharlieEpilog_Single_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_14":
			dialog.text = "";
			link.l1 = "我喜欢你的精神, 亲爱的孩子。让我们举杯——为你, 为你的成就, 也为你值得骄傲的归来! ";
			link.l1.go = "SharlieEpilog_Single_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_15":
			dialog.text = "";
			link.l1 = "敬真正的朋友, 没有他们, 你在新世界根本活不下去! ";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_Single_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_16":
			dialog.text = "";
			link.l1 = "敬祝查尔斯船长和他那颗宽广的心! ";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_Single_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "敬献给船长的钢铁意志! ";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "“为我们船长的智慧干杯! ”";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "为忠诚与事业干杯! ";
			}
			link.l1.go = "SharlieEpilog_Single_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_Single_18":
			dialog.text = "";
			link.l1 = "“永远全身而退! ”";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		// <-- Выбрал остаться в поместье будучи холостяком
		
		// Шарль губернатор разговаривает с зелёным капитаном
		case "SharlieEpilog_GreenCaptain":
			dialog.text = "";
			link.l1 = "我听说你一直很坚持要见我。那是什么事让你来找马提尼克总督的? ";
			link.l1.go = "SharlieEpilog_GreenCaptain_1";
			locCameraFromToPos(-1.80, 3.84, -9.08, true, -2.38, 2.21, -7.33);
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer_common_2.wav");
		break;
		
		case "SharlieEpilog_GreenCaptain_1":
			dialog.text = "我想谈谈为法国王室效力的事。";
			link.l1 = "是的, 我确实有个任务要交给你, 这需要你发挥全部的机智, 还有你的海战本领。你准备好证明自己了吗? ";
			link.l1.go = "SharlieEpilog_GreenCaptain_2";
		break;

		case "SharlieEpilog_GreenCaptain_2":
			dialog.text = "阁下, 您能详细说明一下接下来的任务性质吗? ";
			link.l1 = "当然。你需要找到那艘名叫“Santa Esperanza”的西班牙信使船, 登上去, 把你在船长舱里找到的所有文件都带给我。我说的那艘船大约十二天后会经过特立尼达附近。\n";
			link.l1.go = "SharlieEpilog_GreenCaptain_3";
		break;

		case "SharlieEpilog_GreenCaptain_3":
			dialog.text = "好吧, 这个任务就交给我了。我要找什么样的文件? ";
			link.l1 = "信件往来。其中有一些对我来说非常重要的文件。不过你不用翻看那些文件, 只要把整个包裹原封不动地带给我就行。为此我会付你一万五千比索…… 所以, 我会在我的府邸等你带来结果。";
			link.l1.go = "SharlieEpilog_GreenCaptain_4";
		break;

		case "SharlieEpilog_GreenCaptain_4":
			dialog.text = "我想我不会让您久等的, 阁下。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_5");
		break;
		
		//Шарль разговаривает с комендантом форта
		case "SharlieEpilog_KomendantFort":
			dialog.text = "大人…… 我可以汇报了吗? ";
			link.l1 = "“报告, ” "+GetAddress_Form(NPChar)+" "+npchar.lastname+".";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) link.l1.go = "SharlieEpilog_KomendantFort_1";
			else link.l1.go = "SharlieEpilog_KomendantFort_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\military02.wav");
		break;
		
		case "SharlieEpilog_KomendantFort_1":
			dialog.text = "咳嗯…… ";
			link.l1 = "请直说吧。我对我的妻子没有任何秘密。";
			link.l1.go = "SharlieEpilog_KomendantFort_2";
		break;
		
		case "SharlieEpilog_KomendantFort_2":
			dialog.text = "情报报告: 一支中队已从威廉斯塔德起航。舰队的旗舰是二级战列舰“金狮号”, 堪称海上巨兽。该中队配备了两百五十多门火炮和一千五百多名士兵。他们的目标是圣皮埃尔。\n";
			link.l1 = "嗯…… 那我们几乎没有时间准备了。";
			link.l1.go = "SharlieEpilog_KomendantFort_3";
		break;

		case "SharlieEpilog_KomendantFort_3":
			dialog.text = "总督, 有什么吩咐? ";
			link.l1 = "我们有几艘船停泊在外锚地, 随时准备从敌人的后方发动攻击…… ";
			link.l1.go = "SharlieEpilog_KomendantFort_4";
		break;

		case "SharlieEpilog_KomendantFort_4":
			dialog.text = "你打算从两边夹击他们吗? ";
			link.l1 = "没错。要塞会吸引他们的火力。等到夜幕降临, 我指挥的中队会从海上发起攻击。我们会分散他们的注意力, 然后港口会派出装满沥青和木板的火船。他们的舰队连一块木屑都不会剩下。";
			link.l1.go = "SharlieEpilog_KomendantFort_5";
		break;

		case "SharlieEpilog_KomendantFort_5":
			dialog.text = "好极了, 阁下! 我现在下令开始准备吗? ";
			link.l1 = "开始吧。愿上主与我们同在。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_11");
		break;
		
		// Стражник вызывает Алонсо
		case "SharlieEpilog_Guard":
			dialog.text = "";
			link.l1 = "卫兵, 去叫Alonso。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoArrive");
		break;
		
		//Шарль разговаривает с Алонсо после коменданта
		case "SharlieEpilog_Alonso35":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
			{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
				dialog.text = "总督, 先生…… ";
				link.l1 = ""+npchar.name+", 荷兰舰队随时会到, 马上就要开始围攻了。听我命令: 带上Philippe, 然后\n "+sld.name+", 把他们立刻带去见修道院院长。让他召集所有的妇女、孩子和老人, 确保他们的安全。";
				link.l1.go = "SharlieEpilog_Alonso36_Wife";
				break;
			}
			dialog.text = "总督先生…… ";
			link.l1 = ""+npchar.name+", 荷兰舰队随时可能抵达, 对这座城市展开围攻。告诉修道院院长, 把所有妇女、孩子和老人都集中起来, 确保他们的安全。至于你, 我打算让你负责火船, 具体细节稍后再说。最重要的是, 我们必须保护平民。";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;

		case "SharlieEpilog_Alonso36_Wife":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "我可不这么认为 "+sld.name+" 会同意加入其他女人。她快无聊死了。";
			link.l1 = "嗯…… 那就让她准备好战斗吧。你也不会闲着——你要指挥火船。细节以后再说。现在——照顾好我的儿子。";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;
		
		case "SharlieEpilog_Alonso37":
			dialog.text = "这将是我的荣幸! 我可以开始了吗? ";
			link.l1 = "我允许了。去吧。我们每一秒都很宝贵。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_13");
		break;
		// --> Выбрал отправиться назад на Карибы с женой
		case "SharlieEpilog_ChooseCaribbean_HaveWife_1":
			dialog.text = "";
			link.l1 = "嗯…… 我承认, 我早就猜到你会这么说——虽然我本来希望你能给出不同的答案。不过我尊重你的选择, 不会再劝你改变主意。";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_2":
			dialog.text = "";
			link.l1 = "我知道我让你失望了。不过我带来了一个消息, 我希望这个消息能盖过之前说过的一切。";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_3":
			dialog.text = "";
			link.l1 = "我洗耳恭听。";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "我打算在这里待至少一年。 "+sld.name+" 以她现在的状况, 绝对不能摇晃。";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_5";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_5":
			dialog.text = "";
			link.l1 = ""+pchar.name+", 难道…… ";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		// <-- Выбрал отправиться назад на Карибы с женой
		
		// --> Выбрал отправиться назад на Карибы один
		case "SharlieEpilog_ChooseCaribbean_Single_1":
			dialog.text = "";
			link.l1 = "嗯…… 我得承认, 我早就猜到你会这么说——虽然我其实希望你能给我一个不一样的答案。不过, 我尊重你的选择, 不会再劝你改变主意。可是你告诉我, \n "+pchar.name+", 你考虑过我提出让你娶Yvonne的建议了吗? ";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		// <-- Выбрал отправиться назад на Карибы один
		
		//Диалог Шарль и Мишеля на Рифе Скелета
		case "SharlieEpilog_Mishelle_1":
			dialog.text = "忍不住了, 是吧? ";
			link.l1 = "是你? ! 我是不是在做梦? ";
			link.l1.go = "SharlieEpilog_Mishelle_2";
			SharlieEpilog_OnReefs_6();
			PlaySound("Voice\" + LanguageGetLanguage() + "\sharlie\mishelle-04.wav");
		break;

		case "SharlieEpilog_Mishelle_2":
			dialog.text = "对轻松得利的渴望、对权力的追逐、还有那种无敌的错觉…… 哥哥, 到底是哪一样毁了你? 是什么迷住了你的心智, 就像迷住所有白人的心一样? ";
			link.l1 = "滚出去! 你只是个鬼魂! 这里不属于你! ";
			link.l1.go = "SharlieEpilog_Mishelle_3";
		break;

		case "SharlieEpilog_Mishelle_3":
			dialog.text = "你还是不明白吗? Spectra sunt memoria peccatorum。你就是那个幽灵…… 一个被贪婪和盲目虚荣吞噬的加勒比传奇。为了黄金, 你杀了多少人,  "+pchar.name+"?";
			link.l1 = "好吧, 亲爱的哥哥, 老子不介意再杀你一次! 这是你自找的! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_OnReefs_9");
		break;
		
		
		
		
		
	}
}