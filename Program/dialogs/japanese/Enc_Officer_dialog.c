// BOAL новый диалог офицера и компаньона 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    	sld, rItm, rItem;
	string 	attr, attrLoc, sGun, sBullet, attrL, sAttr;
	int    	iTemp, iTax, iFortValue, i;
	aref 	rType;
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("へっ、船長、今や守備隊の半分がお前を追ってるぜ。今はお前の船に雇われるには最悪のタイミングじゃねえか！","船まで戦い抜くって？いや、船長、また今度にしよう……");
				link.l1 = RandPhraseSimple("ご希望のままに……","実は、お前を雇うつもりはなかったんだ。"); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "「船長、士官が必要ですか？」";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "士官だと？で、お前は何が得意なんだ？";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "いや、俺は全部そろってるぜ。";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "船長、何をしているんだ？面倒を起こす前に武器をしまってくれ！";
			link.l1 = LinkRandPhrase("「いいだろう。」","「いいだろう。」","心配するな、しまっておくからな……");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "今日はついに出航だ！";
				link.l2 = "ああ……嬉しいぜ。";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "俺はちょっと飲み終えてから行くぜ、船長。それから船に向かう。心配すんな――ちゃんと時間通りに行くからよ。";
				Link.l1 = "よし。遅れたら甲板掃除をさせるからな！";
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = "何の用だ、船長？";
			// эпилог -->
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers") && npchar.id == "Folke")
			{
				dialog.text = "この天気は気に入らねぇな、船長。嵐の前兆を見つけたぜ。";
				Link.l1 = ""+npchar.name+"、話がある。率直に言うと、俺はヨーロッパへ行く。戻る時期は未定だ。お前をここに残して待たせるのは馬鹿げてるが、全員を連れて行くわけにもいかない。他人の船に客として乗るんだ。";
				Link.l1.go = "SharlieEpilog_Folke_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers") && npchar.id == "Duran")
			{
				dialog.text = "（あくび）退屈だな…";
				Link.l1 = "しばらく気晴らししてなかったな、"+npchar.name+"？";
				Link.l1.go = "SharlieEpilog_Duran_1";
				break;
			}
			// эпилог <--
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "お前にいくつか命令を出さなきゃならねえ。";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			// на Тайясаль
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l66 = ""+npchar.name+"、俺は古代インディアンの町タイアサルへ行くつもりだ。これは危険で普通じゃない旅になる――テレポーテーションの偶像を通ってな。お前も一緒に来るか？";
				if(npchar.id == "Folke")
				{
					Link.l66 = ""+npchar.name+"、お前に重大な頼みがあるんだ――本気の話だぜ、命知らずだがとんでもなく儲かる。古代インディアンの都市への探索に忠実な奴が必要なんだ。お前、 乗るか？";
				}
				if(npchar.id == "Duran")
				{
					Link.l66 = "クロード、お前は以前、傭兵の給料が安すぎると文句を言っていたな。";
				}
				Link.l66.go = "tieyasal";
			}
			
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
				Link.l2 = "今から俺の命令を聞け！";
				Link.l2.go = "stay_follow";
			}

           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "「船についての詳細な報告をしてくれ。」 "+GetStrSmallRegister(XI_ConvertString("財務官"))+".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "植民地に滞在している間に商品を仕入れてきてほしいんだ。";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "なあ、もう植民地で商品を買う必要はねえんだぜ。";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (pchar.location != "My_Campus") // patch-5
			{
			Link.l4 = "士官、もうお前の助力は必要ない。";
			Link.l4.go = "AsYouWish";
			}
			
			
			// по тек локации определим можно ли тут приказать  -->
			if(IsEntity(&loadedLocation))
			{
				if(CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if(iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if(sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = "この町の代理に任命する！";
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
			Link.l9 = "何もない。気を抜いていいぞ！";
			Link.l9.go = "Exit";
		break;
		
		// Тайясаль
		case "tieyasal":
			if(npchar.id == "Folke")
			{
				dialog.text = "ちくしょう、船長！最初のチャンスで俺を追い出すと思ってたが、やっぱりお前は俺の予想を裏切るな。 もちろん俺はお前と一緒だぜ。それに、このバカに本物の海の狼の人生を味あわせてくれて感謝してる！";
				Link.l1 = "「よくやった」 "+npchar.name+"!";
				Link.l1.go = "folke_tieyasal";
				break;
			}
			if(npchar.id == "Duran")
			{
				dialog.text = "え？俺が本当にそんなこと言ったか？";
				Link.l1 = "君はやった。あの時、俺はちゃんと話を聞いたぜ、だから今こそ不正を正す覚悟ができてるんだ。";
				Link.l1.go = "Duran_tieyasal";
				break;
			}
			dialog.text = LinkRandPhrase("悪いな、船長。でも俺が契約したのはこんなことじゃねえ。俺を臆病者だと思わないでくれよ、 だが確実な死に向かうつもりはねえんだ。まだ生きるのに飽きちゃいねえからな。 気に入らなきゃクビにしてくれてもいいぜ。","船長、申し訳ありませんが……いやです。海や白兵戦、敵の街なら問題ありませんが、あのインディアンの呪術には関わりたくありません。\n私の返答にご不満なら、契約を破棄していただいて構いません。","無理なことを望んでるな、船長。自分でもわかってるだろう。誰も生きては戻れねえ、あんたもな。 だから俺は遠慮しとくぜ。俺の拒否が契約違反だと思うなら、契約を破棄しても構わねえよ。");
			link.l1 = LinkRandPhrase("責めてはいませんよ、役人殿。よく分かっています。","残念だが、君の気持ちは分かる。だからこそ、事前に話しておいたんだ。","お前に期待していたんだが……まあ、お前の立場も分かるぞ、士官。");
			link.l1.go = "tieyasal_1";
		break;
		
		case "Duran_tieyasal":
			dialog.text = "へっ！じゃあ、俺の給料を上げてくれるのか？";
			Link.l1 = "ありえねえ！俺はこれから古代インディアンの都市に向かうんだ。命知らずの仕事だが、そこには金があるはずだ……";
			Link.l1.go = "Duran_tieyasal_2";
		break;
		
		case "Duran_tieyasal_2":
			dialog.text = "俺は金なんか興味ねえよ。昔助けてくれたあんたに恩返しできるなら光栄だぜ、船長。いつ出発するんだ？";
			Link.l1 = "よく言ったぞ、クロード！しっかり準備しておけ――もうすぐだ。";
			Link.l1.go = "Duran_tieyasal_3";
		break;
		
		case "Duran_tieyasal_3":
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "folke_tieyasal":
			Achievment_Set("ach_CL_108");
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.Tieyasal = "true";
		break;
		
		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "船長、どんな積み荷だって？まずは自分たちの船を見つけなきゃならねえだろう！";
				Link.l1 = "ああ、その通りだ。";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "やっておきます。 "+GetSexPhrase("旦那","お嬢さん")+" 船長！";
			Link.l1 = "楽にしてくれ。";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "やってみせます。 "+GetSexPhrase("旦那","お嬢さん")+" 船長！";
			Link.l1 = "楽にしてくれ。";
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;
        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			if(CheckAttribute(pchar,"systeminfo.tutorial.Fighter") && Npchar.quest.officertype == "fighter")
			{
				DeleteAttribute(pchar,"systeminfo.tutorial.Fighter");
				LaunchTutorial("Fighter", 1);
			}
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
			{
				SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
				pchar.questTemp.SKD_SobytieKlodDuran = true;
			}
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("船長、あの、俺…その、お願いがあるんだ。俺を解放してもらえないか。そろそろ落ち着いて、結婚して、子どもも欲しいんだ。 まだ自分の家もないし、年を取ったら水一杯持ってきてくれる人もいないからさ。","船長、どうか、私を辞めさせてください。\n長年世界中をさまよってきましたが、本当の意味で何も見ていない気がします。\n新しい人生を送りたいのです。錨を下ろし、違った視点で世界を見てみたいのです。","船長、海軍勤めも確かに素晴らしいもので、儲けも冒険もあるが、そろそろ自分のことを考える時が来たんだ。\nほら、静かな港に錨を下ろして、家を買って、子どもを持つってやつさ。\nお願いだ、俺を行かせてくれ。"),LinkRandPhrase("船長、あのな、本当に申し訳ねえんだが、もうこの任務や見張りや規律にはうんざりなんだよ。分かるだろ、 俺はただしばらく自由に生きてみたいだけなんだ。でも、船長が俺を待ってくれるわけじゃねえって分かってるからさ……だから、俺を下船させてくれねえか？","船長、あのさ……俺でも手が届く小さな船があってさ、だから……そろそろ自分の商売を始める時だと思うんだ。どうか、俺を行かせてくれないか？","船長、ちょうど港で職を勧められました。実は、ずっと前から錨を下ろして結婚生活に落ち着きたいと願っていたんです。 どうか、行かせてください。こんな機会、絶対に逃せません。"),LinkRandPhrase("船長、俺は本当に船酔いがひどいんだ。医者たちはいつも「体質だ」と言うばかりさ。頼む、神に誓って、 俺を下ろしてくれよ。じゃないと、そのうち自分から海に飛び込んじまうぞ。","船長、そろそろ落ち着いて静かな場所を見つけたいと思います。\nご存知の通り、私は怖いんです。流れ弾が怖いし、斬り込みの最中に死ぬのも怖い。主よ、 私を生かしてくださいと祈っていますが、目を閉じると、これまで殺した罪なき魂たちが見えるんです。\n彼らは私に命乞いをしている……どうか、情けをかけて、私を行かせてください。","船長、昔の傷がうずいてるんだ。それに最近の打撲も毎日痛みを思い出させる。\nもうすぐ俺を解雇するんだろ？その後、誰が俺なんか雇ってくれるんだ？頼む、行かせてくれ、自分で手当てして、 もっと静かな場所を探すよ。"));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("みんな結局は去っていくものさ。\nよし、好きにしな。","あなたの考えは理解できる。遅かれ早かれ、すべてのものには終わりが来るものだ。\nさあ、行くがいい……もし俺が何か気に障ることをしたなら、恨みは持たないでくれよ。","またこれか？わざわざ一番都合の悪い時に俺を置いていくつもりだな、そうじゃねえか？\nまあいい。じゃあな。"),LinkRandPhrase("お前の言うことは信じがたいが……いいだろう、荷物をまとめて出ていけ。","お前か？こんなことになるとは思わなかったぜ……長い間、背中合わせで戦ってきたのにな。まあ、止めやしねえ。幸運を祈るぜ。","真剣な声だな。まあ、幸運を祈るぜ。それに、俺はお前がいなくなるのが寂しいぜ。"));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("なるほど……そういうことかい？俺はお前を頼りにしてたんだがな……まあ、もう決めたってんなら、ここでお別れだ。持っていけ\n "+sti(NPChar.rank)*250+" 忠実な働きへのペソだ。もし私がこれまでに気を悪くさせたなら、どうか恨まないでくれ。","さて、俺は恨みもないし、悪意も覚えていない。お前がそう決めたんなら、行け。そいつも連れて行け "+sti(NPChar.rank)*250+" 新たな出発のためのペソなら、きっと役に立つぜ。","なるほど……まあ、遅かれ早かれそうなる運命だったんだろうな。俺が渡すのは "+sti(NPChar.rank)*250+" お前の命のためのペソだ。それに、体にも気をつけろよ、海軍勤務は苦労が多いからな……"); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("そう言うのか……今ここで去れば、俺の背中に刃を突き立てることになるってわかってねえのか？今はお前を行かせるわけにはいかねえ、 考えるなよ。","それは驚きだな！こういうことは事前に俺に知らせるもんだぜ！だから、しばらくは自分の私生活のことは忘れろ。 時が来たら、引退のタイミングは俺が教えてやるからな。","辞職者はいない。全員の所在は把握している。個人の希望だけで全員を自由にするわけにはいかん。 休暇に値するかどうか、俺が考える間は働け。");	
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "ありがとうございます、船長！こんな思いがけないご厚意を……。そういえば、まだあなたの持ち物がいくつか残っているんだが、返してほしいかい？";
			Link.l1 = "もしかして……最近はいい剣を見つけるのも簡単じゃねえな。";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "「ああ、気にしなくていい。君の働きの記念として取っておきな。」";
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("「でもどうしてですか、船長？奴隷でさえ最終的には陸に上がるんですよ。それに俺は奴隷じゃない、 自分の運命は自分で決めるさ！」","船長、これまでずっと忠実にお仕えしてきました。自分の運命くらい、 自分で決める権利があってもいいんじゃありませんか？");
			Link.l1 = LinkRandPhrase("このままでは君を引き止めておけないようだな。\nよし、金銭的な支援はどうだ？損はしないぜ。静かな港で快適な家を建てるもよし、健康のために使うもよしだ。","よし、こうしよう。どれくらいの金額なら考え直してくれるんだ？","おっしゃる通りだ。しかし、一度きりの金銭的手当を出せば、考えが変わるか？");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(RandPhraseSimple("ああ、違うぞ、友よ、そこは勘違いしてる……お前が酒場で女を追いかけて時間を無駄にしていた間は自分で決められただろうが、俺の船に乗り込んだ瞬間から、 お前の運命は俺の手の中だ。","ふん。そりゃあ大した口ぶりだな。どうやら、お前が臭え酒場で一文無しだったところを俺が見つけてやったこと、 もう忘れちまったらしいな。金貨一枚見せても無駄だぜ、どうせすぐラム酒に変えちまうんだからよ。 「俺の運命を決めろ…」だと？　ぷっ！笑わせるなよ！"),LinkRandPhrase("お前が私の下で働いている間は、決定を下すのは私だ。\nさあ、これ以上私を怒らせる前に持ち場へ戻ってくれ！","ふむ。そりゃあ重大な発言だな。だが、前払いした金はまだ全部働きで返してもらっちゃいねえぜ。つまり、 その行動は恐喝の試みと見なせるんじゃねえか？","ああ、なるほど……船の規則には何て書いてあったっけ？ほら、第2条だ。「許可なく脱走を試みた者は、火薬一袋、水筒一つ、ピストル一丁、 弾丸一発だけを持たされて無人の岸に置き去りにされるものとする。」さて、お前はどうされたいんだ？"));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("さて、それはまた別の話だな。 "+sti(NPChar.rank)*500+" 「ペソを即金で払ってくれりゃ、あんたと一緒にいるぜ。」","さて、もしかすると "+sti(NPChar.rank)*500+" ペソがあれば、たぶんここにいられるだろうな。","そう言われると、 "+sti(NPChar.rank)*500+" ペソがあれば、俺の奉公を続けられるんだ。");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("わかった、承知した。","わかった。だが、もう少し安く頼んでもよかったんじゃねえか。","なかなか食欲があるじゃねえか！だが、俺は約束しただろう？ちゃんと守るぜ。");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("それは高すぎるな。その値段なら士官を二人雇えるぜ。お前を解放した方が手っ取り早いかもな。","ほう、自分のことをずいぶん高く評価してるんだな。よし、行かせてやるよ。\nだがな、自由の身になったら、自分の人生が思ったほど順風満帆じゃねえってことを、身をもって知ることになるぜ。","そんな大金は払わねえ。行きたきゃ行け、だが二度と戻ってくるんじゃねえぞ。裏切りは絶対に許さねえ。");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "わかった、そう言うなら俺は残るぜ。だが、こうするのは俺の本意じゃねえってことは覚えておけよ。";
		Link.l1 = LinkRandPhrase("よろしい。持ち場に戻れ、そしてこの話は後で続けよう。","船に戻れ。次からは、引退を頼む前によく考えるんだな。","確かに。義務は義務だ、まだ妄想にふけっている場合じゃないぞ。");
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		if(NPChar.id == "Duran") NPChar.greeting = "Duran_officer";
		ChangeCharacterComplexReputation(pchar,"authority", 0.2);
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
		NPChar.location = "none";
		LAi_SetOfficerType(NPChar);
	break;
	
	case "WantToGo_free":
		//navy -->
		if (CheckAttribute(NPChar, "PGGAi"))
		{	
			pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("PGG_FireOfficer");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();	
			break;
		}
		//navy <--
		Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
	break;
	
	case "WantToGo_free_Yet":
		Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase("信じられない！ありがとうございます、船長、おかげで心の重荷が取れました。","ありがとう、船長、俺を引き止めようとしなかったことに感謝するぜ。実はな、人生で他にもいろいろ試してみたいんだ。 ","へっ、これからは新たな自由に慣れなきゃならねえな。今になってやっと、 あの艦隊勤務にどれだけうんざりしてたか思い知ったぜ。");	
		Link.l1 = RandPhraseSimple("じゃあ、幸運を祈るぜ。","お前はもう自由だ。お前の務めは終わった。");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 офицер хочет свалить <--
		
	// пассажир возмущен игроком и сваливает -->
	case "WantToRemove":
		if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
		{
			SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
			pchar.questTemp.SKD_SobytieKlodDuran = true;
		}
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("船長、俺は自分の良心に背いてまで略奪に加わりたくねえんだ。","船長、俺はもうあんたの乱暴には加わりたくねえ。俺は士官であって、殺し屋じゃねえんだ。","船長、あんたの無法者みたいなやり方じゃ、俺はこの船にいられねえよ。"),LinkRandPhrase("船長、正直に申し上げますが、あなたのもとで働いたのは失望の一言に尽きます。どんな大金を積まれても、 私は自分の評判を犠牲にするつもりはありません。","船長、あんたは新世界で最も悪名高い人斬りどもを自分の船に集めちまったな。 まともな人間には見るだけでも吐き気がする連中だ。こんな奴らとこれ以上一緒に働くのはごめんだぜ。","船長、あんたはろくでなしばかりの船員を雇ったな、まともに話せる奴が一人もいねえ。こんな仕事、俺は大嫌いだぜ。"))+" さらば。";
			Link.l1 = "「なんだと！？ここは軍艦だ、花嫁学校じゃねえぞ！だったら地獄にでも行きやがれ！」";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "お前がすぐに去ると分かっていた……この務めはお前向きじゃねえからな。だが、俺を責めるんじゃねえぞ。ほら、ここにある "+sti(NPChar.rank)*500+" ペソだ、お前が気に入る仕事を探している間に役立つだろう。";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("「ほう、今はそんな口ぶりかよ。じゃあ、これまでの強奪で手にした分け前はどうした？手が焼けるってか？それとも、 罪の許しを祈るために修道院に引っ込むつもりか？そのときは俺たちの分も頼むぜ！ハハハハハ！」","ふむ。そりゃあ大層なご意見だな。俺たちが一緒に商船を襲ってた時、お前の清らかな良心はどこを見てたんだ？ どうやってその良心をきれいにするつもりだ？それとも、俺たちをチクって、立派な連中と一緒に絞首台に送るつもりか？ ","おお、見事だな！どうやら俺があんたを見つけた時のことを忘れちまったらしいな、 臭え酒場でポケットに一文無しだったくせに。ちなみに言っとくが、 士官としてのあんたは真鍮のファージングの価値もねえ。役立たずだ！");
			Link.l3.go = "WantToGo_stop";
		}
		else
		{
            dialog.text = RandPhraseSimple(LinkRandPhrase("船長、あんたの貴族の遊びには本当にうんざりだぜ。俺は自分のやり方を変えるつもりはねえし、 あんたの安心のために習慣を捨てる気もねえ。じゃあな。","船長、もうあなたの下で働くことはできません。私はすでに多くの時間を無駄にしてしまいました。 普通の私掠船乗りでさえ、もう大金を手にしていたでしょう。私はここを去ります。","船長、あんたの部下にはうんざりだ。まともな奴は一人もいねえ、気取った野郎ばかりで、一緒に酒を飲む価値もねえ。 俺は出ていくぜ。"),LinkRandPhrase("船長、俺はベテランの士官だが、あんたの船はまるで貨物船みたいだな。そんな任務はごめんだ。じゃあな。","船長、あんたの船員どもはみんな気取った野郎ばかりで、飲み相手も話し相手もいねえじゃねえか。 そんな連中の世話になるのは大嫌いだ。じゃあな。","船長、俺は本物のコルセアの下で働いてると思ってたが、俺たちがやってるのは慈善事業ばかりじゃねえか！ こんなことで時間を無駄にしたくねえ。俺はもう出ていくぜ。"));
			Link.l1 = RandPhraseSimple("なるほど。お前の態度じゃ、遅かれ早かれそうなる運命だったんだろうな。よし、もう引き止めはしねえ。","お前の発言は予想通りだった。正直なところ、俺はずっと前からお前の態度に不満を感じていたんだ。")+" 幸運を祈るぜ。";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "お前がすぐに去ると分かっていた……この務めはお前には向いていない。しかし俺を何も責めるな。ここにあるのは "+sti(NPChar.rank)*500+" ペソだ、次の仕事を探している間に役立つだろう。";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("ふむ。これは重大な発言だな。だが、前払いした金の分はまだ働ききってねえだろう。つまり、 その行動は恐喝の試みと見なせるんじゃねえか？","ああ、なるほど……船の規則には何と書いてある？ほら、第2条だ。「許可なく脱走を試みた者は、火薬一袋、水筒一つ、ピストル一丁、弾丸一発だけを持たされ、 無人の岸に置き去りにされるものとする。」さて、お前はそれでどうしたいんだ？");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("俺を侮辱しようなんて思うなよ！俺は金のために働いてるが、 それでも自分が気に入った仕事を選ぶ権利くらいあるんだぜ！","俺は自由な男だ！そして、好きなときに新しい仕事を選ぶ権利があるんだぜ！","俺は食い扶持のために働く奴隷じゃねえから、良心は咎めねえ！だが、もう盗賊行為には加担しねえぜ！");
				Link.l1 = "実はな、お前は勘違いしてるぜ……酒場で飲んでる間は好きな仕事を選べたかもしれねえが……一度俺の船に乗り込んじまったら、帰る道は首を砕く砲弾だけだ……それに舌も引き抜いてやるよ、あの世で余計なことを喋らせねえためにな……";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "よし、行っていいぜ……だが、神に誓って、もし大海原で俺と出くわしたら、その時は後悔することになるからな。 俺のそばに残らなかったことを、きっと悔やむぜ。";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("俺を脅そうなんて思うなよ！俺は金のために働いてるが、それでも自分の好きな仕事を選ぶ権利はあるんだぜ！","俺は自由な男だ！そして、好きな時に新しい仕事を選ぶ権利があるんだぜ！","俺はあんたの奴隷じゃねえ！それに、あんたのボロ船でみじめな人生を送り続けるつもりもねえぞ！");
				Link.l1 = "実はな、お前は勘違いしてるぜ……酒場で飲んでる間は好きな仕事を選べたかもしれねえが……一度俺の船に乗り込んじまったら、帰る道は首を砕く砲弾だけだ……それに舌も引き抜いてやる、あの世で余計なことを喋らせねえためにな……\n";
				// belamour legendary edition можно запугать офицера -->
				//if (makeint(Pchar.Rank) > makeint(NPchar.Rank) || CheckCharacterPerk(pchar, "IronWill"))
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "よし、行っていいぜ……だがな、もし大海原で俺に出くわしたら神に祈るんだな。誓ってやる、俺のそばに残らなかったことを必ず後悔するぜ。";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("そう言われたら、俺はここに残るしかねえ。他に選択肢はないんだ。だが、 これは俺の本意じゃないってことを覚えておけよ……","わかった、そう言うなら俺は残るぜ。だが、そうすることで自分の意志に反するってことは覚えておけよ。");
			Link.l1 = RandPhraseSimple("それでいい……俺が許すまで仕えるんだ。","それでいい。引き続き仕えろ……俺が解放する時は俺が決める。");
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar,"俺に考え直せなんて絶対に言わせねえ！俺を奴隷みたいに縛る権利なんてお前にはねえ！俺は出ていくからな、近づくな、 さもないと終わりだぞ。","ベテラン将校を脅せると思ってるのか！？俺は何度も死の淵をくぐり抜けてきたんだ。そう言うなら、 公正な戦いで死ぬ方が、血まみれの略奪の最中に死ぬよりずっとましだぜ！");
			Link.l1 = NPCharRepPhrase(NPChar,"そうか……人は皆、自分の運命を選ぶもんだ。俺のところに来る前に、ちゃんと祈りは済ませてきたんだろうな。","酒場でお前を拾ったときにこんなことになると知ってたら、絞首台で吊るされるままにしておいたぜ。\n今からでも手配できるんだがな……");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar,"まあ、そんなに自由が欲しいなら出て行けばいいさ。だが、俺から推薦状はやらねえぞ。","よし、行っていいぜ……だがな、もし大海原で俺と出くわしたら、神に祈るんだな。お前が俺のそばに残らなかったことを、 必ず後悔させてやるぜ。");
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			dialog.text = NPCharRepPhrase(NPChar,"もう俺を脅すのはやめろよ！お前の手下の中で、俺に立ち向かえる奴がいるのか？もし俺が船長だったら、 今ごろあいつらは金でウハウハだぜ！それに、お前があれだけ施しをしてきたのに、 乗組員が俺の味方につくのを恐れてるのか！？","そんな手はやめろ、俺はびびらねえ！さらばだ。");
			Link.l1 = NPCharRepPhrase(NPChar,"いいや、相棒、お前が絞首台まで生き延びることはねえ。そんな贅沢はお前には似合わねえんだよ…","待てよ、相棒、まだこれでチャラじゃねえぜ。お前は俺に借りがあるんだ。");
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";
			// belamour legendary edition в ближайшее время не подойдет от страха
			/* if(CheckCharacterPerk(pchar, "IronWill"))
			{
				Npchar.loyality = makeint(Npchar.loyality) + 3 + hrand(sti(GetSummonSkillFromNameToOld(pchar,SKILL_FORTUNE)+GetSummonSkillFromNameToOld(pchar,SKILL_LEADERSHIP)));
				log_info(GetFullName(Npchar)+" increased his loyalty");
				log_testinfo("Loyalty has become: " + Npchar.loyality + " of " + MAX_LOYALITY);
			}
			else
			{ */
				if (!CheckAttribute(pchar, "questTemp.MutinyOfficerIDX"))
				{
					pchar.questTemp.MutinyOfficerIDX = npchar.index;
					npchar.quest.Mutiny = true; // mitrokosta доп защита от багов
					SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
				}
			//}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущен игроком и сваливает <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar,RandSwear()+"俺が一番だ "+XI_ConvertString(Npchar.quest.officertype)+" この海域の中で。 "+Npchar.quest.officertype_2+"そして、俺はあんたに恩を売って、あんたの下で働く覚悟ができてるぜ。","「まあ、悪くないって言われてるぜ」 "+XI_ConvertString(Npchar.quest.officertype)+". "+Npchar.quest.officertype_2+"俺を船に乗せてくれよ、船長、自分の目で確かめてみな。");
			Link.l1 = "「それで、いくら欲しいんだ？」";
			Link.l1.go = "price";
			Link.l2 = "「で、お前はどんな専門家なんだ？」";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "あいにく、俺にはすでにいるんだ "+XI_ConvertString(Npchar.quest.officertype)+".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("へっ、船長、今は守備隊の半分がお前を追ってるぜ。今はお前の船に雇われるには最悪のタイミングじゃねえか！","船まで戦い抜くって？いや、船長、また今度にしようぜ……");
				link.l1 = RandPhraseSimple("ご希望のままに……","実は、お前を雇うつもりはなかったんだ。"); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "気が変わったのかい、船長？新しい "+XI_ConvertString(Npchar.quest.officertype)+" 「害はないだろう？」";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "そんなところだ。いくら欲しいんだ？";
                Link.l1.go = "price";
			}
			Link.l2 = "「お前は何ができるんだ？」";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "揃いは全部ある。じゃあな。";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "同意できると思う "+Npchar.quest.OfficerPrice+" ペソ。";
			if(Npchar.rank >= 15)
			{
				dialog.text = "同意できると思う "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" ドゥブロン金貨だ。";
			}	
			Link.l1 = "それはちょっとやりすぎじゃねえか？";
			Link.l1.go = "trade";
			Link.l2 = "同感だ。お前もこれで乗組員の一員だぜ。";
			Link.l2.go = "hire";
			Link.l3 = "お前にこの金はもったいねえな。";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = "よし…まあ、それでも俺は同意してやってもいいぜ "+Npchar.quest.OfficerPrice+" ペソだ。どうする？";
				if(Npchar.rank >= 15)
				{
					dialog.text = "俺としても、たとえ～でも同意してやってもいいぜ "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" ドゥブロン金貨だ。どうする？";
				}
				Link.l1 = "そいつはいいな。お前は仲間入りだ。";
				Link.l1.go = "hire";				
				Link.l2 = "俺はまだちょっと多すぎると思うぜ。じゃあな。";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "申し訳ありません、船長。でも私は自分が要求した額に見合う価値があるんです。それが高すぎるなら、 他を当たってください。";
				Link.l1 = "よし、わかった。連れて行ってやる。";
				Link.l1.go = "hire";				
				Link.l2 = "それをやるつもりだ。さらば。";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			dialog.text = "お金が足りないようだな、船長！悪いが、ツケでは仕事しねえんだ。";
			Link.l1 = "「ああ、くそっ！」";
			Link.l1.go = "Exit";
			if(Npchar.rank < 15 && makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "ありがとうございます、船長。あなたの選択を後悔することはありません。";
				Link.l1 = "そうだといいんだが。";
				Link.l1.go = "Exit_hire";								
			}
			if(Npchar.rank >= 15 && PCharDublonsTotal() >= makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)))
			{
				RemoveDublonsFromPCharTotal(makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "ありがとうございます、船長。あなたの選択を後悔することはありません。";
				Link.l1 = "そうだといいんだが。";
				Link.l1.go = "Exit_hire";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "俺はちょっと酒を飲み終えたら行くぜ、船長。それから船に向かう。心配すんな、ちゃんと時間通りに着くからよ。";
			Link.l1 = "よし。遅れたら甲板掃除をさせるからな！";
			Link.l1.go = "Exit";											
		break;
        
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "船長、でもあなたには船がないじゃないか！";
				Link.l1 = "思い出させてくれてありがとう……";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			// Rebbebion, добавил фикс отображения знака процента
			dialog.text = "航海中のネズミの活動が最大 "+FloatToString(50.0 /(2.0+GetSummonSkillFromNameToOld(PChar,SKILL_REPAIR)+GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)),1)+"全積荷量の%%。そのため "+GetCrewQuantity(PChar)+" 必要なのは水夫たちだ "+makeint((GetCrewQuantity(PChar)+6)/ 10)+" 1日あたりの食料。ただし、輸送中の奴隷は含まれていない。";
			Link.l1 = "ありがとう。";
			Link.l1.go = "Exit";
			Diag.TempNode = "Hired";
		break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "ご命令は何ですか？";
            Link.l1 = "「ここに立て！」";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "俺について来い、遅れるんじゃねえぞ！";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "目標から一定の距離を保ってほしい。";
				Link.l3.go = "TargetDistance";
			}
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l4 = "お前の火器の弾薬の種類を変える必要がある。";
					Link.l4.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l5 = "お前のマスケットの弾薬の種類を変える必要がある。";
					Link.l5.go = "SetMusketBullets";
				}
					Link.l6 = "戦闘用に主武器を変更する必要がある。";
					Link.l6.go = "SetPriorityMode";
			}
		break;

		case "SetGunBullets":
			Dialog.Text = "弾薬の種類を選択してください：";
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
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "弾薬の種類を選択してください：";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "戦闘開始時に使うのは：";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
            SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
		case "TargetDistance":
			dialog.text = "正確にはどの距離ですか、船長？歩数で指定してください。ただし20歩以内でお願いします。";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "船長、大丈夫ですか？";
				link.l1 = "申し訳ない、俺のミスだ……";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "俺はここでじっとしているぜ。それがあんたの望みか、船長？";
				link.l1 = "ああ。その通り、お前に求められているのはまさにそれだ。";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "俺は目標から二十歩以上離れることはできないって言ったはずだぜ。";
				link.l1 = "よし、20メートル離れていろ。";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "承知し、考慮した。";
			link.l1 = "「いいだろう。」";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "船長、正直申し上げてあなたの考えはよく分かりませんが、この話は陸でできませんか？それとも、 私をそのまま海に放り投げるおつもりですか？";
					Link.l1 = "ふむ……いや、そういう意味じゃねえ。港に着くまでここにいろ。";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("こりゃ新しいな！","なぜ、天国で？","理由は何だ！？"),RandPhraseSimple("船長、正気じゃねえのか？いきなりそんな話をするなんて！","おったまげたぜ！俺が何をしてお前さんの機嫌を損ねたんだ？"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("俺は乗組員に規律を持たせることにしたんだ。\nそれに、お前の仲間との関係は認めねえぞ。","雇用時に話し合ったほどの利点はなかったな。だから、","俺の船の乗組員に悪党やごろつきなんざ居座らせねえ！だからよ、"),LinkRandPhrase("お前がラム酒を盗み、こっそりと俺の船員たちに酒を飲ませて士気を下げていることがわかった。だから、","お前の無法者みたいな振る舞いにはもううんざりだ。これ以上は我慢しないぞ。だから、","お前はいつも中央キャビンでカードやサイコロに興じてばかりいて、他の士官たちの職務の邪魔をしている。 こんなことはいつまでも続けられん。だから、"))+" 荷物をまとめて船を降りろ。";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) >= 41) // герой против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("そのようなご決断の理由をお聞きしてもよろしいでしょうか？","明らかに、そのような決断は十分に考え抜かれている。"),RandPhraseSimple("説明しろ、船長","それはまったく予想外だな。しかし、理由はやっぱり知りたいんだ。"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("私はあなたの職務に対する態度に全く満足していない。","残念だが、お前は優秀な士官にはなれなかったし、これからもなれそうにねえな……","お前は優秀な士官で、働きぶりも悪くなかった。だが、ここで俺たちの道は分かれるんだ。理由は聞くな。"),LinkRandPhrase("俺は言っただろう、ラムへの執着が身を滅ぼすってな。剣すら鞘に戻せねえ奴を、戦いでどうやって信用しろってんだ？","お前はひどい水夫であり士官だな……海より陸で過ごす時間のほうが長くなりそうだぜ。","お前の能力には満足していないが、ようやくふさわしい後任を見つけたぞ。"));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("ふむ……理由をお聞きしてもよろしいですか？","それは重大なご発言ですね。特にどの点にご不満があるのかお聞かせ願えますか？"),RandPhraseSimple("説明しろ、船長。","明らかに、そのような主張には十分な根拠があるのか？"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("私はあなたの資格にまったく満足していない、だから","残念だが、お前はまともな士官とは認められなかった。だから、","お前の貴族ぶった態度にはもううんざりだ。いつまでも我慢してやるつもりはねえからな"),LinkRandPhrase("貴様が乗組員を扇動して反抗させていると耳に入った。俺の船で騒ぎは許さん！ これまで貴様を海に放り投げなかったことに感謝なんてするな。さて","あなたの高貴な信念は立派だが、それは自由な私掠船乗りの無法な生き方とは相容れない。だから","お前の職務に対する態度が気に入らねえ。だから"))+" 荷物をまとめて船を降りろ。";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) < 41) // злодей против злодея
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase("船長、まさかこんなことになるとは思わなかったぜ！\n一体何が起きてるのか説明してくれないか？","船長、どうしたんだ！？","それはどういう意味だ、船長！？"),RandPhraseSimple("なんだよ船長！？昨日までは全部順調だったのに、今はこんな有様じゃねえか、何があったんだ？","なんてこった！お前さん、自分のことを説明してくれねえか？"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("お前は本当に怠け者で役立たずの馬鹿だ。沿岸船の船員見習いでももっとマシにやるぜ。 俺はお前のせいでずっと苦しんできたんだ。だから\n","しばらく前からお前をクビにしようと考えてたんだが、ようやくまともな後任が見つかった。だから","お前がラム酒を盗み、こっそりと俺の船員たちに酒を飲ませて士気を下げていることがわかった。だから\n"),LinkRandPhrase("俺がお前を雇ったとき、お前は艦隊一の優秀な士官だと大口を叩いてたが、結局ただの怠け者じゃねえか、だから\n","お前の酒癖が悪い結末を迎えると警告しただろう。なぜ俺が役立たずの酔っ払いを船に置いておかねえといけねえんだ？ だから","仕える代わりに、あんたはいつもどこかにふらふら出かけたり、カードやサイコロで遊んだりしてばかりじゃねえか。 これがずっと続くと思ってたんじゃないだろうな？それでだ"))+" 荷物をまとめて船を降りろ。";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("なんだよ、その口の利き方は！いいだろう、好きにしな。だが覚えておけ、たとえ飢え死にしそうでも、 俺はもうお前のところには戻らねえからな！","正直言って、あんたの貴族の遊びにも興味はねえよ。じゃあな……","「ああ、くたばれ！お前の腰巾着どもと一緒にいろ。『英雄』だとよ、笑わせるぜ！」"),LinkRandPhrase("正直に言うと、あんたに仕えるのは最初から気に入らなかったんだよ……あんたの船はただの貨物船で、本物の船じゃねえ。まるでお嬢様学校みたいだぜ……","おい、あんたの船員どもにはもううんざりだぜ。みんな気取ったガキばかりで、本物の男なんて一人もいねえじゃねえか……","わかったぜ、船長、あんたの言う通りだ。だが神のみぞ知る、俺はちゃんと自分の仕事をやってきたんだよ……"));
			Link.l1 = "待ってくれ。今は士官なしで船を離れることはできねえ。だが、この話は後でまたしよう。";
			Link.l1.go = "exit_bad";
			Link.l2 = "それでは、安らかにお行きなさい。";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "熱くなるなよ。お前のために退職金を用意してあるんだ―― "+sti(NPChar.rank)*500+" ペソだ。これで全て解決することを願う。";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("失礼だな！「船を降りろ」ってどういう意味だ！？俺はぶどう弾の下で命を張ったんだぜ、 お前の気分次第で放り出されるためじゃねえ！","はっ！「船を降りろ」だと！？俺を子猫みたいに簡単に捨てられると本気で思ってるのか！？","落ち着けよ、船長、まともな奴らはこんなやり方で決着をつけたりしねえ。俺を新米扱いするんじゃねえぞ。");
			Link.l1 = "よし、今のところはいてもいい――だが、ちゃんとした代わりが見つかるまでだけだぞ。";
			Link.l1.go = "exit_bad";
			Link.l2 = "もう一度言う、お前の任務は終わりだ。荷物をまとめていいぞ。";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "熱くなるなよ。俺が用意した "+sti(NPChar.rank)*500+" お前にペソをやる。これで全て解決することを願ってるぜ。";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("実のところ、ここにとどまりたい気持ちはあまりないんだ。\nだが、見返りなしで立ち去るつもりもねえぞ！","今さらお前のあのボロ船には絶対に乗らねえが、まずはきっちり償ってもらうぜ！")+" "+sti(NPChar.rank)*1000+" ペソを払えば、お互いのことは忘れるってわけだ。";
			Link.l1 = "少し感情的になってしまった……どうか、私の謝罪を受け入れて職務に戻ってくれ。";
			Link.l1.go = "exit_bad1";
			Link.l2 = "お前はいつも分け前をちゃんともらってるだろ、どの金の話だ？これじゃまるでゆすりじゃねえか！";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "わかった。装備を返せば、頼んだものを渡してやる。";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "それはまた別の話だな。じゃあな！";
			Link.l1 = "できれば二度とお前と道が交わらないことを願うぜ。";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("これは精神的損害への賠償だと思いなさい。私はそのような扱いを決して許さないし、 私にそんなことをする者は必ず後悔するぞ！","これは恐喝じゃねえ、俺の貴重な時間を無駄にしたことへの当然の報いだ！どんな手を使っても、必ず取り立ててやるぜ！ ","俺はあんたみたいな腑抜けの下で無駄に時間を過ごしちまった。商船を襲ってりゃ、一財産築けたはずだ。 だから失った儲けを取り返したいだけさ。");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "よし。これが金だ……さあ、とっとと失せろ！";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "自分が誰か忘れてるんじゃねえか！お前みたいな半端者に俺に向かって怒鳴らせるつもりはねえぞ！";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("good");
			dialog.text = "行けよ、船長！自分を見せてやれ！";
			Link.l1 = "神のみぞ知る、俺はそんなこと望んじゃいなかったんだ！";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			OfficersReaction("bad");
			dialog.text = "それはまた別の話だな。じゃあな！";
			Link.l1 = "できれば二度とお前と道を交えたくはないものだ。";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("さて、決まったな。それじゃあ、船長、恨みっこなしでお別れだ…","残念だな、船長。でも神のみぞ知る、俺はやれるだけやったぜ。さらばだ。","ふう、船長、あんたは本当に手強いな！よし、幸運を祈るぜ。"),LinkRandPhrase("残念だな、船長。お前の下で働くのは楽しかったぜ。","ああ、いろいろあるさ……だが、恨みはないぜ。じゃあな。","「あなたは私に不公平ですよ、船長。それでも、あなたの決断を尊重します。さようなら。」"));
			Link.l1 = "待て、気が変わった。この話はまた後でにしよう。";
			Link.l1.go = "exit_good";
			Link.l2 = "気を落とすな。幸運を祈るぜ…";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "待てよ……ちゃんと装備を渡しただろう。返せ、俺は大勢に装備を配るつもりはねえんだ……";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "待てよ……手ぶらで帰らせたくねえ。ほら、これを持っていけ "+sti(NPChar.rank)*500+" ペソだ。新しい仕事を探す間、役に立つだろう。";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "「ああ、そうさ、全部持っていけよ…」";
			Link.l1 = "俺の言ってること、わかってるよな……";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "ありがとうございます、船長！こんな思いがけないご厚意を……。そういえば、まだあなたの持ち物がいくつか残っていますが、お返ししましょうか？";
			Link.l1 = "もしかして……最近は良い剣を見つけるのも簡単じゃねえな……";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "ああ、心配しなくていい。君の働きの記念として持っておきなさい。";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("わかった、あなたの望み通りにしよう。だが安心しな、 俺はたとえ飢え死にしそうでも二度とお前のところには戻らねえからな！","船長、あんたの野盗まがいのやり口には俺も反吐が出るぜ。遅かれ早かれ、こうなる運命だったんだ。 言い訳なんざ必要ねえよ。","ならば、そのままお前の殺し屋どもと一緒にいろ。まともな人間なら、お前の船の士官室になんて顔を出しもしないさ。 ここはまるで売春宿じゃないか、神よお許しを！"),LinkRandPhrase("正直言って、あんたの下で働くのも気に入らなかったぜ。あんたが雇ったのはろくでなしばかりで、 まともに話せる奴なんて一人もいねえんだ。","ああ、そんな態度で船員たちに接していたら、すぐに一人ぼっちになっちまうぜ。そしたら言い訳なんて必要なくなるさ。 ","俺たちの敵意はお互い様だ、それが俺の慰めだ。じゃあな。"));
			Link.l1 = "待て。今は引退するには最適な時期じゃねえ。だが、要求はすべて認めてやるぜ。";
			Link.l1.go = "exit_bad";
			Link.l2 = "行け、行け。お前の説教なんかなくても俺は平気だ。";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "待て。今渡す "+sti(NPChar.rank)*500+" ペソだ。お前が路地裏で野垂れ死にして、それで俺が罪悪感を抱くなんてごめんだからな。";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("まあ、ありがとう。では、さらば……","ご理解いただきありがとうございます。ご武運をお祈りします。","これで終わりだ。幸運を祈るぜ…");
			Link.l1 = "俺の言ってること、わかってるよな。";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("しかし船長、それでは俺は陸に取り残されちまうじゃねえか。本当に俺を船から直接教区に送り出すつもりか？","「俺に対して不公平だぜ、船長。でも、ちゃんとした報酬をもらえれば恨みはしねえよ。」","「これが俺の戦傷に対するお前の感謝ってわけか？まあ、金で補償してもらわねえとやってられねえな。」");
			Link.l1 = "よし、考え直した。お前はここにいていい。ただし、この話はまた後で続けるぞ。";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "ああ、気にするな。ほら― "+sti(NPChar.rank)*500+" ペソだ。これで俺の船で過ごした時間の埋め合わせになるだろう。";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "金は渡してやるよ。だが、俺のおかげでお前はいい装備を手に入れたんだし、その品を俺に返すのが筋ってもんだろう。";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "「へえ、そうかい？じゃあ、お前がずっと受け取ってきた取り分はどうなんだ！？結局は文句を言って、 ボーナスをせびることになるって分かってたぜ。」";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "そう言うと思ってたが、お前の装備を返すのは俺が受け取ってからだ "+sti(NPChar.rank)*1000+" ペソだ。さもなきゃ、俺の死体を乗り越えて奪うしかねえぞ！";
			Link.l1 = "よし、じゃあ金を受け取れ。";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "お前、正気か！？タダで渡したものにそんな大金を要求するなんてどういうつもりだ！？なるほどな、 お前の偽善的な親切心よりも欲深さの方が勝ったってわけか。";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "俺を侮辱するんじゃねえ！海軍で一番じゃなくても、俺はれっきとした戦闘士官だ。お前みたいな粗野な奴にも、 俺は敬意を払わせるぜ！";
			Link.l1 = "まだ分かってねえなら、もう一度言ってやるぜ。泣きついても無駄だ、俺からは何ももらえねえぞ。";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("bad");
			dialog.text = "まあ、それでも俺は満足してやるぜ！";
			Link.l1 = "ほう、それは挑戦ってわけか？望みどおりにしてやるよ……";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("これが俺の運命かよ！心血注いで仕えたってのに、年金ももらえずに追い出されちまったんだぜ！","なんて不運だ！？雇われたと思ったら、すぐに追い出されちまう。 今じゃどの聖人にロウソクを灯せばいいのかも分からねえよ……","なんてこった！今年に入ってもう三回目のクビだぜ、しかも全部月曜日だ。 二日酔いのときに船長の前に顔を出すのはやめときゃよかったかもな。"),LinkRandPhrase("まあ、好きにしな。二度と会わないよう祈ってな。","ご希望通りに。しかし、これ以上優秀な士官は絶対に見つからないことを覚えておけ。","わかったぜ、船長、あんたの言う通りだ。だが神のみぞ知る、俺はちゃんと自分の仕事をやってきたんだよ……"));
			Link.l1 = "待て。今は引退するには最適な時期じゃねえ。だが、要求はそのままだ。";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("さっさと失せろ。今日は機嫌がいいんだから神に感謝しな。","さっさと消えろ。お前なんざ、弾丸を作るのにクソが役立つくらいには役に立たねえ士官だぜ。");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "待て。今渡す "+sti(NPChar.rank)*500+" ペソだ。お前が路地裏で死んじまって、俺が後ろめたくなるのはごめんだからな。";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "待てよ……ちゃんと装備を渡したんだ、俺の物を返せ。";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("ああ、ありがとうございます、船長！本当にご親切ですね…","ご理解いただきありがとうございます。ご健闘をお祈りします。","これで終わりだ。幸運を祈るぜ…");
			Link.l1 = "幸運を祈るぜ。最初の酒場で全部使い果たさないようにな。";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("今度は俺の道具まで持っていくのか！くそったれ！もう釣りでもしてやるよ、誓うぜ……","どうやら俺をすっかり丸裸にするつもりなんだな。\nまあ、仕方ねえ。もう俺に残された道は一つ、広場へ行くしかねえ……","ああ、どうもありがとうございます！今度は私を襲うつもりなんですね。ああ、なんて残酷な運命……持っていけばいいですよ、どうぞ！私に何ができるというのですか……");
				Link.l1 = "さっさと失せろ。お前なんざ、弾を作るのにクソが役立つのと同じくらい使えねえ士官だぜ。";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("承知しました、船長。でもまず、どうかこれを私に渡していただけますか "+sti(NPChar.rank)*1000+" ペソだ。これを精神的損害への償いとさせてくれ。","わかった。でも俺はまだ受け取りたいんだ "+sti(NPChar.rank)*1000+" 俺の骨身を削った忠実な働きへの報酬としてペソをくれ。");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "なんて悪党だ！よし、これがあんたの金だ。";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "正気じゃないのか！？俺が自分で渡した物に、よくもそんな大金を要求できるな！";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "あっはっは！冗談だぜ！穴だらけの帽子みたいな古い友達を追い出せるわけねえだろ！";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "なら、何もやらねえぞ！俺の金の音が聞こえるまで、一歩も動かねえからな！";
			Link.l1 = RandPhraseSimple("すぐに俺の剣の音が聞こえるぜ！","なら、お前は足から運ばれていくことになるぜ！");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // интерфейс обмена
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // интерфейс обмена
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // интерфейс обмена
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = "今度は何だ！？もう全部話しただろうが！二度とお前の船には乗らねえぞ。";
			Link.l1 = RandPhraseSimple("さっさと失せな。どうせ大した損じゃねえしな。","よし、行け。それ以上は引き止めない。");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "他に何かあるかい、船長？もう全部話し合ったと思ってたんだが……";
			Link.l1 = "いや、何もない。ただ別れを言いたかっただけさ……";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "船長、俺たちはすべて話し合って、要求も伝えたぜ。今さら気が変わったなんて言わねえよな？";
			Link.l1 = "よし、行けよ。どうせ大した損じゃねえからな。";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "船長、他にどんな質問があるっていうんだ？念のため言っておくが、俺はひどく気分を害してるし、 戻る気なんてさらさらねえぞ…";
			Link.l1 = "よし、行けよ。別にお前なんかそんなに必要じゃなかったぜ。";	 
			Link.l1.go = "Exit";
		break;
		
		// boal 05.09.03 offecer need to go to abordage -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		    dialog.text = "あいよ、船長！";
		    Link.l1 = "楽にしろ。";
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	    break;
		
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		    Diag.TempNode = "Hired";
		    dialog.text = "了解だぜ、船長！";
		    Link.l1 = "楽にしろ。";
		    Link.l1.go = "Exit";
	    break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "船長！それは光栄です！";
            Link.l1 = "秩序を守り、町を繁栄させておけ。俺は時々戻ってきて関税を回収するからな。";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "考えが変わった。";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "ご命令は何でしょうか？前回お越しになった時は "+FindRussianDaysString(iTemp)+" 前だ。";
			}
			else
			{
			    dialog.Text = "ご命令は何ですか？";
			}

            Link.l1 = "お前はどれだけ税金を "+NPCharSexPhrase(NPChar,"収集済","収集した")+" この時点で？";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "船でお前が必要だ、町での任務はもういいぞ。";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "ごきげんよう。";
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "俺の腕前なら集めることができる "+FindRussianMoneyString(iFortValue*iTax)+" 1日につき。以上 "+FindRussianDaysString(iTemp)+" I "+NPCharSexPhrase(NPChar,"収集した","収集した")+" "+FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum))+".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "集めた税金を全部受け取りたい。";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "ご奉仕ありがとうございます！";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "いいぞ！俺は陸のカッペじゃねえんだぜ。";
            Link.l8 = "それはいいな。";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "話を聞こう。";
			Link.l1 = "これは拿捕の話だ。";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "これはあなたの船のことだ。";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "しばらく俺の艦隊から離れて、自分の運を試してきてほしいんだ。";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "今のところ何もない。";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "それで、あなたの望みは何だ？";
			Link.l1 = "敵船には乗り込むな。自分と乗組員の身を大事にしろ。";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "敵船に乗り込んでほしい。";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "それで、あなたの望みは何だ？";
			Link.l1 = "乗り込んだ後に他の船と交換するのはやめてほしい。あの船は貴重すぎるんだ。";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "敵の船に乗り込んだとき、もしまともな船なら自分のものにできるぜ。";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "了解だ、船長。";
			Link.l1 = "楽にしろ。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "承知しました、船長。";
			Link.l1 = "楽にしろ。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "あいよ、船長。";
			Link.l1 = "楽にしてくれ。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "承知しました、船長。";
			Link.l1 = "楽にしてくれ。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	
		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "船長、私はあなたの戦隊を離れません、なぜならあなたはすでに三隻の船を解雇したからです。";
					Link.l1 = "ああ、もしかしたらお前の言う通りかもしれねえな。";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = "問題ねえよ、船長。どの町で落ち合うんだ？";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = "In the " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "考えが変わった。";
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = "船長、でも俺たちに敵対している植民地ではあなたを待てないぜ！";
				Link.l1 = "なあ、もうこの旅のことなんて忘れちまえよ……";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "船長、俺たちの乗組員にはほとんど水夫がいねえんだ！どこへ航海するつもりなんだよ！？";
				Link.l1 = "そうだ、俺たちは本当に水夫が足りねえんだ……";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "船長、そんな航海に必要な食糧が船に足りねえんだ。";
				Link.l1 = "ああ、その通りだ。旅は後回しでいいさ……";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "船長、でも俺の船はボロボロなんだ。この状況で一人で出航するなんて無謀だぜ！";
				Link.l1 = "ああ、その通りだ。お前の船は修理が必要だ。";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = "なるほど。では "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Gen")+" 行く "+sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days)+" 日数が経ったら、到着したら何をすればいいんだ？";
				Link.l1 = "植民地の港の沖で一ヶ月間停泊していろ。";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "そうだな、ふと思ったんだ。俺と一緒にいろよ……";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "なるほど、船長。すぐに出発します。";
				Link.l1 = "はい、ぜひお願いします。";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("今日はまた出航する……","「」での我々の会合を忘れないでくれ "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Dat")+".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "俺もそうしたいぜ。これからは俺の船はまたあんたの指揮下だ、船長。";
					Link.l1 = "「いいだろう。」";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // Потрем группу
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = "船長、あんたの艦隊にはすでに五隻の船があるじゃねえか――六隻目はどうするつもりだ？\nまあ、俺は自分の船でここで待たせてもらうぜ。あんたの新しい仲間たちはどうも信用できねえ。 あいつらの船なんざすぐ沈むだろうし、そしたらまた俺のところに戻ってくるんだろ？";
					Link.l1 = "おい、お前は頭が切れるじゃねえか！船長なんかじゃなくて提督になるべきだぜ！";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "おお、船長、やっぱり戻ってきたな、俺の言った通りだぜ。で、今はお前の艦隊に空きがあるのか？";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "「ああ」 "+NPChar.name+"「いるぞ。一隊へようこそ。」";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = "残念ながら、まだだ。";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- Самостоятельное плавание компаньона
		
		case "tonzag_after_boarding":
			dialog.text = "船長、大変です！敵にがっちりと押さえ込まれていて、このままじゃ殺されるまで離してくれそうにありません！今、我々 の仲間は本当に危機的状況ですし、砲手のほとんどがやられています！";
			link.l1 = "俺が奴らを助ける。指揮を取ってここから脱出しろ！";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "はい、旦那！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "勝利です、船長！上陸部隊は全滅し、敵は撤退して南へ向かうことを選びました。船の状態は許容範囲です。\n生存している乗組員： "+GetCrewQuantity(pchar)+" 人々。報告は完了した！";
			link.l1 = "ありがとう！皆にラムをふるまえ、港に着くまで見張りを強化しろ！";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "万歳！あいよ！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
		
		// --> Эпилог
		case "SharlieEpilog_Folke_1": // Фульк
			dialog.text = "それじゃ…別れを言う時が来たってことか？";
			link.l1 = "どうやらそうみたいだ。そして正直言って、この決断がもっと簡単だと思ってたんだ。";
			link.l1.go = "SharlieEpilog_Folke_2";
		break;
		
		case "SharlieEpilog_Folke_2":
			dialog.text = "それじゃ…ありがとうな、キャプテン、すべてに。多くの船長を見てきたが、誓って言うよ、あんたはその中で最高だ。あんたの旗の下で航海できたことは名誉だった。";
			link.l1 = "お前は忠実な士官だった、"+npchar.name+"。勤務に感謝するよ。運命がまた俺たちを…そして敵対する側じゃなく再び出会わせてくれることを願ってる。";
			link.l1.go = "SharlieEpilog_Folke_nothing";
			link.l2 = "それを聞いて嬉しいよ、友よ。感謝してる。お前が退役するにあたり一か月分の給与を支給するよう手配するよ。長年の勤務と忠誠に感謝する。そしてな…そろそろお前自身が船長になるべき時だと思うんだ。考えてみろ。";
			link.l2.go = "SharlieEpilog_Folke_salary";
			link.l3 = "そしてお前にも感謝するぜ、相棒。お前は立派で有能な士官だ。忠誠への感謝の印として、三か月分の給与を渡すよう手配する。それと、"+npchar.name+"、もしまた借金で捕まったって聞いたら…誓って、全部投げ出して戻って助けに行ってやる——そして無人島に置いてやるからな。";
			link.l3.go = "SharlieEpilog_Folke_salary_X3";
		break;
		
		case "SharlieEpilog_Folke_nothing":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Folke_exit");
		break;
		
		case "SharlieEpilog_Folke_salary":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Folke_exit");
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Folke_salary_X3":
			dialog.text = "はは、いや、キャプテン、もう金貸しのところには二度と足を踏み入れないぜ。でも船長になるってのは…興味深いアイデアだ。正直何度も考えたことがある。もしかしたら本当にやるかもな。";
			link.l1 = "それともう一つ。酒場で送別会を開くつもりだ。来てくれると嬉しい。こっちの仲間をお前の船員として勧誘する良い機会にもなるだろう。";
			link.l1.go = "SharlieEpilog_Folke_salary_X3_2";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Folke_salary_X3_2":
			dialog.text = "もちろん行くよ、キャプテン。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Folke_salary_X3_3";
		break;
		
		case "SharlieEpilog_Folke_salary_X3_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Folke_exit");
		break;
		
		case "SharlieEpilog_Duran_1":
			dialog.text = "ああ、まったく、その言い方じゃ足りないくらいだよ。本当に久しぶりで、もうどうやるかすら覚えてない、はは。";
			link.l1 = "じゃあ話してやることを気に入るかもしれないな。聞けよ、俺は旧世界へ向かうんだ。父さんに会うのはずっと前で、彼は心配してる — 正直俺もだ。でも俺は客として行くんだ。他人の船でな。";
			link.l1.go = "SharlieEpilog_Duran_2";
		break;

		case "SharlieEpilog_Duran_2":
			dialog.text = "客として？ まあ、それはそれだな。";
			link.l1 = "これからもこの調子でやるべきか見極めたいんだ。どうなるか分からん、運が俺を見捨てるかもしれないしな。";
			link.l1.go = "SharlieEpilog_Duran_3";
		break;

		case "SharlieEpilog_Duran_3":
			dialog.text = "そういうことか。ははは。お前が海を捨てられるとは信じられないな。本物の海の狼は陸に上がったら、退屈で飲んだくれるか、首を吊るかのどっちかだ。";
			link.l1 = "だからこそ俺は客として行くんだ — その時が来たらそんな生活ができるか確かめるためにな。でも重要なのはそれだけじゃない: お前たちを連れて行けない — そして待つように言えない。俺自身、いつ戻るかも分からないんだ。父さんは家のことを頼みたいだろうしな。";
			link.l1.go = "SharlieEpilog_Duran_4";
		break;

		case "SharlieEpilog_Duran_4":
			dialog.text = "つまりこれからはそれぞれ自分の道を行くってことか？ まあ…いずれはこうなるさ。でも別れってのは好きじゃないから、涙も抱擁も期待するなよ。";
			link.l1 = "勤務に感謝する。お前なら大丈夫だと思うが、それでも — また会う前に命を落とさないようにな。";
			link.l1.go = "SharlieEpilog_Duran_nothing";
			link.l2 = "じゃあ俺の助言を聞け — 古い仕事からは離れていた方がいい。それじゃあいいことなんてない。ほら、しばらく暮らせるくらいの銀貨をやるよ。軍隊に入れとは勧めないが、どこかの船長の護衛になる — それも悪くないだろう。考えてみろ。";
			link.l2.go = "SharlieEpilog_Duran_salary";
			link.l3 = "涙はないって？ なら銀貨をやろう。はは、お前の目が輝いているのが見えるよ。さあ、これを持て。三か月分の給料 — ル・フランソワの海賊みんなに一週間飲ませるくらいはある。あるいは、言い換えれば半年は暮らせるだろう。何かやることを見つけて、生計を立てる方法を見つけられることを願ってるよ。";
			link.l3.go = "SharlieEpilog_Duran_salary_X3";
		break;
		
		case "SharlieEpilog_Duran_nothing":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Duran_exit");
		break;
		
		case "SharlieEpilog_Duran_salary":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Duran_exit");
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Duran_salary_X3":
			dialog.text = "もう決めたんだ。俺は宝探しの冒険者になるよ。そこには…何かがある。";
			link.l1 = "はは！いい選択だ！そしてもうひとつ: 最後に思いっきり楽しむつもりだ。だから一緒に来たいなら — 酒場に来いよ。";
			link.l1.go = "SharlieEpilog_Duran_salary_X3_2";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Duran_salary_X3_2":
			dialog.text = "冗談だろ、キャプテン？ はは！これは絶対に逃さないぜ！";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Duran_salary_X3_3";
		break;
		
		case "SharlieEpilog_Duran_salary_X3_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Duran_exit");
		break;
		
		
		// <-- Эпилог
	}
}
