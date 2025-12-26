// НПС офиса ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何か用か？";
			link.l1 = "いいや。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// офицер
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "警報だ！敵が来たぞ！武器を取れ！";
				link.l1 = "くそっ！";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "お前、そこで止まれ！その顔、見覚えがあるぞ…そうだ！お前は罪で指名手配されているんだ！\n野郎ども、そいつを捕まえろ！";
				link.l1 = "くそっ！";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "オランダ西インド会社へようこそ。用件は手短に、時間は金だ。";
				link.l1 = "私は交易の用事で来ている。免許証や航海用具などだ…";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "私の働きを会社に提供したいんだ。もちろん、見返りは金で頼むぜ。雇う気はあるか？";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "オランダ西インド会社へようこそ。用件は手短に、時間は金だ。";
				link.l1 = "申し訳ありません、どうやら私の勘違いだったようです。失礼します。";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "私は交易の用事で来ているんだ。免許証や航海用具など、いろいろと……";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "手短に話せ、時間は金だ。";
			link.l1 = "私は交易の用事でここに来たんだ。免許証や航海用具など、いろいろと……";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "私の働きを会社に提供したいのです。もちろん、見返りは金貨で。雇う気はありますか？";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "それならローデンブルグ旦那の執務室へ二階に上がってくれ。";
			link.l1 = "ありがとうございます、これから向かいます。";
			link.l1.go = "HWIC_officer_exit";
			// belamour legendary edition переехали по другому адресу
			LocatorReloadEnterDisable("GVIK", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = "今はカンパニーは人を雇っていない。";
			link.l1 = "それは残念だ。ご迷惑をおかけして申し訳ない。";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "ミネール・ヘリッツに話しかけてくれ。入って左手のテーブルにいる。あいつは契約船長たちと取引しているんだ。";
			link.l1 = "ありがとうございます、士官殿……";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_exit":
			DialogExit();
			// belamour legendary edition переехали
			LAi_ActorGoToLocation(npchar, "soldiers", "soldier3", "GVIK", "soldiers", "soldier3", "", 5);
			DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
			NextDiag.TempNode = "HWIC_officer";
		break;
		
		// солдаты
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "警報だ！敵が来たぞ！武器を取れ！";
				link.l1 = "くそっ！";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "あはは！お前が誰か分かったぞ…そうだ！お前は罪で指名手配されているんだ！\n野郎ども、こいつを捕まえろ！";
				link.l1 = "くそっ！";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "うちの士官かヘリッツ旦那に話せ。俺はお前に言うことはない。今は勤務中だ。";
			link.l1 = "あなたの規律は見事だ。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "警報だ！敵が来たぞ！兵隊ども！";
				link.l1 = "くそっ！";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "マインヘール・ヘリッツに話しかけてくれ。";
			link.l1 = "わかったよ、了解だ。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "警報だ！敵が来たぞ！兵士たち、あいつを捕まえろ！";
				link.l1 = "くそっ！";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "ふむ。お前、どこか怪しいと思ったが……そうか！お前はオランダに対する数々の罪で指名手配されているんだ！\n兵士たち、こいつを捕まえろ！";
				link.l1 = "くそっ！";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "何かご用ですか、旦那？";
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = "オランダ西インド会社の交易許可証を買いたい。";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "ここで航海用の計器や他にも役立つ品が買えると聞いたんだが、本当か？";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "今日は何を売っているんだ？";
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = "面白い書類があるんだ、旦那。最初の数行を見てくれ。共和国の存続と会社の利益に関わる内容だ。それに、 ある会合の座標も記されている。興味があるなら売ってやるぜ。もちろん、たっぷり払ってもらうがな。\n";
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "レジナルド・ジャクソンという名の船長があなたの下で働いているはずです。彼は『ハーピー』 というシーベック船に乗っています。彼を探す方法を教えていただけませんか？彼と重要な用件があるのです。";
				link.l4.go = "caleuche";	
			}
			// Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
			{
				link.l4 = "至急ローデンブルフ旦那にお目にかかる必要があります。非常に重要な用件です。彼はどこにいますか？";
				link.l4.go = "PZ_RazgovorGerrits_1";
			}
			link.l9 = "いいえ、なんでもありません。";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "まあ、購入するのは自由だ。ただし、忠告しておくが、会社は厳格な中立性を重んじている。したがって、 この免許を持っている間は、どの国の商船も攻撃することは禁止されている\nもしそのような行為が発覚した場合、免許は即座に無効となる。また、オランダや会社と何らかの理由で対立した場合も、 免許は取り消される。理解したか？";
				link.l1 = "澄みきった水のように明快だ。覚えておくよ。";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "ライセンスの購入は歓迎しますよ。さて、何日分にしますか？";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "この許可証があれば、どの国の港でも自由に出入りできる。あなたの平和的な意図と、 交易が目的であることを示すものだ。ただし、法律に違反した場合は役に立たない。そのときは単に没収されるだけだ。 覚えておくように。\nどの港に入る前にも、必ず友好の旗を掲げるのを忘れるな。巡回兵や砲台の砲手は、 まず撃ってから質問するのが常だからな。\n許可証の最短期間は二十日、最長期間は六ヶ月、つまり百八十日だ。\nそうだ、もうひとつ言い忘れていた……我々の由緒ある伝統によれば、許可証に関する取引はすべてドゥブロン金貨で支払う決まりだ。さて、 条件について話そう。許可証の期間はどれくらいにする？";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "申し訳ありませんが、もう少し考えさせてください。また後でお会いしましょう。";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "旦那、もっとはっきり話してください。よく聞こえませんでした。それで、どれくらいの期間ですか？";
				link.l1 = "「ちょっと考えさせてくれ…」";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "免許の最短期間は二十日間だ。\nどうする？二十日、それとももっと長くするか？";
				link.l1 = "「ちょっと考えさせてくれ……」";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "免許の最長期間は半年だ。百八十日以内ってことか？";
				link.l1 = "「考えさせてくれ……」";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "For "+FindRussianDaysString(sti(fQty))+"？　よろしい。それには費用がかかる "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+"。これらの条件で納得いただけますか？";
			if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "ああ、そうだ。";
				link.l1.go = "licence_2";
			}
			link.l2 = "残念ながら、今はそんなに大金を持っていません。後で許可証を取りに戻ります。";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "申し訳ありませんが、まだ考えさせてください。\nまた後でお会いしましょう。";	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "start")
			{
				if(iQty < 180) 
				{
					Log_info("Quest: 'Together with the Shark' - your license is less than 180 days");
				}
				else 
				{
					pchar.questTemp.SharkGoldFleet.LicenceOk = true;
					AddQuestRecord("SharkGoldFleet", "2");
				}
				pchar.questTemp.SharkGoldFleet = "afterGvik";
			}
			dialog.text = "ちょっと待ってくれ……ここにサインと印をして……封印、よし。書類を受け取ってくれ。";
			link.l1 = "ありがとう！さようなら、旦那。";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "ええ、ございますよ。ここではコンパスやアストロラーベ、クロノメーター、砂時計などの航海用具を販売しています。 ただし、砂時計以外は常に在庫が揃っているとは限りません。 他の道具は契約業者や船長たちがすぐに買い占めてしまうのです。もしお探しの物が見つからなければ、 補充される来週にまたお越しください。\n地図や望遠鏡も取り扱っております。ご覧になりますか？";
			link.l1 = "「はい、お願いします。」";
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// депеша Кромвеля
		case "depeshe":
			dialog.text = "ふむ、見せてみろ...(読みながら) ほうほう……クロムウェルの欲は増すばかりか。カンケル！あのピューリタンの犬どもは、自分たちの島で流した血だけじゃ足りず、 こんな汚物までこっちに持ち込むのか！？この伝令はどこで手に入れたんだ？";
			link.l1 = "イギリスの使者から奪ったんだ。さて、これを買いたいか？";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "はい。ピーター・スタイフェサントもきっとこれを読んで本当に喜ぶでしょう。そして、 彼はそれを止めるために効果的な手を打つはずです……支払いは金のドゥブロンでもいいし、半年間の許可証を書き出すこともできます。どちらがご希望ですか？";
			link.l1 = "俺は金を選ぶ。";
			link.l1.go = "depeshe_dublon";
			link.l2 = "俺はその許可証が欲しいんだ。";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info("You have received 700 doubloons");
			dialog.text = "よろしい。これが約束の七百ドゥブロンだ。見事な働きへの立派な報酬だぞ。";
			link.l1 = "こちらがあなたの伝令書です。";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "よし。半年間有効の免許証だ。";
			link.l1 = "ありがとうございます！そして、こちらがあなたの伝令書です。";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "ありがとう。共和国への良心と忠誠を示してくれて嬉しいよ。 君の善行についてはマティアス・ベックとピーター・スタイフェサントにも伝えておく。";
			link.l1 = "それは良いことだ。じゃあな！";
			link.l1.go = "exit";
		break;
		
		// Sinistra Путеводная звезда
		case "PZ_RazgovorGerrits_1":
			dialog.text = "申し訳ありませんが、彼はすでにシュヌール家と一緒に旧世界へ旅立ちました。 あなたにもそのことを話していたと思います。";
			link.l1 = "そうだ、その通りだ。しかし、私は彼が最近群島での用事で遅れているのではないかと期待していたんだ。\n教えてくれ、ヘリッツ、会社の誰かがローデンブルク旦那と連絡を取り合っているのか？もしかして、 連絡船を使っているとか？";
			link.l1.go = "PZ_RazgovorGerrits_2";
		break;
		
		case "PZ_RazgovorGerrits_2":
			dialog.text = "とんでもない――彼が出発する前に、二度と自分に構うなと言われたんだ――新しくてもっと良い人生を始めるってさ。";
			link.l1 = "俺たちの人生も良くなるといいな。さよなら。";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "積荷目録を確認させてくれ……イケマ、イメルゼール、ヤコブス……ジャクソン、いたな。ふむ、レジナルド・ジャクソン船長は現在、 ポートロイヤルとフィリップスバーグ間で定期航路を運航中だ。その航路で探すといい。さて、船長、 あらかじめ警告しておくが――もし何か悪だくみを考えているならやめておけ。あのジャクソン船長は我々の保護下にある。分かったな、旦那？";
			link.l1 = "俺はただあいつと取引があるだけだ。単なる商売だよ。別にあいつに危害を加えるつもりはねえ。";
			link.l1.go = "caleuche_1";
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
		break;
		
		case "caleuche_1":
			dialog.text = "素晴らしい。ジャクソン船長は普段、ポートロイヤルやフィリップスバーグに長居しないんだ。結局のところ、 時間は金だからな。船の荷下ろしと積み込みが終われば、すぐに出航するのが常だ。 海路で彼に会う方がよほど可能性が高いぜ。";
			link.l1 = "ありがとう！";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_PrepareCreateGarpiya");
		break;
		
		// новый босс ГВИК
		case "HWIC_Boss":
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if (!CheckAttribute(npchar, "quest.silk_info"))
				{
					if (sti(pchar.reputation.nobility) > 60)
					{
						dialog.text = "あはは、カピテン "+GetFullName(pchar)+"！来てくれて嬉しいぜ。お前に商売の話があるんだ。";
						link.l1 = "面白い！話を聞こう、旦那。";
						link.l1.go = "silk_info";
						break;
					}
					else Notification_Reputation(false, 61, "low");
				}
			}
			dialog.text = "ごきげんよう、カピテン "+GetFullName(pchar)+"！どのようにお役に立てますか？";
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
				{
					if (GetDataDay() == 1 || GetDataDay() == 15)
					{
						link.l1 = "その船の絹の件だが…";
						link.l1.go = "trade_silk";
					}
				}
			}
			link.l2 = "ごきげんよう。いや、何も用はない。ただ挨拶したかっただけだ。";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "私は最近、リヨンの商人とカリブへの船用絹の供給について取引関係を築いたのです。ご存じですか？\nこの絹で作られた帆は世界一と評判ですから、あなたもきっと興味があるでしょう。";
			link.l1 = "俺をぶっ倒してくれ、ああ、それは耳に心地いい話だぜ。条件は何だ？";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "小口だけど定期的な出荷だ。二週間ごとに三十巻を取り置きできる。一巻の値段は二十ドゥブロンだ。こうしよう。 毎月一日と十五日に三十巻を君のために確保する。その時に取りに来なければ、他の客に売るからな。";
			link.l1 = "義理はないんだな？";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "その通りだ、カピテン。欲しければ絹を買いな。全部まとめて六百ドゥブロンだぜ。常連になってくれると嬉しいな。";
			link.l1 = "ご提案ありがとうございます、旦那。取引成立だ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
			AddQuestRecordInfo("Unique_Goods", "3");
		break;
		
		// торговля шелком
		case "trade_silk":
			if (CheckAttribute(pchar, "questTemp.UpgradeSilk"))
			{
				dialog.text = "もちろんだ、カピテン。あんたの絹は用意してあるぜ。支払う準備はできてるか？";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "もちろん！ほら、2,550ドゥブロンを受け取ってくれ。";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "くそっ、金を船に置いてきちまった。すぐに持ってくるぜ！";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "もちろんだ、カピテン。あんたの絹は用意してあるぜ。支払う準備はできてるか？";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "もちろん！はい、六百ドゥブロン受け取ってくれ。";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "くそっ、金を船に置いてきちまった。すぐに持ってくるぜ！";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && !CheckAttribute(pchar, "questTemp.GVIKSilkBlock")) // увеличить объём поставок шёлка
			{
				link.l4 = "Mijnheer "+npchar.name+"、絹の供給量を増やす可能性について話し合いたいのですが。";
				link.l4.go = "UpgradeSilk";
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && CheckAttribute(pchar, "questTemp.GVIKSilkPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок шёлка, если в первый раз не принесли
			{
				link.l4 = "旦那、ドゥブロン金貨を持ってきたぜ\n "+npchar.name+"。どうぞお受け取りください。";
				link.l4.go = "UpgradeSilk_Agreed";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You have given 600 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "取引できて光栄だぜ、カピタン。お前さんの絹はロングボートで船まで届けさせる。";
			link.l1 = "ありがとう！";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "またすぐにお会いできることを願っています。\nまた戻ってきてください。";
			link.l1 = "もちろん。またな！";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk": //
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "あなたのビジネスの姿勢は評価しますし、ご要望も検討するつもりです。\n例えば、取引量を五倍に増やすのも可能かもしれません。\nしかし、そのような供給体制を整えるには多大な資源が必要となります。\n倉庫の拡張、警備の強化、そして確実な輸送ルートの確保が求められます。\nこれはあなたにも利益がある話ですから、これらの費用は折半することを提案します。";
				link.l1 = "すべてもっともらしく聞こえますね。これらの費用をまかなうのに、いくら必要だとお考えですか？";
				link.l1.go = "UpgradeSilk_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "供給を増やしたいというご要望は理解しておりますが、現段階ではそのような変更に同意するのは難しいです。 貴殿の発展への意欲に疑いはありませんが、この種の取引には、 より多くの交易経験とご自身の行動への確固たる自信が必要です。まずは交渉術についてさらに知識を深め、 より具体的な提案を携えて再度お越しください。準備が整いましたら、喜んで協力関係を強化いたします。";
				link.l1 = "ふむ……わかった。この話はまた後で戻るとしよう。";
				link.l1.go = "exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_1":
			dialog.text = "すべての事情を考慮すると、あなたの負担分は三千枚の金ドゥブロンになります。\nこの資金があれば、必要な手配を遅滞なく進めることができます。";
			link.l1 = "Mijnheer "+npchar.name+"「三千ドゥブロンだと？冗談か？私は誠実な提案を持ってきたのに、 物資の手配だけでそんな法外な金額を払えと言うのか？」";
			link.l1.go = "UpgradeSilk_2";
		break;
		
		case "UpgradeSilk_2":
			dialog.text = "どうか誤解なさらないでいただきたい。私はあなたを騙そうとしているわけではありません。この金額は、 補給の手配を適切に行うために必要なものです。倉庫や警備の拡張だけでなく、この事業の予測不能さにもかかわらず、 遅延や損失なく商品を確実にお届けするための保証でもあります。こうした規模では標準的な経費です。最終的には、 あなたの投資は必ずや正当化され、商品も適切な状態で期日通りにお受け取りいただけます。";
			link.l1 = "あなたの説明には多少安心させられます、ミンヘール。しかし、それでもこの金額は高すぎます。 もし価格をせめて二千五百ドゥブロンまで下げていただけるなら、あなたの条件を受け入れる用意があります。 それだけあれば、補給の手配や安全対策を十分に行えると確信しています。";
			link.l1.go = "UpgradeSilk_3";
		break;
		
		case "UpgradeSilk_3":
			dialog.text = "承知しました。金額が大きいのは理解しておりますが、先ほど申し上げた通り、 作業を適切に遂行するために必要なのです。これを減額することはできません。そうすれば我々 の努力がすべて水の泡になりかねませんから。しかし、騙されたと感じてほしくはありませんので、 今後のすべての補給品に関して十五パーセントの割引をお約束いたします。 これでご負担を補っていただけることを願っております。";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "ふむ、十五パーセントの値引きは確かに前進ですな。\nよろしい。価格は非常に高いと感じますが、あなたの提案を受け入れる覚悟はできています。\n我々の協力が私の期待に応えてくれることを願っています。\nこれがあなたのお金です。";
				link.l1.go = "UpgradeSilk_Agreed";
			}
			link.l2 = "Mijnheer "+npchar.name+"旦那、あなたの申し出では他に選択肢がありません。三千ドゥブロンで手を打ちましょう、かなりの大金ですが。しかし、 今すぐ全額を支払うことはできません。金が用意でき次第、必ず戻ってきます。";
			link.l2.go = "UpgradeSilk_5";
			link.l3 = "「15パーセントの値引き？旦那」 "+npchar.name+"、こんなのは予想していなかったぞ。この金額は経費どころか、まるで堂々たる強盗じゃないか！だが、 お前との取引関係を断つつもりはない。以前の条件に戻そう――絹30反を1反あたり20ドゥブロンで、だ。";
			link.l3.go = "UpgradeSilk_4";
		break;
		
		case "UpgradeSilk_Agreed":
			dialog.text = "同意してくれて嬉しいよ。 "+pchar.name+"。さて、詳細についてだが、絹150反を1反あたり17ドゥブロンで。合計で全ロット2550ドゥブロンだ。商品はいつも通り、毎月1日と15日に受け取れる。双方にとって良い利益になる取引だと思うぞ。";
			link.l1 = "素晴らしい！これでこそだ。じゃあな、旦那。またすぐ会おう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "3_1");
			pchar.questTemp.UpgradeSilk = true;
			pchar.questTemp.GVIKSilkBlock = true;
			DeleteAttribute(pchar, "questTemp.GVIKSilkPotom");
		break;
		
		case "UpgradeSilk_4":
			dialog.text = "これは単なる商取引であって、あなたには強盗のように見えたかもしれませんが、そうではありません。\nしかし、ご希望通りにしましょう。いつも通り、1日と15日に絹の受け取りに来てください。新たな取引ができることを楽しみにしています。";
			link.l1 = "かしこまりました、旦那。ごきげんよう。";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_5":
			dialog.text = "正しい決断をしてくれて嬉しいよ。金を持ってきたら、取引の詳細をすべて話し合って、実行に移すとしよう。";
			link.l1 = "さようなら、旦那 "+npchar.name+"。必要な額が集まり次第、また会おう。";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			pchar.questTemp.GVIKSilkPotom = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("HWIC_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("HWIC_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
