int iClockSP4PseudoGlobal = SOUND_INVALID_ID;

void ProcessDialogEvent()
{
	ref NPChar, sld, realShip;
	aref Link, NextDiag, arTmp;
	int i, n, NextMonth, idx;
	string sTemp, sStr, Month, NationName, shipType;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (HasSubStr(Dialog.CurrentNode, "chosenIdx/"))
	{
		Dialog.tmpIdx = FindStringAfterChar(Dialog.CurrentNode, "/");
		Dialog.CurrentNode = FindStringBeforeChar(Dialog.CurrentNode, "/");
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "「何でもない。」";
			link.l1.go = "exit";
		break;
		
		// Диалог с Йоханом
		case "ClockTower_Johan_1":
			dialog.text = "待て、船長旦那。ここから先は通行禁止だ。";
			link.l1 = "なぜだ？";
			link.l1.go = "ClockTower_Johan_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_2":
			dialog.text = "あの塔が見えるか？オランダ西インド会社の事務所だ。船籍登録部と記録保管所がある。入るには予約が必要だぞ。";
			link.l1 = "「それで、どうやって面会の約束を取り付けるんだ？」";
			link.l1.go = "ClockTower_Johan_3";
		break;

		case "ClockTower_Johan_3":
			dialog.text = "知るべき奴は知っている。ミネール取締役は誰とでも仕事をするわけじゃねえ。";
			link.l1 = "「ディレクター旦那」？誰のことだ？";
			link.l1.go = "ClockTower_Johan_4";
		break;

		case "ClockTower_Johan_4":
			dialog.text = "ファン・ドーン所長。正確には所長じゃないかもしれねえが、みんなそう呼んでるんだ。ここで十年働いてて、 全部に秩序をもたらした。今じゃカリブ海のどの船も彼の事務所を通るんだぜ。";
			link.l1 = "「すべての船か？軍艦までか？」";
			link.l1.go = "ClockTower_Johan_5";
		break;

		case "ClockTower_Johan_5":
			dialog.text = "最高級の船と最も裕福な船長たちだけだ。\n我々の事務所の顧客であることは大変な名誉なんだぜ！";
			link.l1 = "どんなサービスを提供しているんだ？";
			link.l1.go = "ClockTower_Johan_6";
		break;

		case "ClockTower_Johan_6":
			dialog.text = "詳しいことは知らねえ――俺は入り口を見張ってるだけだ。\nだが、みんな満足して出ていくって話だぜ。";
			link.l1 = "見事だな。";
			link.l1.go = "ClockTower_Johan_7";
		break;
		
		case "ClockTower_Johan_7":
			dialog.text = "それからもう一つ教えてやろう。あの時計が見えるか？ヨーロッパの驚異だ――こんなものはこの田舎じゃ他に見られねえ。旦那監督自ら手入れしてるんだぜ。";
			link.l1 = "もしかして、話し合いで手を打てるんじゃねえか？";
			link.l1.go = "ClockTower_Johan_8_1";
			link.l2 = "中に入るために何かできることがあるはずだろう？";
			link.l2.go = "ClockTower_Johan_8_2";
		break;

		case "ClockTower_Johan_8_1":
			dialog.text = "俺は賄賂なんか受け取らねえ！";
			link.l1 = "申し訳ない。あんたはいい奴だな。名前は何ていうんだ？";
			link.l1.go = "ClockTower_Johan_9";
		break;
		
		case "ClockTower_Johan_9":
			dialog.text = ""+npchar.name+"…見ろよ…あんたがこの辺の人間じゃないのは分かってる。だが、ここには秩序があるんだ。ミネール館長がいつも言うんだぜ、 「一度でも弱みを見せたら、この塔は崩れ落ちる」ってな。中に入りたいのか？街を助けろ——そうすりゃ目をかけてもらえるさ。";
			link.l1 = "なるほど。気を抜くな、兵士。";
			link.l1.go = "ClockTower_Johan_11";
		break;

		case "ClockTower_Johan_8_2":
			dialog.text = "そうだな、俺には分からねえよ。ミネール長官はウィレムスタッドの友人には報酬をくれるぜ。町を助ければ――きっと目をかけてもらえるさ。あんたがこの辺の人間じゃねえのは分かってる。だが、ここじゃ秩序が大事なんだ。 ミネール長官はいつも言うぜ、「一度でも弱さを見せたら、この塔は崩れちまう」ってな。";
			link.l1 = "なるほど。それで、お前の名前は何だ？";
			link.l1.go = "ClockTower_Johan_10";
		break;
		
		case "ClockTower_Johan_10":
			dialog.text = ""+npchar.name+", "+GetTitle(NPChar, true)+".";
			link.l1 = "そして俺は "+GetTitle(NPChar, false)+" "+GetFullName(pchar)+"。油断するな、兵士。";
			link.l1.go = "ClockTower_Johan_11";
		break;
		
		case "ClockTower_Johan_11":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_1");
		break;
		
		case "ClockTower_Johan_repeat":
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) >= 51)
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
				link.l1 = "何かあったのか？";
				link.l1.go = "ClockTower_Johan_22";
				Notification_ReputationNation(true, 51, HOLLAND);
			}
			else 
			{
				dialog.text = ""+Greeting(true)+", "+GetTitle(NPChar, true)+"。何かお手伝いできることはありますか？";
				link.l1 = "「いや」 "+npchar.name+"。続けろ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_repeat";
				Notification_ReputationNation(false, 51, HOLLAND);
			}
		break;
		
		case "ClockTower_Johan_21":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
			link.l1 = "何かあったのか？";
			link.l1.go = "ClockTower_Johan_22";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_22":
			dialog.text = "おめでとうございます。予定された面会があります。";
			link.l1 = "「約束？誰とだ？」";
			link.l1.go = "ClockTower_Johan_23";
		break;

		case "ClockTower_Johan_23":
			dialog.text = "マイネール取締役代理と一緒だ。あなたが街を助けてくれたことを聞いて、私にあなたを招待するよう命じたんだ。";
			link.l1 = "監督本人はどうなんだ？";
			link.l1.go = "ClockTower_Johan_24";
		break;

		case "ClockTower_Johan_24":
			dialog.text = "えっと…その件については俺には話す権限がねえんだ。中で健闘を祈るぜ。 "+GetTitle(NPChar, true)+".";
			link.l1 = "ありがとうございます。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower");
		break;
		
		// Диалог с Маартеном Виссером, заместителем директора
		case "ClockTower_Visser_1":
			dialog.text = "DWIC船籍登録部へようこそ。船長……？";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_2":
			dialog.text = ""+GetFullName(NPChar)+"、\n" +
							"マールテン・ヴィッサー、副所長。\n" +
							"ウィレムスタッドにずいぶん貢献してくれたと聞いている。\nもしかしたら、我々の役所も君の役に立てるかもしれないな。";
			link.l1 = "だから俺はここにいるんだ。";
			link.l1.go = "ClockTower_Visser_3_1";
			link.l2 = "キュラソーの首都のお役に立てて嬉しいです。";
			link.l2.go = "ClockTower_Visser_3_2";
		break;

		case "ClockTower_Visser_3_1":
			dialog.text = "どんな船長でも――フランス人でも、スペイン人でも、オランダ人でも――俺たちに船の検査を依頼できるぜ。\n艤装、大砲、艤具を調べて、弱点を見つけて、改善策を提案するんだ。";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
		break;

		case "ClockTower_Visser_3_2":
			dialog.text = "どんな船長でも――フランス人でも、スペイン人でも、オランダ人でも――俺たちに船の検査を依頼できるぜ。\n艤装、大砲、装備を調べて、弱点を見つけて、改善策を提案するんだ。";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "ClockTower_Visser_4":
			dialog.text = "もし一度の監査で足りなければ、新しい船の書類も手配できるぜ。\nつまり、うちの事務所の仕事でお前さんの船はもっと良くなるってわけだ――貴重なマホガニーや絹を使わずにな。";
			link.l1 = "「そんなことがあり得るのか？」";
			link.l1.go = "ClockTower_Visser_4_1";
		break;

		case "ClockTower_Visser_4_1":
			dialog.text = "船長、あんたは自分がどれほど強大な場所に足を踏み入れたか、 そしてたった一本のペンの一振りがどれほどのことを成し遂げるか、まるで分かっちゃいねえ。";
			link.l1 = "ドゥブロン金貨のためだろうな？";
			link.l1.go = "ClockTower_Visser_5";
		break;

		case "ClockTower_Visser_5":
			dialog.text = "当然だ。俺たちのサービスは安くねえし、お前の船の大きさ次第で値段も変わる。だが、必ず元は取れるぜ。 ここを通った船長が失敗することは滅多にねえんだ\n" +
						"しかし、俺たちはお前の金を奪うだけじゃねえ――稼ぐチャンスも与えてやる。\n今や海賊どもは増えすぎて、小アンティル諸島ですら、船長たちは害虫退治のために艦隊を組まなきゃならねえ。\n退治した証拠を持ってこい――同じドゥブロン金貨で報酬を払ってやるぜ。";
			link.l1 = "「どんな証拠だ？」";
			link.l1.go = "ClockTower_Visser_6";
		break;

		case "ClockTower_Visser_6":
			dialog.text = "航海日誌だ。あの連中ですら、記録の真似事くらいはしているはずだ――でなきゃ、ロガー船すらまともに指揮できねえからな。それに、日誌は悪事の動かぬ証拠になるし、必ず我々 の記録庫に収められる。保険の揉め事にも役立つからな\n" +
						"もし俺たちのサービスに興味があるなら、依頼主リストに空きができたぜ――最近、うちの船長の一人が契約を終えたんだ。仕事をやり遂げれば、その席はお前のものだ。";
			link.l1 = "「なぜややこしくするんだ？俺のドゥブロン金貨じゃ足りねえのか？」";
			link.l1.go = "ClockTower_Visser_7";
		break;

		case "ClockTower_Visser_7":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"、俺たちは量より質で勝負してるんだ。うちの事務所の依頼人は全員、 最高のサービスと旦那ディレクター本人の個別対応を受けられるぜ。しかも、その旦那の手間賃は、 うちみたいな貧乏じゃねえ会社でもかなりの金がかかるんだ。\n月は三十日しかねえから、三十人の依頼人しか受けられねえってわけさ。";
			link.l1 = "何をすればいい？";
			link.l1.go = "ClockTower_Visser_8";
		break;

		case "ClockTower_Visser_8":
			dialog.text = "海賊船の航海日誌を五冊持ってこい——それがお前の腕前の証明になる。報酬は、その持ち主がどれだけ危険だったかによって決まるぞ。";
			link.l1 = "わかった。やってやるぜ。";
			link.l1.go = "ClockTower_Visser_9_1";
			link.l2 = "考えさせてくれ。";
			link.l2.go = "ClockTower_Visser_9_2";
			link.l3 = "「監督本人はどこだ？」";
			link.l3.go = "ClockTower_Visser_9_3";
		break;

		case "ClockTower_Visser_9_1":
			dialog.text = "素晴らしい。結果を楽しみにしているし、我々の協力関係にも期待している。";
			link.l1 = Goodbye(true) + ".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_2":
			dialog.text = "ご希望通りに。申し出はまだ有効だぜ。\nだが、お前の席は思ったより早く奪われるかもしれねえぞ。";
			link.l1 = Goodbye(true) + ".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_3":
			dialog.text = "海上にて。ファン・ドーン旦那は事務所の管理と旗艦の指揮を兼ねている。";
			link.l1 = "どうやってそんなことをやってのけるんだ？";
			link.l1.go = "ClockTower_Visser_10";
		break;

		case "ClockTower_Visser_10":
			dialog.text = "あいつは一日に十八時間も働いてるんだ。寝るのはここ、上の階の事務所だってさ。 睡眠なんて時間の無駄だって言ってる。四時間も寝れば十分らしい。";
			link.l1 = "あの巨大な時計仕掛けの騒音はどうなんだ？ここでどうやって眠れるんだよ？";
			link.l1.go = "ClockTower_Visser_11";
		break;

		case "ClockTower_Visser_11":
			dialog.text = "自分で彼に聞けるし、何か学べるかもしれねえ。あいつはいつも客と話すのが好きなんだ。わかったか？";
			link.l1 = "完璧だ。";
			link.l1.go = "ClockTower_Visser_12";
			link.l2 = "「まだ違うな……」";
			link.l2.go = "ClockTower_Visser_12";
		break;

		case "ClockTower_Visser_12":
			dialog.text = "「ごきげんよう。」 "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;
		
		case "ClockTower_Visser_13_exit":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_2");
		break;
		
		// Йохан спрашивает про журналы
		case "ClockTower_Johan_31":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"！航海日誌は持ってきたか？";
			link.l1 = "「よく知っているようだな」 "+npchar.name+".";
			link.l1.go = "ClockTower_Johan_32";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Johan_32":
			if (!CheckAttribute(npchar, "questTemp.ClockTower_Johan_journal"))
			{
				dialog.text = "はっ！ここは波止場でも城門でもねえし、俺はただの当番の衛兵じゃなくて、会社の雇われだぜ。";
				npchar.questTemp.ClockTower_Johan_journal = true;
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"！航海日誌は持ってきたか？";
			}
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "丸太を持ってきた。通してくれるか？";
				link.l1.go = "ClockTower_Johan_33";
			}
			link.l2 = "また今度だ。";
			link.l2.go = "ClockTower_Johan_34";
		break;
		
		case "ClockTower_Johan_33":
			dialog.text = "うまくいってよかったぜ！さあ行け、みんなお前を待ってるぞ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower_2");
		break;
		
		case "ClockTower_Johan_34":
			dialog.text = "良い一日を、船長旦那。 "+GetTitle(NPChar, true)+".";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Johan_32";
		break;
		
		case "ClockTower_Visser_21":
			dialog.text = "船長！戻ったんだな。航海日誌は持ってきたか？";
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "ああ。五人全員だ。";
				link.l1.go = "ClockTower_Visser_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "また今度だ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Visser_21";
			}
			// link.l1.go = "ClockTower_Visser_36";	
			
		break;

		case "ClockTower_Visser_22":
			dialog.text = "素晴らしい。見せてくれ。\n"+
							"ああ、すべて順調だ。これは本物の海賊船だぜ。出来も上等だ。お前の取り分だ " + SellJournals() + " ドゥブロン金貨\nどうぞ、お受け取りください。それから、こちらにもご署名をお願いします。";
			link.l1 = "じゃあ、俺も名簿に載ってるのか？";
			link.l1.go = "ClockTower_Visser_23";
			//RemoveItemsFromKPTotal("ClockTower_PirateJournal", 5);	// 
		break;

		case "ClockTower_Visser_23":
			dialog.text = "ほとんど終わりだ。まずは書類の手続きをしないとな。数分かかるぜ\n"+
							"「フルネームは？」";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_24";
		break;

		case "ClockTower_Visser_24":
			dialog.text = "国籍は？";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_25";
		break;

		case "ClockTower_Visser_25":
			dialog.text = "お前の船の名前は？";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_26";
		break;

		case "ClockTower_Visser_26":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "船の種類は？";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_27";
		break;

		case "ClockTower_Visser_27":
			dialog.text = "砲門の数は？";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_28";
		break;

		case "ClockTower_Visser_28":
			dialog.text = "乗組員の人数か？";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_29";
		break;

		case "ClockTower_Visser_29":
			dialog.text = "よし。ここに署名しろ。ここにも。それから、ここにもだ。";
			link.l1 = "それだけか？";
			link.l1.go = "ClockTower_Visser_30";
		break;

		case "ClockTower_Visser_30":
			dialog.text = "ほとんど終わった。あとは君を名簿に登録するだけだ。もちろん、旦那館長が君に直接会うべきなんだが……まあ、形式的なものさ。新しい顧客を受け入れる権限は俺にあるからな\n"+
			"…しかし、また話が逸れてしまったな。さて、繰り返し利用できるサービスについてだが…\n"+
			"保険だ。高いが、会社が保険をかけた船にはどんな艦隊も手を出さねえ。港の保管庫に好きなだけ船を預けても、 植民地が包囲されてる間に失う心配はねえぞ\n"+
			"船舶監査――戦略物資を消費せずに全ての性能を少し向上させる。索具、船倉、乗組員区画まで全て点検するぜ。改善点も提案する。 料金は船の大きさ次第だ\n"+
			"我々の記録への登録。カリブ海域で船の安全性が向上するから、賞金稼ぎや海賊、 軍人たちもお前を襲う前によく考えるようになるぜ\n"+
			"特定の船について監査と登録は一度しかできないんだ。だから金を払ったなら、自分の船を大事にしろよ。 船長どもが自分の船をぞんざいに扱って、手袋みたいに次々と乗り換えるのを見ると、 俺の上司たちはどれだけ苛立つか分かってないだろうな！\n"+
			"しかし、また話が逸れてしまったな。さて、繰り返し利用できるサービスについてだが……\n"+
			"書類の差し替えだ。船にはいろんな専門分野があるってのは知ってるだろう。でもな、それが何よりもまず、 どんな書類で船を登録してるかにかかってるなんて思いもしなかっただろ？ お前の軍艦が要塞攻撃用に登録されてるのが気に入らねえなら、誰に頼めばいいか分かってるよな\n"+
			"もう知ってるだろうが、海賊船の航海日誌を渡せば報酬が出るんだぜ…海賊が危険であればあるほど、その日誌には高い金を払うぜ。";
			link.l1 = "感心したぞ。言わせてもらうが、Visser旦那、あなたの執務室は本当に……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor");
		break;

		case "ClockTower_Visser_31":
			dialog.text = "アムステルダム号が港に入ってるぞ！旦那館長が戻ってきた！";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_31_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
			ClockTower_AmsterdamInTheHarbor_2();
		break;

		case "ClockTower_Visser_31_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_32", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_32":
			dialog.text = "「何だって！？もう戻ったのか！？でも、あと三日は帰らないはずだったのに！」";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_32_add";
		break;

		case "ClockTower_Visser_32_add":
			StartInstantDialog("ClockTower_Johan_clone", "ClockTower_Visser_33", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_33":
			dialog.text = "「旦那館長はもう上陸してるぞ！まっすぐこっちに向かってきてる！」";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_33_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
		break;

		case "ClockTower_Visser_33_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_34", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_34":
			dialog.text = "おお神よ……もし彼があなたを見たら……";
			link.l1 = "「何が問題なんだ？自分で新しい依頼人を受け入れる権限があるって言ったじゃねえか。」";
			link.l1.go = "ClockTower_Visser_35";
		break;

		case "ClockTower_Visser_35":
			dialog.text = "そうだよ！でもあいつは……いや、なんでもない。船長、外で待っててくれ。入口のところだ。館長旦那があんたと話したがってるぜ。";
			link.l1 = "俺と一緒にか？";
			link.l1.go = "ClockTower_Visser_36";
		break;

		case "ClockTower_Visser_36":
			dialog.text = "彼は新しい依頼人を必ず自分で審査する。いつもだ。急いで行け！";
			link.l1 = "丸太のためにドゥブロン金貨は返さねえぞ！";
			link.l1.go = "ClockTower_Visser_36_1";
			link.l2 = "残念だな、俺は聞いていきたかったぜ。";
			link.l2.go = "ClockTower_Visser_36_2";
		break;

		case "ClockTower_Visser_36_1":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;

		case "ClockTower_Visser_36_2":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		// диалог с Йоханом, после того как мы вышли из башни
		case "ClockTower_Johan_41":
			dialog.text = "...";
			link.l1 = "「今のは何だ、ヨハン？」";
			link.l1.go = "ClockTower_Johan_42";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_42":
			dialog.text = "旦那ディレクターが戻ってきた。";
			link.l1 = "「それの何がそんなにひどいんだ？」";
			link.l1.go = "ClockTower_Johan_43";
		break;

		case "ClockTower_Johan_43":
			dialog.text = "大したことじゃない！ただ……旦那取締役は驚きが嫌いなんだ。すべて計画通りに進まなきゃならない。なのに、 まだ調査していない新しい依頼人が現れたってわけさ。";
			link.l1 = "マールテンが自分には俺を名簿に登録する権限があると言っていた。";
			link.l1.go = "ClockTower_Johan_44";
		break;

		case "ClockTower_Johan_44":
			dialog.text = "いや、そういうことじゃねえんだ。旦那館長はただ……まあ、何もかも自分で管理したがるんだよ。細かいことまで全部な。そうしねえと全部崩れるって言ってる。 今に見てろよ、また時計のことを気にし始めるぜ。";
			link.l1 = "「何だ？」";
			link.l1.go = "ClockTower_Johan_45";
		break;

		case "ClockTower_Johan_45":
			dialog.text = "ドールン旦那は苛立つと時計を止めて、いじくり始めるんだ。\n時には町中が半日も時を失うことがある。\nそして、それが起こるんだよ……";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_45_1";
		break;

		case "ClockTower_Johan_45_1":
			dialog.text = "「ああ……聞こえるか？始まったぜ。」";
			link.l1 = "ボスが戻った。いつも通りだ。";
			link.l1.go = "ClockTower_Johan_46_1";
			link.l2 = "ちゃんと聞こえるぜ。やつら、マールテンをボコボコにしてやがるな。";
			link.l2.go = "ClockTower_Johan_46_2";
			iClockSP4PseudoGlobal = ClockTower_PlaySound_rh2("Location/SP4_quest2");
		break;

		case "ClockTower_Johan_46_1":
			dialog.text = "残念だが、それが当たり前になっちまった。";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_46_2":
			dialog.text = "それはきついな。俺に言わせりゃ、不公平じゃねえか。";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";	
			ChangeCharacterComplexReputation(pchar, "nobility", -2);

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_47":
			dialog.text = "静かになったようだな。すぐに中へ招かれるだろう。";
			link.l1 = "俺はやばいのか？";
			link.l1.go = "ClockTower_Johan_48";
		break;

		case "ClockTower_Johan_48":
			dialog.text = "心配するな。お前は何も悪いことはしてねえ。";
			link.l1 = "それは心強いな。";
			link.l1.go = "ClockTower_Johan_49";
		break;

		case "ClockTower_Johan_49":
			dialog.text = "さあ、行こうぜ！旦那監督は時々厳しすぎることもあるが……でも気前が良くて礼儀正しいんだ……ほら、見てみろ？";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_50";
		break;

		case "ClockTower_Johan_50":
			dialog.text = "ああ、言っただろう！";
			link.l1 = "...";
			link.l1.go = "exit";
			ClockTower_VisserComingTowardsUs();
		break;

		case "ClockTower_Visser_37":
			dialog.text = "旦那取締役が中でお待ちです。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VisserComingTowardsUs_2");
			DelLandQuestMark(npchar);
		break;
		
		// Первое знакомство с ван Дорном
		case "ClockTower_VanDoorn_1":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+"。お前の船――『"+PChar.Ship.Name+"「、」 "+shipType+". "+GetCannonQuantity(pchar)+" 銃と "+GetMaxCrewQuantity(pchar)+" 船員。";
			link.l1 = "すべて正しい。";
			link.l1.go = "ClockTower_VanDoorn_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_VanDoorn_2":
			shipType = XI_ConvertString(GetShipTypeName(npchar));
			dialog.text = "俺があんたのことを全部知ってるのに、あんたはヨハンの噂話以外、俺のことを何も知らねえなんて不公平だよな。\nヘンドリック・ファン・ドーン。カリブのオランダ西インド会社登記部長。フリゲート艦アムステルダムの艦長だ。 "+shipType+". "+GetCannonQuantity(npchar)+" 銃と "+GetMaxCrewQuantity(npchar)+" 乗組員。";
			link.l1 = "お会いできて嬉しいです。";
			link.l1.go = "ClockTower_VanDoorn_3";
		break;

		case "ClockTower_VanDoorn_3":
			dialog.text = "お前は海賊船の航海日誌を五冊手に入れた。俺の副官はお前を高く評価し、顧客名簿に登録し、 俺の事務所のサービス内容も説明したぞ\n"+
						"だが、最終的な入団の決定はいつも俺のものだ。俺自身が、面談の後で決める。 マールテンが候補者を推薦することはできるが――それだけだ。";
			link.l1 = "始めよう。";
			link.l1.go = "ClockTower_VanDoorn_4";
		break;

		case "ClockTower_VanDoorn_4":
			if (!CheckAttribute(npchar, "ClockTower_option"))
			{
				dialog.text = "俺たちのサービスを利用できるほど商売で成功しつつ、海賊としっかり戦える船長が必要なんだ。 お前はその条件を満たしているか？";
			}
			else dialog.text = "";
			if (!CheckAttribute(npchar, "ClockTower_option_1") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				link.l1 = "俺はモーティマー・グリムを倒した。ブリッグ艦「メメント」の船長だ。";
				link.l1.go = "ClockTower_VanDoorn_option_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_2") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				link.l2 = "お前の仲間は俺がアルバート・ブラックウッドを倒したことを高く評価してくれたと思うぜ。 スノー船レディ・ベスは手強い相手だった。";
				link.l2.go = "ClockTower_VanDoorn_option_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_3") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				link.l3 = "フェルナンド・デ・アラミダは海賊じゃなかったが……";
				link.l3.go = "ClockTower_VanDoorn_option_3";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_4") && CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l4 = "俺は航海する者すべてが恐れる存在を倒したんだ。知ってるはずだぜ。";
				link.l4.go = "ClockTower_VanDoorn_option_4";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_5") && GetCharacterShipClass(PChar) <= 3)
			{
				link.l5 = "今、お前は俺の船を船籍簿に登録したばかりだ。\n無能な船長にこの船が維持できると思うか？";
				link.l5.go = "ClockTower_VanDoorn_option_5";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_6") && sti(pchar.Money) >= 1000000)
			{
				link.l6 = "俺はうまくやってるさ、カリブじゃ金なんて木になるもんだぜ。";
				link.l6.go = "ClockTower_VanDoorn_option_6";
			}
			link.l7 = "ファン・フィッサー旦那はすでに俺の腕前を認めてくれたぜ。お前の副官の評価だけじゃ足りねえのか？";
			link.l7.go = "ClockTower_VanDoorn_5";
			npchar.ClockTower_option = true;
		break;

		case "ClockTower_VanDoorn_option_1":
			dialog.text = "グリム？我々の組織はグリムについて不満を持ったことは一度もない、むしろ逆だ。\nだが、彼の後釜になった奴については……俺はそいつが誰で、もともと何の目的でカリブに来たのか知っている。\nあんな悪事に時効なんてない。お前がその犯罪者であり、我が国の真の敵を裁いてくれて嬉しいぜ。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_1 = true;
		break;

		case "ClockTower_VanDoorn_option_2":
			dialog.text = "カイマン事件の報告を正確に思い出せば、君はその主張を確認する機会がなかったはずだ。\n私の考えでは、状況は決して単純明快とは言えないが、君の勝利は間違いなく見事だった。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_2 = true;
		break;

		case "ClockTower_VanDoorn_option_3":
			dialog.text = "だが、もっとひどい存在になっていたかもしれねえ、そうだろう。奴は立派な敵だったが、お前に負けたんじゃなく、 恩知らずな上官どもにやられたのさ。俺はオランダ人だ、カスティーリャとの戦争についてはよく知ってるぜ。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_3 = true;
		break;

		case "ClockTower_VanDoorn_option_4":
			dialog.text = "「」"+GetShipName("「フライング・ハート」")+"’。あんな化け物じみた船が港に入ってきても、まともな連中が逃げ出さないのが今でも不思議だぜ。 この話には驚かされることばかりだ、船長。でもいつかは書物に記され、すべてがただの物語になるだろう。 お前については……もう自分の名を永遠に刻んだな。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_4 = true;
		break;

		case "ClockTower_VanDoorn_option_5":
			dialog.text = "驚くだろうな。\nだが、お前の場合は疑いの余地がない、それは確かだぜ。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_5 = true;
		break;

		case "ClockTower_VanDoorn_option_6":
			dialog.text = "だから価値はねえさ。もちろん、ドゥブロン金貨なら別だがな。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_6 = true;
		break;

		case "ClockTower_VanDoorn_5":
			dialog.text = "\n事務所のサービス利用が承認されたぜ。名高きオランダ西インド会社の海軍登録簿へようこそ。";
			link.l1 = "ありがとうございます。";
			link.l1.go = "ClockTower_VanDoorn_6";
		break;

		case "ClockTower_VanDoorn_6":
			dialog.text = "これは互いに利益となる協力関係だ。\nお前はカリブで最高のサービスを利用できる。\n俺たちは信頼できる仲間を得るってわけだ。";
			link.l1 = "「よし。」";
			link.l1.go = "ClockTower_VanDoorn_7";
		break;

		case "ClockTower_VanDoorn_7":
			dialog.text = "待て！聞こえるか？";
			link.l1 = "何も聞こえねえ。";
			link.l1.go = "ClockTower_VanDoorn_8";
			// sound stops
			i = FindSoundEventId("Location/clocks_mechanism_inside");
			SetSoundEventPauseState(i, true);
			DelEventHandler("NextHour", "Villemstad_BigClock_Above");
		break;

		case "ClockTower_VanDoorn_8":
			dialog.text = "まさにその通りだぜ！たった一週間離れただけで……";
			link.l1 = "何かあったのか？";
			link.l1.go = "ClockTower_VanDoorn_9";
		break;

		case "ClockTower_VanDoorn_9":
			dialog.text = "時計のことで。仕掛けを確認しなきゃならねえ。すまねえ。これは……大事なんだ。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
		break;

		case "ClockTower_VanDoorn_10":
			if (!CheckAttribute(npchar, "ClockTower_question"))
			{
				dialog.text = "今は大丈夫そうだな。改めてすまねえ。何か質問があるか？";
				LAi_Fade("", "");
				// sound returns
				i = FindSoundEventId("Location/clocks_mechanism_inside");
				SetSoundEventPauseState(i, false);
				SetEventHandler("NextHour", "Villemstad_BigClock_Above", 0);
			}
			else dialog.text = "他に質問はあるか？";
			if (!CheckAttribute(npchar, "ClockTower_question_1"))
			{
				link.l1 = "副官が事務所のサービスについて詳しく説明してくれた。どうしてこんなことが可能なんだ？";
				link.l1.go = "ClockTower_VanDoorn_question_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_2"))
			{
				link.l2 = "二つの役職をどうやって兼任するんだ？船長と監督か？";
				link.l2.go = "ClockTower_VanDoorn_question_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_3"))
			{
				link.l3 = "こんな環境でどうやって仕事をしているんだ？時計の機械音、暗闇、そして分厚いカーテンで覆われた窓。";
				link.l3.go = "ClockTower_VanDoorn_question_3";
			}
			link.l4 = "いえ、お時間をいただきありがとうございます。事務所のサービスについてはどうですか？";
			link.l4.go = "ClockTower_VanDoorn_11";
			npchar.ClockTower_question = true;
		break;

		case "ClockTower_VanDoorn_question_1":
			dialog.text = "ここに魔法なんてないぜ、船長。世界を支配するのはペンとインクだ。教会は人の誕生、洗礼、結婚、 そして死を記録する。一行でも書き換えれば、その運命も変わる。船はもう少し複雑だが、 それでもペンひとつで多くが変わるんだ。隠しはしない、俺は自分の成し遂げたことに誇りを持ってる。だが、 まだもっと良くできると分かっている。もし台帳に船や人だけじゃなく、世界そのものを書き込んだらどうなるだろうな？ ";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_1 = true;
		break;

		case "ClockTower_VanDoorn_question_2":
			dialog.text = "誰かがやらなきゃならなかったからだ。アムステルダム号の前任の船長はアンティグアの連中との戦いで戦死した。 会社はふさわしい後任を見つけられなかった。そこで俺が志願した。訓練を受け、試験に合格し、任命状を手に入れた\n"+
			"ああ、俺は貧乏な船長さ。お前よりずっとひどいのは間違いねえ。\nだが、優れた管理者は船だけじゃなく、何だって率いることができるんだ。三人を指揮するのは難しい。けど、 それを身につけたら三千人だって指揮できる。\n役所でも、船でも、町でも、でっかい会社でも――限界なんてねえさ。優秀な人材を見つけて、自分の代わりを任せてやれるならな……\nその最後が一番難しい。まさに呪いだぜ。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_2 = true;
		break;

		case "ClockTower_VanDoorn_question_3":
			dialog.text = "それに、呼吸できる空気もほとんどないんだ。船長、人間は自分自身の環境を作るものさ。 ここでは何も誰も俺を邪魔しない、すべてが手の届くところにあって、俺と時間だけのものだ。できることなら、 外の世界とは紙だけでやり取りしたいくらいだ。残念ながら、それは無理だがな。気を悪くしないでくれ、船長。 ひとりきりでも、孤独じゃない方がいい。俺の言いたいこと、わかるだろう。\n";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_3 = true;
		break;

		case "ClockTower_VanDoorn_11":
			// pchar.quest.ClockTower.date = rand(27)+1;
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "ご予約の方のみご案内しております。あなたのご予約は…… "+pchar.quest.ClockTower.date+" "+month+"。もし指定の日に来られなくても問題ない。ヨハンに連絡すれば、次の空いている予約日を教えてくれるぞ。";
			link.l1 = "「なぜそんなにややこしいんだ？」";
			link.l1.go = "ClockTower_VanDoorn_12";
		break;

		case "ClockTower_VanDoorn_12":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "我々の仕事は高額だが、それは本物の奇跡を起こし、お客様に大きな利益をもたらすからだ。\n利害の衝突はあり得ず、特定のお客様のために丸一日を割り当てている。\n次にご案内できる日程は以下の通りだ： "+pchar.quest.ClockTower.date+" "+month+"\n"+
			"もしフィッサーに会ったら……マールテンが君を推薦したのは正しい判断だったと伝えてくれ。\nそのことを必ず伝えてほしい。\n彼は優秀な副官だ。\n自分を疑わないように、とも伝えてくれ。";
			link.l1 = "「よし。」";
			link.l1.go = "ClockTower_VanDoorn_13";
		break;

		case "ClockTower_VanDoorn_13":
			dialog.text = "「ごきげんよう」 "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VanDoornInCabinet_3");
		break;
		
		case "ClockTower_Visser_41":
			dialog.text = "どうだった？";
			link.l1 = "長い一日だったが、ファン・ドールンがあなたの決断を認めてくれた。";
			link.l1.go = "ClockTower_Visser_42";
		break;

		case "ClockTower_Visser_42":
			dialog.text = "神に感謝する。これで俺は全部正しくやったんだな。";
			link.l1 = "「お前は優秀な副官だと伝えてくれ」と彼に言われた。";
			link.l1.go = "ClockTower_Visser_43";
		break;

		case "ClockTower_Visser_43":
			dialog.text = "本当か？あいつが…そう言ったのか？";
			link.l1 = "ああ。そう言ってたぜ。";
			link.l1.go = "ClockTower_Visser_44";
		break;

		case "ClockTower_Visser_44":
			dialog.text = "くそっ。あいつ、そんなこと言うんじゃねえよ。これじゃあ俺が恩知らずのクズみてえじゃねえか。……いや、もしかして全部計算づくだったのか？";
			link.l1 = "「代官旦那、急に別人みたいになったじゃねえか。」";
			link.l1.go = "ClockTower_Visser_45";
		break;

		case "ClockTower_Visser_45":
			dialog.text = "船長、俺は商人だし、あんたもそうだろう。だから手短に話そうぜ。\n"+
						 "旦那ディレクターはもう長いこと俺たちのために働いていないんだ。";
			link.l1 = "なんだって、もう一度言ってくれ！？";
			link.l1.go = "ClockTower_Visser_46";
		break;

		case "ClockTower_Visser_46":
			dialog.text = "彼はここに契約でやって来て、ただ一つの目的――船籍登録部門を設立するためだった。見事にそれを成し遂げ、後継者を育て、俺を昇進させてくれた……それで終わりだ。";
			link.l1 = "「なんだ、それだけか？」";
			link.l1.go = "ClockTower_Visser_47";
		break;

		case "ClockTower_Visser_47":
			dialog.text = "彼の契約はとっくに終わっている。\n正確な時期は分からないが、この男にその地位を保持する権利がもうないことは間違いない。";
			link.l1 = "なるほどな。この建物の中央棟にいる金持ちどもはみんなソワソワしてやがる。";
			link.l1.go = "ClockTower_Visser_48_1";
			link.l2 = "なるほどな。あいつが椅子を空けるのを待ちくたびれたってわけだ。";
			link.l2.go = "ClockTower_Visser_48_2";
		break;

		case "ClockTower_Visser_48_1":
			dialog.text = "その通りだぜ！しかも、あいつらにはどうすることもできねえんだ！";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_48_2":
			dialog.text = "率直に言うぜ。俺は本当に疲れてるんだ。くそっ、ファン・ドーンの野郎、 契約が切れた時に自分の代わりをやらせるために、わざわざ俺を昇進させやがったんだ！";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_49":
			dialog.text = "それでも、俺は騙された気がしても、あの野郎の下のこの忌々しい椅子を揺らしたりは絶対にしねえ！神よ、 俺はこの男に感謝し、敬意を抱いているんだ！";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_50";
		break;

		case "ClockTower_Visser_50":
			dialog.text = "いいや、旦那。ファン・ドーンは俺たち共通の上司どもを追い出したがってるんだ。あの塔の壁の向こう――まさにこの建物の中央棟に座ってる連中さ！だが、あいつらでさえファン・ドーンを制御する方法が見つからねえんだ！";
			link.l1 = "それの何がそんなに難しいんだ？ヴァン・ドールンなんて、スタイフェサントより大した存在じゃねえだろ。";
			link.l1.go = "ClockTower_Visser_51";
		break;

		case "ClockTower_Visser_51":
			dialog.text = "ここは船でも王宮でもないんだ、船長。俺たちの組織はまったく新しいタイプの集団だぜ。そんな貴重な人材を、 指一本で追い出すなんてできやしねえよ。\n"+
						 "まず、ファン・ドーンの契約書の原本がどこにあるか誰も知らない。つまり、解雇する根拠がないんだ。 もしやろうとしたら、奴は弁護士どもを送り込んできて、結局こっちが借りを作る羽目になるだろう。\n"+
						 "次に、経営陣はアムステルダム号の指揮権をファン・ドーンに与えたことで失敗した。 あいつは頼りない船長かもしれないが、この地域で最高の乗組員を集めたんだ。命令を出せば、 会社の精鋭兵士たちがためらいもなくこの建物を制圧するだろう。\n"+
						 "三つ目に、彼の妻は彼を心から愛しているんだ。何年も会っていなくても関係ない。デ・ウィットの娘は、 愛する夫のためなら何だってやってのける。十七人評議会もそれを認めざるを得ないのさ。\n"+
						 "今日のあの騒ぎを見ただろう、船長。秘密を教えてやるが、最近ああいうことがますます増えてるんだ。重役たちは、 いつかあいつに追い出されるんじゃないかと怯えてる。だがどうすることもできねえ、 なぜならアムステルダム号は港に停泊中だし、ファン・ドールンは自分の執務室に大事な客を抱えてるし、 家には義父である七つの連合州共和国の大年寄りが後ろ盾についてるからな！\n"+
						 "つまり、総監部はお前の協力にたっぷり報酬を払うってわけだ。\nそれに船籍登録所での特権も守ってやるぜ。";
			link.l1 = "感心したぜ。本当に商売人だな、マールテン。つい最近お前の役所のサービスを売り込んだ時と同じ手際で、 今度は裏切りを俺に売りつけてくるとはな。";
			link.l1.go = "ClockTower_Visser_57";
		break;

		case "ClockTower_Visser_57":
			dialog.text = "ヴァン・ドーン本人に交渉術を教わっていて、しかも自分の言葉を本気で信じているなら、難しいことじゃねえさ。";
			link.l1 = "それで、俺に何の用だ？";
			link.l1.go = "ClockTower_Visser_58";
		break;

		case "ClockTower_Visser_58":
			dialog.text = "よそ者にしかできねえことだ。夜に事務所へ忍び込んで、そこでファン・ドールンの元の契約書を見つけてくれ。 俺がドアの鍵は開けておくぜ。";
			link.l1 = "「なぜ自分でやらないんだ？それに、俺が今すぐお前の上司に全部話しに行くのを止める理由は何だ？」";
			link.l1.go = "ClockTower_Visser_59";
		break;

		case "ClockTower_Visser_59":
			dialog.text = "ファン・ドールンは夜なら誰でも受け入れる癖があるが、会社の従業員だけは例外だ。\nだから、この塔を不規則な時間に出ていっても誰も驚きはしないさ。";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_60";
		break;

		case "ClockTower_Visser_60":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "お前の脅しについてだが……今は監督には会えねえぞ、今日は別の予定が入ってるんだ。 "+pchar.quest.ClockTower.date+" "+month+"、そうだろう？その頃には知らせの緊急性も多少は薄れているはずだ。それに、所長は決して密告者に報酬を与えないし、 常に自分の部下を守るものさ。";
			link.l1 = "都合がいいんだな。";
			link.l1.go = "ClockTower_Visser_61";
		break;

		case "ClockTower_Visser_61":
			dialog.text = "これは裏切りじゃねえよ、船長。俺たちはただ契約を守って会社を守りたいだけだ。それに、あんたが散々 助けてくれたウィレムスタッドもな。";
			link.l1 = "考えてみるぜ。だが、何も約束はしねえ。";
			link.l1.go = "ClockTower_Visser_62";
		break;

		case "ClockTower_Visser_62":
			dialog.text = "これ以上は何も求めません、船長。何よりも、あなたは俺たちの依頼人ですから。どう転んでも、 あなたを見つけて事務所の名簿に登録したのが俺だってことを、とても誇りに思っています。";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_63";
		break;

		case "ClockTower_Visser_63":
			dialog.text = "いつでも中央棟にいるからな。良い一日を。";
			link.l1 = "また会う日まで。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Quest_3");
		break;
		
		case "ClockTower_Visser_64":
			dialog.text = "「こんにちは」 "+GetTitle(NPChar, false)+"。何か知らせはあるか？";
			link.l1 = "まだ何もない。";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_64";
		break;
		
		case "ClockTower_Johan_51":
			if (GetHour() >= 6 && GetHour() < 24)
			{
				if (pchar.quest.ClockTower.date <= GetDataDay())
				{
					NextMonth = GetDataMonth() + 1;
					if (NextMonth == 13) NextMonth = 1;
				}
				else NextMonth = GetDataMonth();
				Month = XI_ConvertString("MonthGen_" + NextMonth);
				if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"今日はお前の日だ。どうぞ、進んでくれ。";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
						
						ClockTower_RightDay();
					}
					else
					{
						dialog.text = "「ごきげんよう」 "+GetTitle(NPChar, false)+"!";
					}
				}
				else
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"、別の日に来てくれ。お前に会えるのを楽しみにしてるぜ： "+pchar.quest.ClockTower.date+" "+month+".";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					}
					else
					{
						dialog.text = "「ごきげんよう」 "+GetTitle(NPChar, false)+"!";
					}
				}
				link.l1 = "ありがとう、Johan。";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_51";
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeatnight"))
				{	// первая ночная встреча с Йоханом
					dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"、ずいぶん遅かったな。事務所はもう閉まってるぜ。";
					link.l1 = "「こんにちは」 "+npchar.name+"。夜でも動いていると聞いたぞ。";
					link.l1.go = "ClockTower_Johan_52";
					npchar.ClockTower_repeatnight = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = ""+TimeGreeting()+", "+GetTitle(NPChar, false)+"!";
					link.l1 = "";
					link.l1.go = "ClockTower_Johan_53";
				}
			}
		break;
		
		case "ClockTower_Johan_52":
			dialog.text = "そうだな。いろんな奴がここに来るぜ。時には神父まで顔を出すこともある、へっへっ。だが、 みんなまず俺を通らなきゃならねえんだ。お前については何の指示も受けてねえぞ。";
			link.l1 = "待て、お前はここで四六時中見張りをしてるのか？そんなことできるのか？";
			link.l1.go = "ClockTower_Johan_53";
		break;

		case "ClockTower_Johan_53":
			if (!CheckAttribute(npchar, "ClockTower_repeatnight_2"))
			{
				dialog.text = "ああ。旦那ディレクターが今命じたところさ。どうやってやりくりしてるのかは分からねえが、 俺にはまだ休息も仕事も両方やる時間がちゃんとあるんだ。それに給料も上げてくれた――文句はねえよ！";
				npchar.ClockTower_repeatnight_2 = true;
			}
			else
			{
				dialog.text = "他に何か？";
			}
			if (!CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
			{
				link.l1 = "通してもらおうか。俺は会社の上層部の人間だぜ。";
				link.l1.go = "ClockTower_Johan_54";
				link.l2 = "（殺せ）";
				link.l2.go = "ClockTower_Johan_KillHim";
			}
			link.l3 = "続けろ、兵士。";
			link.l3.go = "ClockTower_Johan_NightExit";
		break;
		
		case "ClockTower_Johan_KillHim":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_KillToJohan");
		break;
		
		case "ClockTower_Johan_NightExit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_Johan_51";
		break;
		
		case "ClockTower_Johan_54":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				dialog.text = "うっ。俺に何の用だ、船長旦那？俺はただの兵士だ、何も知らねえよ。";
				link.l1 = "お前は何でも知ってるじゃねえか、ヨハン。そんなに謙遜するなよ。高官どもはお前に報告しないかもしれねえが、 奴らの間のいざこざについてはきっと耳にしてるはずだろう。";
				link.l1.go = "ClockTower_Johan_55";
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
			}
			else
			{
				dialog.text = "俺は小物だが、直属の上司を飛び越えるつもりはねえ。すまねえな、 "+GetTitle(NPChar, true)+".";
				link.l1 = "この話はまた後で続けよう。";
				link.l1.go = "ClockTower_Johan_NightExit";
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
			}
		break;
		
		case "ClockTower_Johan_55":
			Achievment_Set("ach_CL_197");
			dialog.text = "「それは本当だ」 "+GetTitle(NPChar, true)+"。旦那館長は長居しすぎだ。嵐が近づいているぞ。";
			link.l1 = "具体的に何を聞いたんだ？";
			link.l1.go = "ClockTower_Johan_56";
		break;
		
		case "ClockTower_Johan_56":
			dialog.text = "誰もが恐れているんだ、今日じゃなくても明日にはあいつが権力を握るんじゃないかってな。 あいつはこの田舎には大物すぎる。検査でみんなの首を締め上げて、すべての署名を自分を通させようとするんだ\n正直に言うぜ、あんたも見ただろう？アムステルダム号が港に入るたびに、すぐに嫌な緊張が走るんだよ。";
			link.l1 = "俺がこれを解決できるが、そのためには通してもらわなきゃならねえ。";
			link.l1.go = "ClockTower_Johan_57";
		break;

		case "ClockTower_Johan_57":
			dialog.text = "「先に行け」 "+GetTitle(NPChar, true)+"。だが、頼むから俺を台無しにしないでくれよ。もし旦那監督にバレたら、首が飛ぶし、 養わなきゃならねえ家族がいるんだ。";
			link.l1 = "全力を尽くすぜ。";
			// if (sti(pchar.reputation.nobility) >= 71) link.l1.go = "ClockTower_Johan_58_hint";
			// else link.l1.go = "ClockTower_Johan_NightSuccess";
			link.l1.go = "ClockTower_Johan_58_hint";
		break;

		case "ClockTower_Johan_58_hint":
			ClockTower_AddBook();
			dialog.text = "「お前はいい奴だ」 "+GetTitle(NPChar, true)+"。もしかしたら俺が手伝えるかもしれねえ：総督旦那が持ってる本の一冊に鍵が隠されてるって知ってるんだ。 それが何のための鍵かは知らねえが、もしかしたら役に立つかもしれねえ。";
			link.l1 = "ありがとう、Johan。";
			link.l1.go = "ClockTower_Johan_NightSuccess";
			// if (sti(pchar.reputation.nobility) >= 71) Notification_Reputation(true, 71, "low");
		break;
		
		case "ClockTower_Johan_NightSuccess":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_NightFree");
			NextDiag.CurrentNode = "ClockTower_Johan_51";
			// if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
		break;
		
		case "ClockTower_Peter_50":
			dialog.text = "止まれ。ここはオランダ西インド会社の所有地だ。\n海軍登記部と記録保管所だぞ。\n立ち入りは予約者のみだ。";
			link.l1 = "俺は "+GetTitle(NPChar, false)+" "+pchar.name+".";
			link.l1.go = "ClockTower_Peter_51";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_51":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "予約があるのか？進みな。";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					
					ClockTower_RightDay();
				}
				else
				{
					dialog.text = "...";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "あなたの予約は別の日に予定されています： "+pchar.quest.ClockTower.date+" "+month+".";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = "...";
				}
			}
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Peter_51";
		break;
		
		case "ClockTower_Visser_71":
			dialog.text = "「こんにちは」 "+GetTitle(NPChar, false)+"。何か知らせはあるか？";
			link.l1 = "ああ。これが契約書だ。";
			link.l1.go = "ClockTower_Visser_72";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_72":
			dialog.text = "信じられねえ……七年前に期限が切れてるじゃねえか！";
			link.l1 = "これが欲しかったものか？";
			link.l1.go = "ClockTower_Visser_73";
		break;

		case "ClockTower_Visser_73":
			dialog.text = "その通りだ！この書類があれば会社は正式に彼を召還できる。抜け道はない。言い訳もできない。時間切れ――以上だ。";
			link.l1 = "次はどうする？";
			link.l1.go = "ClockTower_Visser_74";
		break;

		case "ClockTower_Visser_74":
			dialog.text = "契約書はアムステルダムに送る。十七人評議会が決定を下すだろう。ドーンには帰還命令が出される。奴は断れねえさ。";
			link.l1 = "もし彼が断ったらどうする？";
			link.l1.go = "ClockTower_Visser_75";
		break;

		case "ClockTower_Visser_75":
			dialog.text = "彼にはできない。妻は株主である大年寄の娘かもしれないが、彼女の父親でさえ評議会には逆らえないんだ。 そしてカタリナ自身も……彼女は十年も待ち続けている。もし彼が帰れるのに拒んでいると知ったら――彼女はきっと耐えられないだろう。";
			link.l1 = "残酷だ。";
			link.l1.go = "ClockTower_Visser_76";
		break;
		
		case "ClockTower_Visser_76":
			dialog.text = "ああ、しかしこれしか方法がないんだ。ありがとう、船長。大事な仕事をしてくれたな。";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_77";
		break;
		
		case "ClockTower_Visser_77":
			if (CharacterIsAlive("ClockTower_Johan"))
			{
				dialog.text = "報酬は五百ドゥブロンだ。\nそれと約束しよう――二、三か月後に俺が所長の座に就いたら、お前には事務所のサービスを無制限で使わせてやる。\n行列もなし、予約も不要、いつでも好きな時にだ。";
				AddItems(pchar, "gold_dublon", 500);
			}
			else
			{
				dialog.text = "それにお前はヨハンを殺した。俺はすでに尊敬し、全てを捧げた男を裏切ったんだ。今度はこれか\n"+
				"お前の船では人間が薪みたいなものかもしれないが、会社は従業員を大事にしているんだ。殺人に加担するなんて、 俺は本当にうんざりだ\n"+
				"お前のドゥブロンはヨハンの家族に渡すが、取引のもう一つの約束は俺が果たすぜ\n"+
				"俺が約束するぜ：二、三か月後に俺が所長の座に就いたら、お前には事務所のサービスを無制限に利用させてやる。";
			}
			link.l1 = "お前の言葉を信じてるぜ。では、良い一日を。";
			link.l1.go = "ClockTower_Visser_78";
		break;
		
		case "ClockTower_Visser_78":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_WaitFewMonths");
		break;
		
		case "ClockTower_Visser_79":
			dialog.text = "「こんにちは」 "+GetTitle(NPChar, false)+"。まだ知らせはない。心配するな、俺は約束を覚えているぜ。";
			link.l1 = "そうだといいんだが。";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_79";
		break;
		
		case "ClockTower_Visser_81":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"！入ってくれ、入ってくれ。会えて嬉しいぜ。";
			link.l1 = "ご就任おめでとうございます。";
			link.l1.go = "ClockTower_Visser_82";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_82":
			dialog.text = "ありがとうございます。十七人評議会は思ったより早く決断を下しました。契約書が十分な証拠となりました。 ファン・ドールン旦那は事務所の管理から外されました。";
			link.l1 = "「彼はどう受け止めた？」";
			link.l1.go = "ClockTower_Visser_83";
		break;

		case "ClockTower_Visser_83":
			dialog.text = "奴は負け方を知っている。自分の私物を事務所からまとめて、さっさと出て行った。だが、本当に負けたのか？\n"+
			"アムステルダム号の指揮権は彼のままだった。その点で、会社は確かに失敗したんだ。あの時、 彼にあの船を与えるべきじゃなかったんだよ。\n"+
			"俺たちはあいつを甘く見てたんだ。結局、事態がもっと悪くならなきゃいいがな\n"+
			"それだけじゃねえ。";
			link.l1 = "「これ以上悪くなることがあるのか？」";
			link.l1.go = "ClockTower_Visser_84";
		break;

		case "ClockTower_Visser_84":
			dialog.text = "ファン・ドールン旦那は誰が自分の執務室から契約書を持ち出したか知っている。";
			link.l1 = "どうして！？";
			link.l1.go = "ClockTower_Visser_85";
		break;

		case "ClockTower_Visser_85":
			dialog.text = "そんな目で俺を見るな！俺は何も言ってねえ。あいつが自分で気づいたんだ。";
			link.l1 = "これからどうする？";
			link.l1.go = "ClockTower_Visser_86";
		break;

		case "ClockTower_Visser_86":
			dialog.text = "今や彼はお前を敵と見なしている。だが、七つの連合州共和国に脅威を与えない限り――手出しはしないだろう\n"+
			"ファン・ドーンはいつも私情と仕事をきっちり分けていた。\n問題は、お前にそれができるかどうかだ。";
			link.l1 = "もし俺にできなかったらどうする？";
			link.l1.go = "ClockTower_Visser_87";
		break;

		case "ClockTower_Visser_87":
			dialog.text = "そしたら、あいつが来るぜ。そして仕事を果たす。理由を与えるんじゃねえぞ。";
			link.l1 = "やってみるぜ。";
			link.l1.go = "ClockTower_Visser_88";
		break;

		case "ClockTower_Visser_88":
			dialog.text = "「ごきげんよう。」 "+GetTitle(NPChar, false)+"……どうぞご遠慮なく、我々……いや、私の執務室をいつでもご利用ください。";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VillemstadStreet");
		break;
		
		case "ClockTower_Johan_61":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"、お待ちしておりました。フィッサー旦那が全ての客を自由に入れるように命じました。昔の規則は厳しすぎたそうです。 ";
			link.l1 = "ありがとう、Johan。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_61":
			dialog.text = "営業時間内ならいつでもどうぞ。\n予約制度は廃止された。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Helena_1":
			dialog.text = "ちょっと時間あるか？";
			link.l1 = "お前のためなら――いつでもだ。";
			link.l1.go = "ClockTower_Helena_2";
		break;

		case "ClockTower_Helena_2":
			dialog.text = "ああ、もしそうなら、俺の船長。あんたには他にも夢中になるものがあるだろう。たとえば今だって、 あんたのそのイカした頭の中は俺以外の誰かでいっぱいなんじゃねえか？";
			link.l1 = "...";
			link.l1.go = "ClockTower_Helena_3";
		break;

		case "ClockTower_Helena_3":
			dialog.text = "そう思ったんだ。俺は自分の部下のことはよく知ってるからな。それに水夫の興奮なんて、もっとよく知ってるぜ。 だから、はっきり言ってくれよ、可愛い子ちゃん\n"+
			"「名高いオランダ西インド会社の旗艦を拿捕するのに、俺たちにはどれほどの代償が必要だ？」";
			link.l1 = "ファン・ドールンが自ら俺たちのところに来るためには、俺がウィレムスタッドの敵にならなきゃならねえ。";
			link.l1.go = "ClockTower_Helena_4";
		break;

		case "ClockTower_Helena_4":
			dialog.text = "ああ、俺の船長……そういうことになるのか。これが初めてじゃねえよな？";
			link.l1 = "まるでお前が認めてないみたいじゃねえか。";
			link.l1.go = "ClockTower_Helena_5";
		break;

		case "ClockTower_Helena_5":
			dialog.text = "俺はありのままのお前に惚れたんだ。これからもずっとお前の味方だぜ。\nただ、俺たち……いや、お前が民の前で背負う責任の重さを忘れるなよ。";
			link.l1 = "それはアロンソの役目だ。あいつがちゃんと思い出させてくれるさ。";
			link.l1.go = "ClockTower_Helena_6";
		break;

		case "ClockTower_Helena_6":
			dialog.text = "出航しだいすぐにですよ、船長。";
			link.l1 = "じゃあ、ぐずぐずしていられないわね、あなた。";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Mary_1":
			dialog.text = "「チャールズ？ちょっと聞きたいことがあるんだ。」";
			link.l1 = "もちろんだ、メアリー。何があったんだ？";
			link.l1.go = "ClockTower_Mary_2";
		break;

		case "ClockTower_Mary_2":
			dialog.text = "俺……お前のことが心配なんだよ。あの顔つき、知ってるぜ。何か悪いことを考えてるんだろう。";
			link.l1 = "馬鹿なことを言うな。俺はさっき自分が何を考えていたかすら覚えてねえんだぜ。お前に分かるわけがねえだろう？";
			link.l1.go = "ClockTower_Mary_3";
		break;

		case "ClockTower_Mary_3":
			dialog.text = "俺は知ってるんだよ！アムステルダム号をちゃんと見たぜ。美しい船だった。ほんとに美しかった。だが\n"+
			"もう全部決めてあるんだな……前と同じでいいんだろう？";
			link.l1 = "ファン・ドーンが自ら俺たちのところへ来るだろうが、そのためにはウィレムスタッドの敵にならなきゃならねえ。";
			link.l1.go = "ClockTower_Mary_4";
		break;

		case "ClockTower_Mary_4":
			dialog.text = "「それだけの価値があるのか、チャールズ？」";
			link.l1 = "わからないよ、メアリー。";
			link.l1.go = "ClockTower_Mary_5";
		break;

		case "ClockTower_Mary_5":
			dialog.text = "お前に幸せになってほしいんだ、いいか。でもな、それでもアロンソにお前を思いとどまらせるよう頼んでみるぜ、 いいな！";
			link.l1 = "あいつらしいな。行こうぜ、愛しい人よ。";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Girl_End":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Girl_DlgExit");
		break;
		
		case "ClockTower_Alonso_1":
			dialog.text = "船長、話があるんだ。";
			link.l1 = "聞いてるぜ。";
			link.l1.go = "ClockTower_Alonso_2";
			link.l2 = "今はだめだ、Alonso。";
			link.l2.go = "ClockTower_Alonso_2";
		break;

		case "ClockTower_Alonso_2":
			dialog.text = "こういうことなんだ、船長、でも最後まで聞いてくれよ。えっと、その、なんて言うか\n"+
			"急用――それだ！\n"+
			"なるほどな、小耳に挟んだぜ。お前が会社の重役の一人をぬくぬくした椅子から引きずり下ろしたってな。 そいつは根に持って、今じゃ立派なフリゲートで俺たちを追い回してるってわけだ。";
			link.l1 = "それは大げさすぎるぜ。";
			link.l1.go = "ClockTower_Alonso_3";
		break;

		case "ClockTower_Alonso_3":
			dialog.text = "人は噂話が大好きだろ、船長。噂を一週間も放っておけば、ヴァン・ドーンは農園主の娘に誘惑されたとか、 アムステルダム号には生ける屍の乗組員がいるとか、船倉にはコルテス本人の財宝が眠ってるなんて話が聞こえてくるぜ\n"+
			"だが、俺が知りたいのは本当の状況だぜ。さて、船長、やるのかやらねえのか？";
			link.l1 = "...";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Томми
			{
				link.l1.go = "ClockTower_Alonso_4_1";
			}
			else
			{
				link.l1.go = "ClockTower_Alonso_4_5";
			}
		break;
		
		case "ClockTower_Alonso_4_1":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin");
		break;
		
		case "ClockTower_Alonso_4_2":
			dialog.text = "ところで、それは血が騒ぐほど面白そうだぜ、文句は言わねえ！オランダの旗艦だ！ははっ！ あのチーズ野郎どものツラを想像してみろよ、俺たちが……\n";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_3";
		break;
		
		case "ClockTower_Alonso_4_3":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin_2");
		break;
		
		case "ClockTower_Alonso_4_4":
			dialog.text = "「トミー、黙れ。」";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_5";
		break;
		
		case "ClockTower_Alonso_4_5":
			dialog.text = "...";
			link.l1 = "戦いになるとしても、すぐには起こらねえさ。ファン・ドールンは復讐なんて考えねえ男だ。 まずはオランダ人を本気で怒らせなきゃならねえな。";
			link.l1.go = "ClockTower_Alonso_4_6";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "ClockTower_Alonso_4_6":
			dialog.text = "ありがとう、船長、それで船員たちも安心するだろう。";
			link.l1 = "お前は？";
			link.l1.go = "ClockTower_Alonso_5";
		break;
		
		case "ClockTower_Alonso_5":
			dialog.text = "俺の心配は乗組員を守ることだ。奴ら自身からも……できればお前からもな。どうせお前は自分の計画通りに動くんだろうが。";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Томми
			{
				link.l1 = "...";
				link.l1.go = "ClockTower_Alonso_5_add";
			}
			else
			{
				link.l1 = "続けてくれ、Alonso。";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
			}
		break;
		
		case "ClockTower_Alonso_5_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_6", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;
		
		case "ClockTower_Alonso_6":
			dialog.text = "スペインのラバみたいに頑固だな！";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_6_add";
		break;
		
		case "ClockTower_Alonso_6_add":
			StartInstantDialogTurnToNPC("ClockTower_Alonso", "ClockTower_Alonso_7", "Quest\ShipsPack\ClockTower_dialog.c", "Irons");
		break;
		
		case "ClockTower_Alonso_7":
			dialog.text = "「主よ、なぜ私なのだ。」";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_7_add";
		break;
		
		case "ClockTower_Alonso_7_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_8", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_8":
			dialog.text = "全部ややこしくしすぎだぜ！船長は立派な船が欲しいんだ――だったら立派な船を手に入れるだけさ！俺たちは一つのクルーだろう！";
			link.l1 = "続けろ、アルフォンソ。トミー、出ていけ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
		break;
		
		// Абордаж Амстердама, перед боем с Ван Дормом
		case "ClockTower_VanDoorn_21":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+"。お前の船――『"+PChar.Ship.Name+"「」、 "+shipType+". "+GetCannonQuantity(pchar)+" 銃と "+GetMaxCrewQuantity(pchar)+" 船員。";
			link.l1 = "「相変わらずお見事ですね、ディレクター旦那。」";
			link.l1.go = "ClockTower_VanDoorn_22";
		break;

		case "ClockTower_VanDoorn_22":
			dialog.text = "その称号はもう俺のものじゃねえ――お前の活躍のおかげだ。だが、俺がちっぽけな復讐心でお前を襲ったなんて思うなよ。俺は自分の仕事をしていただけだ。 \n"+
			"そして、当然ながら失敗した。俺には成功なんてできなかったさ。前にも言ったが、 お前のほうが俺よりずっと優れた船長だ。";
			link.l1 = "自分でこの重荷を背負ったんだろう！お前の契約は七年前に切れてる。なぜ素直に家に帰らなかったんだ？";
			link.l1.go = "ClockTower_VanDoorn_23";
		break;

		case "ClockTower_VanDoorn_23":
			dialog.text = "お前が同じことをしない理由は何だ？答えは分かっているだろう、船長。お前には夢がある。他の人生なんてないんだ。 そして、もし自分を制御するのをやめたら――すべてが崩れちまうんだ。\n"+
			"俺がこの地に秩序をもたらすこともできたはずだ。終わりなき暴力の連鎖を止められたかもしれねえ。 もし俺が手綱を緩めなければ――もし恐怖を押し潰して、とっくの昔にやるべきことをやっていればな。\n"+
			"だが、感傷はもうたくさんだ。俺は船長としても戦士としても腕はからっきしだが、部下を選ぶ目だけはあるんだぜ。 お前を俺の最後の仕事にした、船長。今日で役所の名簿から船長が二人減ることになるぞ！";
			if (CheckCharacterItem(PChar, "CatharinaLetter"))
			{
				link.l1 = "恐怖について何か言っていたな。じゃあ、この手紙を読んでみろ。"; // Доступно, если игрок принёс письмо
				link.l1.go = "ClockTower_VanDoorn_24";
			}
			link.l2 = "一人だけだ。戦闘開始だ！"; // бой
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_24":
			dialog.text = "カタリナからだと！？仕事と私情を混ぜるなんて、どういうつもりだ！？";
			link.l1 = "ご覧の通り、手紙はまだ封がされています。私は待っています。";
			link.l1.go = "ClockTower_VanDoorn_25";
			TakeItemFromCharacter(pchar, "CatharinaLetter");
			pchar.questTemp.ClockTower_GaveCatharinaLetter = true;
		break;

		case "ClockTower_VanDoorn_25":
			dialog.text = "…もう待てない…他の男のところへ行ってしまう…俺が戻らなければ！？";
			link.l1 = "お前はもうその地位を失った。今まさに仲間たちが死んでいるんだ。\n家族まで失う覚悟はできているのか？";
			link.l1.go = "ClockTower_VanDoorn_26";
		break;

		case "ClockTower_VanDoorn_26":
			dialog.text = "こんなのは嫌だ。船長、俺の降伏を受け入れてくれるか？";
			link.l1 = "ああ。俺の船からとっとと失せろ。"; // Отпускает, повышает честь
			link.l1.go = "ClockTower_VanDoorn_27";
			link.l2 = "いや、それが死刑囚への最後の礼儀だった。戦闘だ！"; // бой
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_27":
			dialog.text = "それでは、ご勝利おめでとうございます、船長 "+GetFullName(pchar)+"。今日、船籍簿からは船長が一人減るだけだ。";
			link.l1 = "...";
			link.l1.go = "ClockTower_cabinPeace";
			GiveItem2Character(PChar, "pistol15");
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE); // нужно два раза, чтобы сработало...
			TakeItemFromCharacter(npchar, "pistol15");
		break;
		
		// Финальный диалог с Маартеном
		case "ClockTower_Visser_101":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+"。ここに来るとは思わなかったぜ。";
			link.l1 = "なぜだ？俺はまだお前の依頼人だし、事務所のサービスが必要なんだ。";
			link.l1.go = "ClockTower_Visser_102";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_102":
			dialog.text = "「用事だと？用事だとぉ！？お前がやったことの後で？お前は名高いオランダ西インド会社の敵だ！ 別の船長がその依頼主の席を奪うことになるぞ！」";
			link.l1 = "ありえねえな。見ろよ、俺がファン・ドールンの書類で見つけたものを。";
			link.l1.go = "ClockTower_Visser_103";
		break;
		
		case "ClockTower_Visser_103":
			dialog.text = "...";
			link.l1 = "「お前の前任者は、この書類を使うのは自分の威厳に関わると思っていた――椅子がぐらつき始めてもな。」";
			link.l1.go = "ClockTower_Visser_104";
			// отдаём Ключ к Маартену Виссеру
			TakeItemFromCharacter(pchar, "Visser_Key");
		break;
		
		case "ClockTower_Visser_104":
			dialog.text = "...";
			link.l1 = "お前は運が良かったな、そんな上司がいてさ。そんな悪ふざけをしたら、普通なら裁判にかけられるところだぜ――せいぜいな。";
			link.l1.go = "ClockTower_Visser_105";
		break;
		
		case "ClockTower_Visser_105":
			dialog.text = "...";
			link.l1 = "あんたは商売人だろう。俺が何を言いたいか分かるよな。";
			link.l1.go = "ClockTower_Visser_106";
		break;
		
		case "ClockTower_Visser_106":
			dialog.text = "お前……名簿への登録は元に戻ったぞ。";
			link.l1 = "ああ、マールテン。お前は所長の座を狙っていたが、あいつはお前に全てを与えてくれたんだ。裁判から救い出し、 お前に知らせる必要すらないと思っていたのさ。";
			link.l1.go = "ClockTower_Visser_107";
		break;
		
		case "ClockTower_Visser_107":
			dialog.text = "...";
			link.l1 = "この小さな罪が、お前を決して上へは行かせず、絶えず恐れの中で生きさせるだろう。";
			link.l1.go = "ClockTower_Visser_108";
		break;
		
		case "ClockTower_Visser_108":
			dialog.text = "...";
			link.l1 = "今度はお前がこの場所に縛り付けられる番だ。だが、ファン・ドーンが持っていたような副官は、 お前には絶対にいないぜ。";
			link.l1.go = "ClockTower_Visser_109";
		break;
		
		case "ClockTower_Visser_109":
			dialog.text = "もういい。俺をとことん始末したいのか！？";
			link.l1 = "違うんだ。俺の新しい船を登録簿に載せてほしいんだ。誤解が生じるのは困るからな。";
			link.l1.go = "ClockTower_Visser_110";
		break;
		
		case "ClockTower_Visser_110":
			dialog.text = "お前の船は『"+GetShipName("Amsterdam")+"「…DWICの旗艦だ。そんな簡単に…再登録できるはずがねえ。」";
			link.l1 = "なぜだ？紙は何でも耐えるからな。お前たちのやり方ってそういうもんじゃねえのか？";
			link.l1.go = "ClockTower_Visser_111";
		break;
		
		case "ClockTower_Visser_111":
			dialog.text = "おお神よ、だが何事にも限度ってもんがあるだろう！";
			link.l1 = "俺はこの場所の力を信じてるぜ。お前も信じるべきだ。";
			link.l1.go = "ClockTower_Visser_112";
		break;
		
		case "ClockTower_Visser_112":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_113";
		break;
		
		case "ClockTower_Visser_113":
			dialog.text = "「フルネームは？」";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_114";
		break;
		
		case "ClockTower_Visser_114":
			dialog.text = "「臣籍か？」";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_115";
		break;

		case "ClockTower_Visser_115":
			dialog.text = "お前の船の名前は？";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_116";
		break;

		case "ClockTower_Visser_116":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "船の種類は？";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_117";
		break;

		case "ClockTower_Visser_117":
			dialog.text = "砲門の数は？";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_118";
		break;

		case "ClockTower_Visser_118":
			dialog.text = "乗組員の人数は？";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_119";
		break;

		case "ClockTower_Visser_119":
			dialog.text = "よし。ここに署名しろ。ここにも。ここにもだ。";
			link.l1 = "それだけか？";
			link.l1.go = "ClockTower_Visser_120";
		break;
		
		case "ClockTower_Visser_120":
			dialog.text = "それで終わりだ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Visser_pausa_1");
		break;
		
		case "ClockTower_Visser_121":
			dialog.text = "...";
			link.l1 = "何か言い忘れてるぞ。";
			link.l1.go = "ClockTower_Visser_122";
		break;
		
		case "ClockTower_Visser_122":
			dialog.text = "\n"+
			"「名高いオランダ西インド会社の海軍登録簿へようこそ。」";
			link.l1 = "また会う日まで、ディレクター旦那。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FINAL");
		break;
		

		//------------------Услуги конторы------------------//
		case "ClockTower_OfficeServices":
			if (npchar.id == "ClockTower_VanDoorn")
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.name+"。今日は私と私の役職に、どのようなご用件でしょうか？";
			}
			if (npchar.id == "ClockTower_Visser")
			{
				if (CharacterIsAlive("ClockTower_VanDoorn"))
				{
					dialog.text = "会えて嬉しいぜ。 "+GetTitle(NPChar, false)+"！いつでもお役に立ちますぜ。今日は何にご興味があるんだ？";
				}
				else
				{
					dialog.text = "どうした？今日は何に興味があるんだ？";
				}
			}
			link.l1 = "俺の船の監査をしてくれるか？性能を向上させたいんだ。";
			link.l1.go = "ClockTower_OfficeServices_audit"; // Аудит
			link.l2 = "俺の船の専門分野には満足してねえ。新しい書類を手配してくれるか？";
			link.l2.go = "ClockTower_OfficeServices_changeTrait"; // Смена документов
			link.l3 = "俺の船を船籍簿に登録してくれるか？海賊や賞金稼ぎどもに二の足を踏ませてやろうぜ。";
			link.l3.go = "ClockTower_OfficeServices_buffSpec"; // Занесение в реестр
			if (!CheckAttribute(pchar, "questTemp.ShipInsurance"))
			{
				link.l4 = "港の保管庫にある俺の船を保険に入れたいんだ。今ある船も、これから手に入れる船もな。";
				link.l4.go = "ClockTower_OfficeServices_Insurance"; // Страховка (пропадает после оплаты)
			}
			if(!CheckAttributeEqualTo(npchar, "last_logbook_date", LastSpeakDate()) && ClockTower_JournalsQty() > 0)
			{
				link.l5 = "お前は海賊船長たちの航海日誌を受け取るんだろう？";
				link.l5.go = "ClockTower_OfficeServices_logbook"; // Награда за пиратов (раз в сутки)
			}
			link.l6 = "今日は無理かもしれねえな。では、良い一日を。";
			link.l6.go = "ClockTower_OfficeServices_exit"; // Отказ
		break;

		// --> Аудит
		case "ClockTower_OfficeServices_audit":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "費用は船の大きさによって変わるぜ。どの船のことを言ってるんだ？";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.Audit")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}
 
			if (n == 0)
			{
				dialog.text = "残念だが、監査は各船ごとに一度きりのサービスだ。他に何かあるか？";
				link.l1 = "また今度にしよう。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "Audit"))
			{
				n = GetAuditShipCost(sld);
				dialog.text = "そうだな……これは費用がかかるぜ " + n + " ドゥブロン金貨。";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "進め。";
					link.l1.go = "ClockTower_OfficeServices_audit_upgradeShip";
				}
				link.l2 = "……まあ、また今度にしようぜ。";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "申し訳ありませんが、お断りしなければなりません。記録によれば、 あなたの船は何年も前に海の悪魔のもとへ行ってしまい、時の亡霊は書類一枚で元に戻せるものではありません。 協力する前に、まずその船を復元していただく必要があります。イスラ・テソロには、 そういった仕事を引き受ける名人がいると聞いています。";
				link.l1 = "「ああ、ありがとう。」";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$すでに船は強化されている";
				link.l1 = "ありがとうございます。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetAuditShipCost(sld));
			UpgradeShipAudit(sld);
			dialog.text = "完了した。";
			link.l1 = "ありがとうございます。";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;
		// <-- Аудит

		// --> Улучшение специализации
		case "ClockTower_OfficeServices_buffSpec":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "費用は船の大きさによって変わるぜ。どの船のことを言ってるんだ？";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "残念ながら、登録は各船ごとに一度きりのサービスだ。他に用はあるか？";
				link.l1 = "また今度にしよう。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "SpecialityUpgrade"))
			{
				n = GetSpecialityUpgradeShipCost(sld);
				dialog.text = "そうだな……これは費用がかかるぜ " + n + " ドゥブロン金貨だ。";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "進め。";
					link.l1.go = "ClockTower_OfficeServices_buffSpec_upgradeShip";
				}
				link.l2 = "……まあ、また今度にしよう。";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "申し訳ありませんが、お断りしなければなりません。記録によれば、 あなたの船は何年も前に海の悪魔のもとへ行ってしまい、時の亡霊は書類一つで元に戻せるものではありません。 協力する前に、まずその船を復元する必要があります。イスラ・テソロには、 そういった仕事を引き受ける名人がいると言われています。";
				link.l1 = "「ああ、ありがとう。」";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$船はすでに強化されている";
				link.l1 = "ありがとうございます。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetSpecialityUpgradeShipCost(sld));
			UpgradeShipSpeciality(sld);
			dialog.text = "完了した。";
			link.l1 = "ありがとうございます。";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;
		// <-- Улучшение специализации

		// --> Смена трейта корабля
		case "ClockTower_OfficeServices_changeTrait":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "費用は船の大きさによって変わるぜ。どの船のことを言ってるんだ？";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				sTemp = "";
				ShipTraitCanBeChanged(sld, &sTemp);
				if (sTemp == "EmptyShip" || sTemp == "QuestCompanion") continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "ふむ。港にお前の船は一隻も見当たらねえな。";
				link.l1 = "また今度にしよう。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";

			if (ShipTraitCanBeChanged(sld, &sTemp))
			{
				n = GetChangeShipTraitCost(sld);
				dialog.text = "そうだな……これは費用がかかるぜ " + n + " ドゥブロン金貨だ。";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "進め。";
					link.l1.go = "ClockTower_OfficeServices_changeTrait_upgradeShip";
				}
				link.l2 = "……まあ、また今度にしようぜ。";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "QuestSP")
			{
				dialog.text = "残念だが、それは無理だ。お前の船は伝説に彩られた唯一無二の品だぜ。こういう場合、 書類一枚じゃどうにもならねえんだよ。";
				link.l1 = "「ああ、ありがとよ。」";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else
			{
				dialog.text = "どんな特化のことを言ってるんだ？お前の船は万能型で、これといった特徴はねえぞ。";
				link.l1 = "知れてよかった、ありがとう。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			// тут можно обработать другие причины отказа, но на данный момент таковых не будет
		break;

		case "ClockTower_OfficeServices_changeTrait_upgradeShip":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
			DialogExit();
			LaunchChangeShipTraitScreen(sld);
		break;
		// <-- Смена трейта корабля

		// --> Страховка
		case "ClockTower_OfficeServices_Insurance":
			n = GetInsuranceCost();
			dialog.text = "そうだな……これは費用がかかるぜ " + n + " ドゥブロン金貨だ。";
			if (PCharDublonsTotal() > n)
			{
				link.l1 = "進め。";
				link.l1.go = "ClockTower_OfficeServices_Insurance_done";
			}
			link.l2 = "……まあ、また今度にしよう。";
			link.l2.go = "ClockTower_OfficeServices_exit";
		break;

		case "ClockTower_OfficeServices_Insurance_done":
			pchar.questTemp.ShipInsurance = true;
			RemoveDublonsFromPCharTotal(GetInsuranceCost());
			dialog.text = "完了した。";
			link.l1 = "ありがとうございます。";
			link.l1.go = "ClockTower_OfficeServices_exit";
			Achievment_Set("ach_CL_199");
		break;
		// <-- Страховка
		
		// Награда за пиратов (раз в сутки) -->
		case "ClockTower_OfficeServices_logbook":
			dialog.text = "まったくその通りだ。報酬は航海日誌の数と、その持ち主の危険度によって決まるんだぜ。\n" + 
						  "「何本の丸太を持ってきた？」"
			link.l1 = "" + ClockTower_JournalsQty();
			link.l1.go = "ClockTower_OfficeServices_logbook_1";
		break;
		
		case "ClockTower_OfficeServices_logbook_1":
			dialog.text = "会社はあなたの働きに感謝している。あなたには報酬がある\n " + JournalsCost() + " ドブロン金貨です。どうぞお受け取りになり、ここに署名してください"
			link.l1 = "ありがとうございます。";;
			link.l1.go = "ClockTower_OfficeServices_exit";
			npchar.last_logbook_date = LastSpeakDate();
			Achievment_Set("ach_CL_199");
		break;
		// <-- Награда за пиратов

		case "ClockTower_OfficeServices_exit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
		break;

		case "ClockTower_cabinFight":
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			ClockTower_CabinFight2();
		break;
		
		case "ClockTower_cabinPeace":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_cabinPeace");
		break;
	}
}

void ClockTower_NoShipInPort(ref link)
{
	dialog.text = "港にお前の船は見当たらねえな。";
	link.l1 = "また今度にしようぜ。";
	link.l1.go = "ClockTower_OfficeServices_exit";
}

int ClockTower_PlaySound_rh2(string name)
{
    float x = stf(loadedLocation.locators.reload.houseO2.x);
    float y = stf(loadedLocation.locators.reload.houseO2.y);
    float z = stf(loadedLocation.locators.reload.houseO2.z);
    return SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, name, 0, x, y, z);
}
