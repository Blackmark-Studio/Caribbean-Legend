// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string 	sTemp;
	int 	amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref 	shTo;
	string 	s1;
 
	switch (Dialog.CurrentNode)
	{		
		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "ふう……なんてひどい気候だ……私の名前は "+GetFullName(npchar)+"、そしてこの神に見捨てられた島々で俺が一番の船大工じゃなかったら神に呪われてもいいぜ。だが、 この湿気には本当にやられるな……";
				Link.l1 = pcharrepphrase("くそっ、サメが千匹もいるってのに、爺さんのぶつぶつまで聞かされるとはな。俺の名は "+GetFullName(pchar)+"、俺のことは聞いたことがあるだろう。","湿気のせいじゃなくて、年のせいだよ、旦那。俺の名前は "+GetFullName(pchar)+"、俺のことは聞いたことがあるだろう。");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = "ああ、またお前か、いつも自分の問題ばかり言いやがって……（ゴホッ）。";
				link.l1 = pcharrepphrase("おっしゃる通り、また俺だぜ。だが、まだ神様に魂を渡しちまう前に仕事の話をしようじゃねえか。","記憶力は素晴らしいですね。さて、もしよろしければ、もう少し具体的な質問に入りましょう。");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("お前のぶつぶつにはもううんざりだ。じゃあな。","もう行く時間だ。邪魔して悪かったな");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
		//Jason ----------------------------------- Хронометр Алекса ------------------------------------------
			if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
			{
				dialog.text = "ああ、船長 "+GetFullName(pchar)+"！立ち寄ってくれて嬉しいぜ！";
				Link.l1 = "何か用があるみたいだな？普段はそんなに丁寧じゃねえだろ。";
				Link.l1.go = "clock_begin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
			{
				dialog.text = "手ぶらで戻ってきたな、船長！…客人たちはどうしたんだ？";
				Link.l1 = "奴らは行っちまった。俺が頼んだら、もう行っちまったんだ。";
				Link.l1.go = "clock_complete";
				break;
			}
		//<-- хронометр Алекса
			dialog.text = "ああ、またお前か、いつも自分の問題ばかり話しやがって……（ゴホッ）";
			link.l1 = pcharrepphrase("あんたの言う通り、また俺だよ。だが、まだ神様に魂を渡しちまう前に、仕事の話をしようじゃねえか。","記憶力がいいですね。さて、もしよろしければ、もう少し具体的な質問に入りましょう。");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("お前のぶつぶつにはもううんざりだ。じゃあな。","もう行く時間だ。邪魔して悪かったな。");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "最近の若い連中は……まったく礼儀ってもんがないな。血の気は多いし、手も荒い。で、何の用だ？";
			link.l1 = pcharrepphrase("その通りだ。しかし、遅かれ早かれ全ては終わるもんでな、どうやらお前の番も近いようだぜ…","何となく思うんだが、あんたも若い頃は年長者にあまり敬意を払ってなかったんじゃねえか？俺の考え、当たってるか？");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "年長者に逆らうんじゃねえぞ、小僧。";
			link.l1 = pcharrepphrase("落ち着けよ。冷静になれ。無理しすぎるな、そうじゃねえと心臓発作を起こすかもしれねえぞ。 カリブ一の船大工を死なせたなんて言われたくねえからな。さて、本題に入ろうぜ。","年長者として敬意を表して無礼は許してやる。\nさて、話はこれで終わりか？それじゃあ、本題に入ろう。");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("よし、俺の説教はこれくらいにしとくぜ！じゃあな！","どうやら意見が合いそうにないな。では、さらばだ。");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "（ゴホッゴホッ）…年寄りを放っておいてくれんのう。今度は何の用じゃ、 "+GetAddress_Form(NPChar)+"? ";
			link.l1 = pcharrepphrase("造船所のサービスを利用したいんだ。","造船所のサービスを利用したいんだ。");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "質問がある。";
			Link.l2.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "財政について話したいんだ。";
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase("くそっ、急ぎの用事が二つばかりあるんだ。じゃあな。","もう行かなくちゃ。すまねえ。");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":			
			dialog.Text = "さあ、何の用だ？年寄りを邪魔するんじゃねえ…";
			link.l2 = "俺はただ造船所のサービスを利用したいだけだ。";
			link.l2.go = "shipyard";
			link.l3 = "船のために武器が必要だ。";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l4 = "俺の帆の見た目を変えたいんだ。";
					link.l4.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "俺の船はかなり……特別なんだ。ちょっと手を加えたいんだが。";
					link.l50.go = "FDM";
			}
			/*if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_cabin") && npchar.quest.FDM_cabin == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "船室の改修用にさらに宝箱を用意したぜ。";
					link.l50.go = "FDM_cabin_pay";
			}*/
			// Xenon -->
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmoney")
			{
					link.l50 = "船の再建について来たんだ。";
					link.l50.go = "FDM_hull_givemoney";
			}

			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmaterials")
			{
					link.l50 = "船の修復について来たんだ。";
					link.l50.go = "FDM_hull_checkmaterials";
			}
			// <-- Xenon
			link.l9 = pcharrepphrase("くそっ、急ぎの用事が二つあるんだ、じゃあな。","俺はもう行かなきゃならねえ。悪いな。");
			Link.l9.go = "ship_tunning_not_now";
		break;	
		
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問があるんだ？","どうされましたか？"),"少し前に俺に何か質問しようとしたよな……","俺の造船所でも、この町のどこでも、こんなに好奇心旺盛な連中に会ったことはねえな。","質問が多いな。俺の仕事は船を造ることだ。さあ、それを片付けようぜ。","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直した……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ…","ふむ、そうだな……","よし、では……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "聞いてくれ、通り抜けたいんだが、その扉は鍵がかかってるんだよ…";
				link.l2.go = "Step_Door_1";
			}

			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "取引を提案したいんだ。";
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if(CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
			{
				link.l1 = "フリゲート艦の資材について来たんだ。";
				link.l1.go = "clock";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "「聞け、」 "+npchar.name+"、最近イスラ・テソロでミゲル・ディチョソを見かけたか？";
				link.l1.go = "tieyasal";
			}
		break;
//*************************** Генератор - "Найденные судовые документы" **************
		
		case "Al_ShipLetters_1":
			dialog.text = "条件を言え。";
			s1 = "I lucked into finding an absolutely legal ship's documents packet that hasn't been called for search yet.";
			s1 = s1 + "The ship is afloat and it hasn't been excluded from the registry, don't worry. Just a blind fool-owner had the misfortune of losing these papers...";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = "Let me take a look! It really looks to be freshly filled out. Well, luck is in your favor, sir! ";
			s1 = s1 + "I actually needed a packet just like this. I, in turn, will offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What do you say?";
			dialog.text = s1;
			link.l1 = "まさに王家の寛大さだな！もちろん同意するぜ！";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "いや、そうは思わねえな。";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		

//*************************** Открывание двери ***************************
 		case "Step_Door_1":
			dialog.text = "その通りだ。この扉を通りたきゃ、俺に二万ペソ払ってもらうぜ。払わねえなら開けねえぞ。 ここは慈善事業じゃねえんだ。\nそれに、あそこへ行くのはやめといた方がいいぜ。行かない方が身のためだ……";
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = "ほら、金だ。開けろ。";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "そんな大金は持ってねえ。";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "ありえねえ！俺がドアなんかに金を払うわけねえだろ。";
    		link.l2.go = "exit";
		break;
		
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = "入れよ。ドアは開いてるぜ。礼なんていらねえからな！";
			link.l1 = "いや、なぜだ。ありがとう。 "+npchar.name+"...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		
 		case "Step_Door_3":
			dialog.text = "持ってきたら戻ってこい。そうでなけりゃ、俺を説得しようなんて無駄だぜ……";
			link.l1 = "ああ、言葉も出ねえぜ！";
			link.l1.go = "exit";
		break;
		
	// ------------------------------------------- хронометр Ђлекса ----------------------------------------------// Addon-2016 Jason замена дублонов на песо везде
		case "clock_begin":
			dialog.text = "頼むよ、そんなに年寄りに厳しくしないでくれ……本当に助けが必要なんだ、船長。";
			link.l1 = "教えてくれ、親方。何があったんだ？";
			link.l1.go = "clock_begin_1";
		break;
		
		case "clock_begin_1":
			sTotalTemp = "Steven Dodson";
			if (pchar.questTemp.Alex.Clock == "terrax") sTotalTemp = "Marcus Tyrex";
			dialog.text = "「我ら沿岸同盟の新しい頭領、」 "+sTotalTemp+"、新しい船、フリゲート艦を注文したんだ。それに加えて、かなり難しい注文もつけてきた。強化された船体、高速、 優れた操縦性、さらに可能な限り最大口径の大砲も要求されたんだ\n提督――いや、兄弟団の長の船は特別なものでなければならないのは分かるが、そのためには特別な素材が必要になる。 君も聞いたことがあるだろう。アイアンウッド、樹脂、船用の絹、それにロープだ……";
			link.l1 = "じゃあ、そのことをバラバラ兄弟団の頭に伝えてくれ。\nそれとも、お前は警戒してるのか "+sTotalTemp+" そのことでお前の首をはねるってのか？";
			link.l1.go = "clock_begin_2";
		break;
		
		case "clock_begin_2":
			dialog.text = "俺はあいつに言ったんだ…実はな、うちの新しい親方には、その材料を探して持ってくる時間も余裕もねえんだよ。どれだけ珍しいものか、 あんたも分かってるだろう。そいつらがなきゃ、言われた仕様のフリゲートなんて絶対に造れねえんだ。";
			link.l1 = "「それで、俺に船の材料を探してこいってことか？」";
			link.l1.go = "clock_begin_3";
		break;
		
		case "clock_begin_3":
			dialog.text = "そうだな。あんたは我らの親方の良き友人だ。 "+sTotalTemp+" 「彼自身があなたに多大な恩があると言っており、あなたには最大限の敬意を払うべきだと主張しています……それで思ったんですが、あなたは彼の友人ですし、手を貸していただけませんか？同時に、 私がどれだけ困った立場にいるかもご理解いただけますよね？材料費はすべてお支払いします。」\n "+sTotalTemp+" 金にケチじゃねえ。";
			link.l1 = "申し訳ありませんが、旦那、俺もあいつと同じくらい忙しいんです "+sTotalTemp+"。材料を集めるのは永遠にかかるかもしれねえ。だから、他の奴に頼んだほうがいいぜ。";
			link.l1.go = "clock_exit";
			link.l2 = "さて、もし "+sTotalTemp+" お前から船を注文したんだ――もちろん手伝うぜ。本当に俺たちは仲間だし、仲間同士は助け合わなきゃな。どれくらい資材が必要なんだ？";
			link.l2.go = "clock_begin_4";
		break;
		
		case "clock_exit":
			dialog.text = "それは残念だ。本当に残念だぜ。お前に期待してたんだがな。まあ、世の中、ダメなものはダメってことか……";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
		
		case "clock_begin_4":
			dialog.text = "鉄木が100単位、樹脂の容器が150個、船用シルクが110反、麻縄が90巻足りないんだ。\nどう思う？これ全部、四ヶ月以内に揃えてくれないか？もうこれ以上時間はないんだ。";
			link.l1 = "少なくとも試してみることはできるぜ。で、報酬の方はどうするんだ？";
			link.l1.go = "clock_begin_5";
		break;
		
		case "clock_begin_5":
			dialog.text = "俺の料金はこうだぜ：鉄木は1本4000ペソ、樹脂は1樽1400ペソ、絹は1反2500ペソ、ロープは1巻1500ペソだ。\n全部まとめて持ってきてくれたら、俺から素敵な贈り物をやるぜ。";
			link.l1 = "何だろうな？";
			link.l1.go = "clock_begin_6";
		break;
		
		case "clock_begin_6":
			dialog.text = "まずは材料を持ってきてくれ。だが、保証するぜ、これはお前にとって役に立つし、しかも唯一無二の品だ。 カリブ中どころか、世界中探しても他にないぜ。少しは興味が湧いて、材料集めにやる気が出たんじゃねえか？";
			link.l1 = "へえ、旦那はまるで妖精みたいに抜け目がねえな！\nよし、取引成立だ。";
			link.l1.go = "clock_begin_7";
		break;
		
		case "clock_begin_7":
			dialog.text = "とても嬉しいです。あなたの帰りを楽しみにしています。";
			link.l1 = "あまり時間がかからなければいいが……";
			link.l1.go = "clock_begin_8";
		break;
		
		case "clock_begin_8":
			DialogExit();
			pchar.questTemp.AlexClock = "go";
			npchar.quest.clock = "true";
			SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
			AddQuestRecord("alex_clock", "1");
			// запоминаем переменные
			pchar.questTemp.AlexClock.Sandal = 100;
			pchar.questTemp.AlexClock.Oil = 150;
			pchar.questTemp.AlexClock.Shipsilk = 110;
			pchar.questTemp.AlexClock.Ropes = 90;
		break;
		
		case "clock":
			dialog.text = "素晴らしい！今日は何を持ってきたんだ？";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "鉄材、数量 "+FindRussianQtyString(iSan)+".";
				link.l1.go = "sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "樹脂、数量は "+FindRussianQtyString(iOil)+".";
				link.l2.go = "oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "船用の絹、数量は "+FindRussianQtyString(iSil)+".";
				link.l3.go = "shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "麻縄、数量は "+FindRussianQtyString(iRop)+".";
				link.l4.go = "ropes";
			}
			link.l5 = "今は特に用はない。ただ、俺たちの取り決めがまだ有効か確認したかっただけだ。";
			link.l5.go = "exit";
		break;
		
		case "clock_1":
			if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
			{
				dialog.text = "素晴らしい！必要な資材はすべて揃ったぜ。手伝ってくれて本当にありがとう、船長。おかげで大助かりだ。";
				link.l1 = "はい、いつでもどうぞ、旦那。私もとても満足していますよ。友人を助けて、いい金も稼げましたからね。さて、 それでは、あなたが約束してくれた謎の品についての話に戻りましょうか。";
				link.l1.go = "clock_2";
			}
			else
			{
				dialog.text = "「俺にまだ何か驚きがあるのか、船長？」";
				link.l1 = "残念だが、今はこれで全部だ。あとは待つしかねえな。";
				link.l1.go = "exit";
				link.l2 = "ああ、もう一つあるんだ……";
				link.l2.go = "clock";
			}
		break;
		
		case "sandal": // бакаут
			amount = sti(pchar.questTemp.AlexClock.Sandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 4000*iSan;
				dialog.text = "わかった、いいだろう。俺が必要なのは "+FindRussianQtyString(amount)+" 鉄木製だな。お前が持ってきたのか "+FindRussianQtyString(iSan)+"……それで、あんたが俺に持ってくるべき物が残っているのは "+FindRussianQtyString(iTemp)+"。よし、1隻あたり4000ペソの計算で、報酬の合計は "+FindRussianMoneyString(iSum)+"。どうぞ、お受け取りください。";
				link.l1 = "ありがとう！残りもすぐに用意するぜ。";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 4000*amount;
				dialog.text = "わかった、いいだろう。俺も必要なんだ "+FindRussianQtyString(amount)+"  鉄木製だな。お前が持ってきたのか "+FindRussianQtyString(iSan)+"。さて、これでアイアンウッドの件は片付いたな！よし、1本あたり4000ペソの計算で、あんたの報酬は合計で "+FindRussianMoneyString(iSum)+"。どうぞ、お受け取りください。";
				link.l1 = "ありがとう！";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.sandal = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "oil": // смолы
			amount = sti(pchar.questTemp.AlexClock.Oil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1400*iOil;
				dialog.text = "わかった、いいだろう。俺も必要なのは "+FindRussianQtyString(amount)+" 樹脂か。持ってきてくれたんだな "+FindRussianQtyString(iOil)+"。さて、あんたが俺に持ってくるべき残りは "+FindRussianQtyString(iTemp)+"。よし、1コンテナあたり1400ペソの計算で、あなたの報酬は合計 "+FindRussianMoneyString(iSum)+"。どうぞ、お受け取りください。";
				link.l1 = "ありがとうございます！残りもすぐにお渡しします。";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "resins");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1400*amount;
				dialog.text = "わかった、いいだろう。俺も必要なんだ "+FindRussianQtyString(amount)+" 樹脂か。持ってきてくれたんだな "+FindRussianQtyString(iOil)+"。さて、これで樹脂の処理は終わったな！よし、1コンテナあたり1400ペソの計算で、報酬の合計は "+FindRussianMoneyString(iSum)+"。どうぞ、お受け取りください。";
				link.l1 = "ありがとう！";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.oil = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "resins");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "shipsilk": // шёлк
			amount = sti(pchar.questTemp.AlexClock.Shipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 2600*iSil;
				dialog.text = "わかった、いいだろう。俺も必要なのは "+FindRussianQtyString(amount)+" 絹か。持ってきてくれたんだな "+FindRussianQtyString(iSil)+"。さて、あんたが俺に持ってくるべき残りは "+FindRussianQtyString(iTemp)+"。よし、1つあたり2600ペソの計算で、報酬の合計は "+FindRussianMoneyString(iSum)+"。どうぞ、お受け取りください。";
				link.l1 = "ありがとう！残りもすぐに渡すよ。";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "silk");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 2600*amount;
				dialog.text = "わかった、いいだろう。俺も必要なんだ "+FindRussianQtyString(amount)+" 絹か。持ってきてくれたんだな "+FindRussianQtyString(iSil)+"。さて、これで絹の件は片付いたな！1枚あたり2600ペソの計算で、報酬の合計は "+FindRussianMoneyString(iSum)+"。どうぞ、お受け取りください。";
				link.l1 = "ありがとう！";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.shipsilk = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "silk");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "ropes": // канаты
			amount = sti(pchar.questTemp.AlexClock.Ropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1500*iRop;
				dialog.text = "わかった、いいだろう。俺も必要なんだ "+FindRussianQtyString(amount)+" ロープか。持ってきてくれたんだな "+FindRussianQtyString(iRop)+"。で、まだ俺に持ってきてもらわなきゃならねえのは "+FindRussianQtyString(iTemp)+"。というわけで、1つあたり1500ペソの計算で、あなたの報酬は合計 "+FindRussianMoneyString(iSum)+"。どうぞ、お受け取りください。";
				link.l1 = "ありがとう！残りもすぐに用意するぜ。";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ropes");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1500*amount;
				dialog.text = "わかった、いいだろう。俺が必要なのは "+FindRussianQtyString(amount)+" ロープか。持ってきてくれたんだな "+FindRussianQtyString(iRop)+"。さて、ロープの件はもう片付いたぜ。よし、一本あたり1500ペソの計算で、あんたの報酬は合計で "+FindRussianMoneyString(iSum)+"。どうぞ、お受け取りください。";
				link.l1 = "ありがとう！";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.ropes = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ropes");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "clock_2":
			dialog.text = "ああ、ああ……俺の件についてだな、もちろん。うーん……ふむ……どこにやったっけな……ああ……";
			link.l1 = "どうしました、旦那？ずいぶん心配そうな顔をしてますね。何かあったんですか？何かトラブルでも？";
			link.l1.go = "clock_3";
		break;
		
		case "clock_3":
			dialog.text = "まさにその通りだ。問題がある。最近のことだ。あの財宝探しの連中め……";
			link.l1 = "落ち着け、落ち着け。そんなに心配してたら、あんたの歳じゃ体に悪いぜ。神様が守ってくれても、 あと一歩でどうなるかわからねえぞ。もしあんたが倒れたら、海賊同盟の頭のために誰がフリゲートを造るんだ？ 落ち着いて教えてくれ、その宝探しの連中ってのは一体誰なんだ？";
			link.l1.go = "clock_4";
		break;
		
		case "clock_4":
			dialog.text = "あそこの俺の机のそばに扉がある。あれは古い金庫室に直接つながってるんだ。その金庫室の宝箱のひとつに、 二十年前にあの忌々しい渦に巻き込まれてここに流れ着いた時に持っていた品々を入れた金属の箱をしまってあるんだよ……";
			link.l1 = "「煙突？何の話だ？」";
			link.l1.go = "clock_5";
		break;
		
		case "clock_5":
			dialog.text = "ああ、つい話が長くなってしまったな。年を取るのは楽じゃないぞ、若いの。すまんのう。だが、それはさておきだ。 大事なのは、お前への贈り物が入った箱が、今なら悪党どもが居座っている地下牢の宝箱にあるということじゃ。 奴らは我々の仲間でもなければ、イスラ・テソロの者でもない。\n財宝目当ての連中――誰かがここが宝の山だと吹き込んだんじゃろう。普段ならここに顔を出す度胸はないはずだが、 わしは怖くて近づけんのじゃ。奴らの顔ときたら……";
			link.l1 = "なるほどな。扉を開けろ。俺が招かれざる客どもを追い出してやるぜ。";
			link.l1.go = "clock_6";
		break;
		
		case "clock_6":
			dialog.text = "そんな簡単に？あんた一人で奴らを追い払うつもりか？怖くねえのか？頼んでくれりゃ、 俺たち全員があんたのために戦うぜ……";
			link.l1 = "話はいいから、さっさと動け、旦那。ここの扉を開けて、あとは俺に任せな。どの箱に自分の物をしまってるんだ？";
			link.l1.go = "clock_7";
		break;
		
		case "clock_7":
			dialog.text = "廊下をまっすぐ行った先に、空の木樽がずらりと並んでいる。\nその奥、目立たない場所の床に小さな箱があるんだ。俺が錠前を打ち付けておいたから、 たとえあの侵入者どもが見つけても、汚い手で中身を漁ることはできねえだろう。\nほら、これが鍵だ。";
			link.l1 = "先を考えてくれて嬉しいぜ。ここで待ってろ、どこにも行くんじゃねえぞ。";
			link.l1.go = "clock_8";
		break;
		
		case "clock_8":
			DialogExit();
			GiveItem2Character(pchar, "key3"); 
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);//офицеров не пускать
			pchar.quest.Alex_Chest.win_condition.l1 = "location";
			pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.Alex_Chest.function = "AlexClock_Chest";
			pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
			pchar.questTemp.AlexClock = "chest";
			AddQuestRecord("alex_clock", "3");
		break;
		
		case "clock_complete":
			dialog.text = "奴らはお前の話を聞いただけで出て行ったのか？";
			link.l1 = "その通りだ。あいつら、意外と礼儀正しい連中だったぜ。俺が「お前らのせいで、年季の入った有名な船大工が怯えてる」 と説明したら、年長者への敬意から素直に立ち去ったんだ。もう心配せずに下へ行っていいぜ。";
			link.l1.go = "clock_complete_1";
		break;
		
		case "clock_complete_1":
			dialog.text = "ははっ、年寄りをからかうつもりか！よし、俺の箱を渡してくれ。そしたら開けて、 お前が正当に手に入れた装置を渡してやるぜ。";
			link.l1 = "どうぞ、受け取ってくれ…";
			link.l1.go = "clock_complete_2";
		break;
		
		case "clock_complete_2":
			RemoveItems(pchar, "alexs_chest", 1);
			dialog.text = "ありがとう！さあ、開けてみよう。ほら、これを受け取ってくれ。自動機械式のタイマーだ――こんな装置はここじゃ誰も作れねえし、あと三百年は誰も作れねえだろう……ああ、すまん、年寄りの戯言だ。つまり、これは唯一無二の品ってことさ。\nこいつは全部自分で動くから、くだらねえ砂時計なんかもういらねえ。間違いもねえ！ただ、衝撃と水には気をつけろよ、 壊れたらおしまいだ。猿でも使えるタイマーだぜ。";
			link.l1 = "見てくれよ！こんな奇跡みたいなもん、生まれて初めて見たぜ！ありがとう、旦那。";
			link.l1.go = "clock_complete_3";
		break;
		
		case "clock_complete_3":
			GiveItem2Character(pchar, "clock3");
			Log_Info("You've received an automatic mechanical timer");
			SetAlchemyRecipeKnown("sextant2");
			PlaySound("interface\important_item.wav");
			dialog.text = "どういたしまして。これでいつでも正確な時間がわかるぜ。\nどこで手に入れたかは聞くなよ。教えてやらねえからな。";
			link.l1 = "誰にだって秘密はあるもんだろ、旦那？まあいいさ……秘密はそのままにしておけよ、俺も詮索はしねえ。贈り物、ありがとな！";
			link.l1.go = "clock_complete_4";
		break;
		
		case "clock_complete_4":
			dialog.text = "ご協力ありがとうございます、船長。たまには顔を見せてくれ。老いぼれ船大工のことを忘れないでくれよ。";
			link.l1 = "お前のことなんて忘れられるわけねえだろ……まあ、とにかく、絶対にやるぜ、達人アレクサス。じゃあな！";
			link.l1.go = "clock_complete_5";
		break;
		
		case "clock_complete_5":
			DialogExit();
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
			AddQuestRecord("alex_clock", "5");
			CloseQuestHeader("alex_clock");
			DeleteAttribute(pchar, "questTemp.AlexClock");
			// belamour legendary edition на пару с Акулой
			pchar.questTemp.SharkGoldFleet.KGBB = true;
			if(CheckAttribute(pchar,"questTemp.SharkFrigate")) SetTimerCondition("SharkGoldFleet", 0, 0, 30, false);
		break;
	// <-- хронометр Алекса
		
		// город майя
		case "tieyasal":
			dialog.text = "ああ、ミゲル！俺の古い知り合いだ。覚えてるぜ。あいつは何度も何度も細かいことを聞いてきたんだ。\nだがよ、電信機すら見たこともねえ奴に、どうやって無線機の中身の仕組みを説明しろってんだ？";
			link.l1 = "「えっ？…何のことだ、旦那？」";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "ああ、すまん、若いの。俺の話はあまり気にするな……うちの好奇心旺盛なミシェルは好奇心を満たして姿を消したんだ。三日前に話したばかりだったのによ。";
			link.l1 = "今ミゲルはどこにいるんだ？もし差し支えなければ教えてくれないか？";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "誰にも分からねえな。もしかしたらシャープタウンで自分の仕事をしてるかもしれねえし、 あるいはもうイスラ・テソロを出発しちまったかもしれねえ。";
			link.l1 = "なるほど。ありがとうございます、親方！";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Калеуче
		case "FDM":
			if(CheckAttribute(npchar, "quest.FDM_secondtime"))
				dialog.text = "またその「幽霊船」か……いいか、俺があれに関わってるのは、まともな船になるかもしれないって一縷の望みがあるからだ。それがなきゃ、 絶対に手を出さねえよ。海の連中はみんな同じ気持ちだと思うぜ。で、今回はその船をどうしたいんだ？";
			else	
				dialog.text = "ああ、「幽霊船」か！母親たちはお前のガレオンを使って悪さをする子供を脅してるぜ。なのにお前はあの忌々 しい船を沈めずに持ち続けることにしたんだな！船乗りどもはお前の船が地平線に見えるだけで震え上がる……で、そいつをどうしたいんだ？";
			/*if (!CheckAttribute(npchar, "quest.FDM_cabin"))
			{
				link.l1 = "臆病者どもがビクビクしてるのは面白いが、内装を見ると気が滅入るぜ。\n船室を見たか？まるで棺桶みてえだ。カビと埃だらけでよ。俺が直したいんだが、大将、あんたにできるか？";
				link.l1.go = "FDM_cabin";
			}
			if (!CheckAttribute(npchar, "quest.FDM_sails"))
			{
				link.l2 = "こんなボロボロの黒い布きれにはもううんざりだ。風を受けるのは普通の帆と同じくらいだってのは認めるが、見た目が……ひでえ。俺は普通の真っ白な帆が欲しいんだ。どうだい、親方？";
				link.l2.go = "FDM_sails";
			}*/
			
			if (!CheckAttribute(npchar, "quest.FDM_hull"))
			{
				link.l3 = "さて、そろそろまともな船に生まれ変わらせる時だと思うんだ。船自体はいいし、乗組員も慣れてるが、 大人ですら腰を抜かすような船に、ましてや子供ならなおさら、まともな船長が乗るのは格好がつかねえ。 俺は完全に作り直して、他の船長たちが俺の船を見て羨ましがるようにしたいんだ、十字を切るんじゃなくてな。で、 こんな相談をするなら、諸島で一番の船大工しかいねえだろ？\n";
				link.l3.go = "FDM_hull";
			}
		break;
		
		case "FDM_cabin":
			dialog.text = "なぜだ？俺の手はまだしっかりしてるぜ。";
			link.l1 = "...";
			link.l1.go = "FDM_cabin_s";
			//link.l2 = "贅沢は無用だ。標準を守れ。";
			//link.l2.go = "FDM_cabin_s";
		break;
		
		case "FDM_cabin_m":
			dialog.text = "わかった。ドゥブロン金貨十箱で、五日あれば仕上げてやる。";
			link.l1 = "「取引成立だ！」";
			link.l1.go = "FDM_cabin_m1";
			link.l2 = "十個の宝箱だと？千五百ドゥブロンだと？ふむ、そんな出費は少し考えさせてもらわないとな…";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_s":
			dialog.text = "ドブロン金貨の入った箱七つ、五日で仕上げてやるぜ。";
			link.l1 = "取引成立だ！";
			link.l1.go = "FDM_cabin_s1";
			link.l2 = "七つの宝箱だと？千枚以上のドゥブロン金貨か？うーん、そんな大金の出費は少し考えさせてくれ…";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_m1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 10;
			npchar.quest.FDM_cabin.type = "Cabin_Huge";
			dialog.text = "よし、支払いを待っているぞ。";
			if (iTemp > 0)
			{
				link.l1 = "俺が箱を持ってきたぜ。さてと。ほら、 "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "俺は行って、金貨を箱に入れなきゃならねえ。";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_s1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin.chest = 7;
			npchar.quest.FDM_cabin.type = "Cabin";
			dialog.text = "よし、支払いを待っているぞ。";
			if (iTemp > 0)
			{
				link.l1 = "俺は宝箱を持ってきたぜ。さてと。ほら、 "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "俺はこれから金貨を箱に入れに行かねえとな。";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_wait":
			DialogExit();
			npchar.quest.FDM_full = "cabin";
		break;
		
		case "FDM_cabin_pay":
			iTemp = GetCharacterItem(pchar, "Chest");
			amount = sti(npchar.quest.FDM_cabin.chest)-iTemp;
			Log_Info("You have given chests to Master Alexus");
			PlaySound("interface\important_item.wav");
			if (amount <= 0) // всё принес
			{
				RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin.chest));
				dialog.text = "それで、俺のところに連れて来なきゃならなかったんだな "+FindRussianQtyString(sti(npchar.quest.FDM_cabin.chest))+" 持ってきた宝箱だ "+FindRussianQtyString(iTemp)+"。支払いは用意できてる。今度は俺の番だ。ちょっと外を歩いてきな。心配すんな、全力を尽くすぜ。";
				link.l1 = "「よし……」";
				link.l1.go = "FDM_cabin_do";
			}
			else
			{
				RemoveItems(pchar, "chest", iTemp);
				dialog.text = "それで、俺のところに連れてきたってわけか "+FindRussianQtyString(sti(npchar.quest.FDM_cabin.chest))+" 持ってきた箱だ "+FindRussianQtyString(iTemp)+". "+FindRussianQtyString(amount)+" 残りの箱だ。";
				link.l1 = "承知しました、旦那。";
				link.l1.go = "FDM_cabin_wait";
				npchar.quest.FDM_cabin.chest = amount;
			}
		break;
		
		case "FDM_cabin_do":
			DialogExit();
			SetLaunchFrameFormParam("Five days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.CabinType = npchar.quest.FDM_cabin.type;
			if (CheckAttribute(npchar, "quest.FDM_sails")) npchar.quest.FDM_full = "done";
			else DeleteAttribute(npchar, "quest.FDM_full");
			npchar.quest.FDM_cabin = "done";
		break;
		
		case "FDM_sails":
			dialog.text = "ああ、できるぜ！さてさて……つまり、汚れたボロ布は全部捨てて、綿でできた新しくてきれいな帆を張らなきゃならねえってことだな。 ここはやることが山ほどあるぜ。作業と材料で十万ペソだ。どうする？";
			if (sti(Pchar.money) >= 100000)
			{
				link.l1 = "ああ、それで構わねえぜ。取引成立だ！";
				link.l1.go = "FDM_sails_do";
			}
			link.l2 = "ふむ。考えないといけないな…";
			link.l2.go = "exit";
		break;
		
		case "FDM_sails_do":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "よし。金は受け取った、仕事に取りかかるぜ。終わるまでぶらぶらしててくれ、心配はいらねえ。";
			link.l1 = "「よし…」";
			link.l1.go = "FDM_sails_done";
		break;
		
		case "FDM_sails_done":
			DialogExit();
			SetLaunchFrameFormParam("Two days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//белый хлопковый парус
			npchar.quest.FDM_sails = "true";
			if (CheckAttribute(npchar, "quest.FDM_cabin")) npchar.quest.FDM_full = "done";
		break;
		//--> Xenon
		case "FDM_hull":
			dialog.text = "ようやくその話が聞けて嬉しいよ。確かに、あんたはなかなかの人物みたいだが、 どんな船に乗ってるのかさっぱり分からねえ。だが最初に言っとくが、この仕事は数時間で終わるもんじゃねえし、 かなり金もかかるぜ。 ";
			link.l1 = "わかった、もう少し詳しく教えてくれないか？";
			link.l1.go = "FDM_hull_01";
		break;

		case "FDM_hull_01":
			dialog.text = "よし、計算してみよう……船体を完全に再建するには、バカウト材、ロープ、船用シルク、樹脂がそれぞれ150ユニットずつ必要だ――それと金貨1万ドゥブロンだ。\nそんな目で見るなよ；ほとんどの金は材料費に消えるんだ。この仕事は船を解体して一から作り直すのと同じなんだぜ。";
			link.l1 = "いや、そうは思わねえな。そんなに多くの資材を持ち込んで、再建のために山ほどの金貨を渡す気はねえ。 今あるものでやっていくぜ。";
			link.l1.go = "FDM_hull_thinking";
			link.l2 = "ああ、俺たちの船のためなら何だってやるさ……よし、取引成立だ。";
			link.l2.go = "FDM_hull_02";
		break;

		case "FDM_hull_02":
			dialog.text = "よし、無駄話はやめて行動だ。必要な物を買い揃えるために、まずはあんたから金をもらうのを待ってるぜ。 金が用意できたら、材料を持ってきてくれ。そしたら、あんたの船に取りかかるからな。";
			if(PCharDublonsTotal() >= 10000)
			{
    			link.l1 = "金なら問題ねえ。ちゃんと持ってきたぜ。ほらよ、親方。";
    			link.l1.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "今はそんな金は持ってねえ。少し待ってくれ、すぐに持ってくるからよ。";
    			link.l1.go = "FDM_hull_waitmoney";
            }
		break;

		case "FDM_hull_waitmaterials":
			RemoveDublonsFromPCharTotal(10000);
			npchar.quest.FDMsandal = 0;
			npchar.quest.FDMoil = 0;
			npchar.quest.FDMshipsilk = 0;
			npchar.quest.FDMropes = 0;
			AddQuestRecord("renovate_fdm", "1");

			npchar.quest.FDM_hull = "hull_waitmaterials";
			dialog.text = "そんな大金を持って海賊の集落を歩き回るのが怖くねえのか、へへ？まあ、冗談だよ、 ここにいる連中はそれぞれのやり方で真面目な奴らさ。さて、今は資材を待ってるところだ。念のために言っておくが、 全部で鉄木150、ロープ150巻、船用シルク150反、樹脂150樽を持ってきてもらう必要があるぜ。\n";
			link.l1 = "頑張ってくれ、材料を持ってくるからな。";
			link.l1.go = "exit";
		break;

		case "FDM_hull_checkmaterials":
			dialog.text = "上出来だ！今日は何を持ってきたんだ？";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && sti(npchar.quest.FDMsandal) < 150)
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "鉄材（アイアンウッド）を "+FindRussianQtyString(iSan)+".";
				link.l1.go = "FDM_sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && sti(npchar.quest.FDMoil) < 150)
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "樹脂、数量 "+FindRussianQtyString(iOil)+".";
				link.l2.go = "FDM_oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && sti(npchar.quest.FDMshipsilk) < 150)
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "絹を次の数量で積み込め "+FindRussianQtyString(iSil)+".";
				link.l3.go = "FDM_shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && sti(npchar.quest.FDMropes) < 150)
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "「本数分のロープ」 "+FindRussianQtyString(iRop)+".";
				link.l4.go = "FDM_ropes";
			} 
			link.l5 = "まだ何もない。ただ、取引がまだ有効か確認したかっただけだ。";
			link.l5.go = "exit";
		break;

		case "FDM_hull_checkmaterials_1":
			if (sti(npchar.quest.FDMsandal) > 149 && sti(npchar.quest.FDMoil) > 149 && sti(npchar.quest.FDMshipsilk) > 149 && sti(npchar.quest.FDMropes) > 149)
			{
				dialog.text = "素晴らしい！材料はすべて揃っているな。さて、その化け物は俺に任せてくれ。ようやく本来の姿にしてやれるぜ。";
				link.l1 = "わかった、もう文句はやめてくれ、親方。結果を楽しみにしてるぜ。";
				link.l1.go = "FDM_hull_building";
			}
			else
			{
				dialog.text = "俺の一日を明るくしてくれるような話は他にないのか、船長？";
				link.l1 = "残念だが、今はこれで全部だ。";
				link.l1.go = "exit";
				link.l2 = "ああ、他にも頼みたいことがあるんだ……";
				link.l2.go = "FDM_hull_checkmaterials";
			}
		break;

		case "FDM_sandal": // бакаут
			amount = 150 - sti(npchar.quest.FDMsandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) 
			{
				dialog.text = "そうだな……俺が必要なのは "+FindRussianQtyString(amount)+" 鉄木製だ。お前が持ってきた "+FindRussianQtyString(iSan)+"鉄木だ。だから、まだ俺に持ってきてもらわなきゃならねえ\n "+FindRussianQtyString(iTemp)+".";
				link.l1 = "ありがとう！残りはすぐに渡すぜ。";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + iSan;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "さてと……まだ必要なのは "+FindRussianQtyString(amount)+" 鉄の木材か。お前が持ってきたのか  "+FindRussianQtyString(iSan)+"。だから、これで鉄木の仕事は終わりだ！";
				link.l1 = "ありがとう！";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood"); 
			}
		break;

		case "FDM_oil": // смолы
			amount = 150 - sti(npchar.quest.FDMoil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) 
			{
				dialog.text = "さて……俺が必要なのは "+FindRussianQtyString(amount)+" 樹脂を持ってきた "+FindRussianQtyString(iOil)+"。だから、まだ俺に持ってきてもらわなきゃならねえ "+FindRussianQtyString(iTemp)+".";
				link.l1 = "ありがとう！残りはすぐに渡すぜ。";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				npchar.quest.FDMoil = sti(npchar.quest.FDMoil) + iOil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "さてと……まだ必要なのは "+FindRussianQtyString(amount)+" 樹脂を持ってきてくれた "+FindRussianQtyString(iOil)+"。だから、樹脂の作業はこれで終わりだ！";
				link.l1 = "ありがとう！";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.FDMoil = makeint(npchar.quest.FDMoil) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
			}
		break;

		case "FDM_shipsilk": // шёлк
			amount = 150 - sti(npchar.quest.FDMshipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) 
			{
				dialog.text = "さて……俺が必要なのは "+FindRussianQtyString(amount)+" 船の絹の分だ。持ってきた "+FindRussianQtyString(iSil)+"。したがって、まだ俺に持ってきてもらう必要がある "+FindRussianQtyString(iTemp)+".";
				link.l1 = "ありがとう！残りはすぐに持ってくるぜ";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + iSil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "さて……まだ必要なのは "+FindRussianQtyString(amount)+" 船用の絹だ。だから、まだ俺に持ってきてもらわなきゃならねえ "+FindRussianQtyString(iSil)+"。したがって、これで船の絹は終わりだ";
				link.l1 = "ありがとう！";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk"); 
			}
		break;

		case "FDM_ropes": // канаты
			amount = 150 - sti(npchar.quest.FDMropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) 
			{
				dialog.text = "そうだな……俺が必要なのは "+FindRussianQtyString(amount)+" ロープのことだ。持ってきた "+FindRussianQtyString(iRop)+"。だから、まだ俺に持ってきてもらわなきゃならねえ\n "+FindRussianQtyString(iTemp)+".";
				link.l1 = "ありがとう！残りはすぐに渡すぜ";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + iRop;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "そうだな……俺が必要なのは  "+FindRussianQtyString(amount)+" ロープだ。持ってきた "+FindRussianQtyString(iRop)+"。だから、これでロープの仕事は終わりだ！";
				link.l1 = "ありがとう！";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
			}
		break;

		case "FDM_hull_thinking":
			DialogExit();
			npchar.quest.FDM_secondtime = true;
		break;

		case "FDM_hull_waitmoney":
			DialogExit();
			npchar.quest.FDM_hull = "hull_waitmoney";
		break;

		case "FDM_hull_givemoney":
			dialog.text = "さて、金は持ってきたのか";
			if(PCharDublonsTotal() >= 10000)
			{
    			link.l2 = "ああ、持ってきたぜ。約束通り、重さの揃ったドゥブロン金貨一万枚だ。";
    			link.l2.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "まだだ、待ってくれ、旦那。";
    			link.l1.go = "exit";
            }
		break;

		case "FDM_hull_building":
			DialogExit();
			SetLaunchFrameFormParam("Five days passed..."+ NewStr() +"Master Alexus completed the job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //Pass time
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			
			shTo = &RealShips[sti(pchar.Ship.Type)];
			object newShip;
			aref arTuning;
			CopyAttributes(&newShip, shTo);
			
			pchar.Ship.Type = GenerateShipExt(SHIP_RENOVATED_FDM, 0, pchar);
			
			if(CheckAttribute(newShip, "Tuning"))
			{
				makearef(arTuning, newShip.tuning);
				for (int iQty = 0; iQty < GetAttributesNum(arTuning); iQty++)
				{
					aref realTuning = GetAttributeN(arTuning, iQty);
					string tuningName = GetAttributeName(realTuning);
					UpgradeShipParameter(pchar, tuningName);
				}
			}
			if(CheckAttribute(newShip, "Traits")) RealShips[sti(pchar.Ship.Type)].Traits = newShip.Traits;
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//White cotton sail
			pchar.ship.hp = GetCharacterShipMaxHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");	
			CloseQuestHeader("renovate_fdm");
			Achievment_Set("ach_CL_178");
		break;
		//<-- Xenon
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
