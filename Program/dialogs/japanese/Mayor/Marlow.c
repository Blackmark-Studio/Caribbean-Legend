// Захария Марлоу, Чёрный Пастор, Пуэрто-Принсипе, Куба
int iMarlowTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                    if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    } //<-- блок angry

	switch(Dialog.CurrentNode)
	{
		case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("気でも狂ったのか？屠殺屋ごっこがしたかったのか？海賊どもはみんなお前に怒ってるぜ、坊主、 さっさとここから出ていったほうがいいぞ…","どうやらお前、頭がおかしくなったみたいだな、坊主。ちょっと腕を伸ばしたかったのか？悪いが、 ここはお前の来る場所じゃねえ。とっとと失せろ！");
				link.l1 = RandPhraseSimple("聞けよ、この状況を何とかしたいんだ…","この問題を解決するのを手伝ってくれ…");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+"、私は" + GetSexPhrase("","") + " 海での安全について話したいんだ。沿岸の兄弟団の連中が、私のつつましい身に過剰な興味を示しているんだ。 少し黙らせてもらえないか？";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("俺に言いたいことでもあるのか？ないのか？だったらさっさと失せろ！",
						"はっきり言ったはずだ、これ以上俺をイラつかせるな。","はっきり言ったはずだが、しつこく俺を苛立たせやがって！",
						"ああ、もうこの無礼にはうんざりだぜ。","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("もう行くぜ。",
						"ああ、"+npchar.name+"……",
						"悪いな、"+npchar.name+"…",
						"「いてっ……」",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
			{
				link.l1 = "俺はシャーク・ドッドソンを探してるんだ。あんたが最後に奴を見たって聞いたぜ。協力してくれるか？";
				link.l1.go = "Shark";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
			{
				link.l1 = "なんでそんなに無礼なんだ？それとも、俺から欲しい本を手に入れる気がねえのか？";
				link.l1.go = "book";
			}
			//<-- Сага
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "お前の囚人について話がある。";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "やあ、神父さん。お前の宣教について話がしたいんだ。";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "お前の囚人について話がしたいんだ。";
					link.l1.go = "CapComission6";
				}
			}
		break;
		
		case "shark":
			dialog.text = "スティーブン・ドッドソン？俺の話があんたの役に立つとは思えねえな。というのも、シャークはここ数ヶ月行方不明で、 誰も奴を見ちゃいねえ。\nだが、別に驚きじゃねえぜ。奴はブレイズ・シャープを殺して、自分の名を愚かな行為で汚したんだ。 何人かの大物コルセアを敵に回しちまったからな。";
			link.l1 = "シャークがシャープの死に無実だと信じる十分な理由がある。証拠はねえが、 もしかしたらシャーク自身が証明できるかもしれねえ。あんた、あいつについて何か話す気はあるのか？";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "数か月前、スティーブンが俺のところに来て、妙な取引を持ちかけてきたんだ。自分のフリゲート艦『フォーチュン』 を一か月間の担保として預ける代わりに、食糧満載のブリッグを貸してくれってな。 それで一か月後にはブリッグを返して食糧代も払うか、そうでなければ俺がフリゲート艦をもらうって話だった。だが、 一か月経ってもシャークも俺のブリッグも金も現れやしねえ。それに、ブレイズが殺されたって噂も聞いたし、 シャークが容疑者だともな。俺がどう思ったと思う？そうだ、スティーブンは最悪の事態から逃げやがったと考えたのさ。 だから、あいつのフリゲート艦はウィリアム・パターソンって名のイギリス野郎に売り飛ばした。 そいつは大喜びで山ほどドゥブロン銀貨を払ってくれたぜ。だから、俺の損失はきっちり埋まったし、 スティーブンに恨みなんざねえ。シャープの死なんてどうでもいい、俺には俺の心配事があるんでな。";
			link.l1 = "もし奴が逃げたかったんなら、お前のブリッグなんか必要なかっただろう？奴には自分の船があったんだ、 どんなブリッグより百倍もいいやつがな。シャークには何か計画があったみたいだが、何かが狂って、 時間通りに戻れなかったんだろうな。\n";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "もう言っただろうが、俺はドッドソンの問題なんざ興味ねえ。俺の分の約束は果たしたぜ。船のことなら、なぜあの忌々 しいブリッグが必要だったのか本人に聞くんだな。無理やり押し付けたわけじゃねえからな。";
			link.l1 = "わかった、もうその話はやめよう。確かにお前の言う通りだ。で、聞くが、 スティーブンが自分のブリッグでどこへ向かっていたか知ってるのか？";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "誰にも確かなことは分からねえさ。でも、俺にはいくつか心当たりがある。あいつは本土に向かって北西へ航海した。 だから、敵対的なインディアンで有名なペリル湾か、 異端審問とパピストで知られるヌエバ・エスパーニャのどちらかだろうな。\nだが、あいつがそんな場所に行くとは思えねえ。だがな、キューバの北西に「見捨てられた船の街」 っていう奇妙な場所があるって話だ。多くの奴らはそれを作り話だと思ってるが、俺は違う。 俺がロマンチストだからじゃねえ、本当にそこへ長艇で行った奴らがいるからだ。少なくとも、昔はな。";
			link.l1 = "「そいつらは誰だ？」";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "キューバから来たバッカニアどもだ。奴らはバルク船に牛の死骸を積み込んで、北西へと出航したんだ。 少し後になって戻ってくるときは、いつも懐に金や珍しい貴重品を詰め込んでやがるんだぜ。";
			link.l1 = "面白いじゃねえか！そのバッカニアどもはどこにいるんだ？";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "なんで俺に聞くんだ？キューバの森でも探してみろよ。たとえ見つけたとしても、あいつらは何も話さねえさ。 自分たちの幸運の源なんて、わざわざ教えるわけがねえだろ？だから時間の無駄だ、 長いこと誰もあいつらがやってるところなんて見ちゃいねえんだよ。\nそれと、スペイン人の水夫アルバラードが自分で島を訪れて書き残した記録があるって話も聞いたぜ。 だからちょっと気になってるんだ、もしかしたらスティーブンも結局そこに航海したのかもしれねえな。";
			link.l1 = "どの地図にも載っていない未知の島か……ふん。そいつは期待できねえ情報だな。";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "最初から俺の話が役に立たねえって言っただろうが。で、なんでドッドソンが必要なんだ？";
			link.l1 = "森の悪魔と俺は、奴をコースト同盟の頭に据えたいと思ってるんだ。前にも言ったが、 ブレイズは誰かに殺されたと信じるに足る重大な理由があるんだぜ。";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "へっ！ヤンがあいつの後ろ盾ってわけか？まあ、掟は知ってるだろう――ドッドソンは各バロンから票をもらわなきゃならねえんだ。";
			link.l1 = "俺は法律くらい知ってるぜ。\nじゃあ、二つ目の質問だ。選挙でドッドソンに票を入れるつもりか？";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "まあ、まずはあいつが戻るべきだな。正直言って、俺は誰がバラナスの頭になろうが、 ちゃんと仕事して俺に迷惑かけなきゃどうでもいいんだ。言っただろ、俺には俺の問題があるってな。お前、 うちの島にどれだけ魔女や魔術師がいるか知ってるか？知らねえ？教えてやるよ、軍団だぜ！ それにサンティアゴやハバナにもパピストどもが山ほどいるんだ。\n魔術師と言えばだな。「魔女の鉄槌」って本がある。俺はあれがどうしても欲しいんだが、英語版だけだ。 他のラテン語やドイツ語、スペイン語の訳本なんていらねえ、読めねえからな。その本を持ってきたら、 俺はドッドソンに票を入れてやるぜ。\nただし、ジャックマンもその本を探すって俺に約束したからな。もしあいつが先に見つけたら……その時は文句言うなよ。";
			link.l1 = "よし、考えてやるぜ。時間を取らせたな。じゃあな。";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "after_marlow";
			npchar.quest.sharkbegin = "true";
			AddQuestRecord("SharkHunt", "2");
		break;
		
		case "book":
			dialog.text = "本か？お前が言ってるのは『魔女への鉄槌』のことか？";
			link.l1 = "もちろんだ。お前のために見つけてやったぜ。頼まれた通り、英語で書かれているぞ。";
			link.l1.go = "book_1";
		break;
		
		case "book_1":
			dialog.text = "はっ、荒っぽい歓迎ですまねえな、相棒。もう二度とやらねえよ……その珍品、見せてくれ！";
			link.l1 = "ああ、見てみろよ。";
			link.l1.go = "book_2";
		break;
		
		case "book_2":
			RemoveItems(pchar, "witches_hammer", 1); // удалить трактат
			dialog.text = "やっとだ！震えて待て、地獄の下僕ども！俺の手が動かなくなるまで、お前らを放っておくつもりはねえぞ……";
			link.l1 = "よかったな、牧師。で、お前の票はどうするんだ？";
			link.l1.go = "book_3";
		break;
		
		case "book_3":
			dialog.text = "俺が言った通りだ、「誰が頭になろうが知ったこっちゃねえ」。スヴェンソンがふさわしくねえ奴を選ぶはずがねえさ。 だから俺の票を持っていけ。好きにしろ。これが俺の分け前だ。";
			link.l1 = "ありがとう、Zechariah。またそこで会おうぜ！";
			link.l1.go = "book_4";
		break;
		
		case "book_4":
			GiveItem2Character(pchar, "splinter_zm"); // дать осколок
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "27");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("気でも狂ったのか？屠殺屋ごっこがしたかったのか？海賊どもはみんなお前に怒ってるぜ、坊主、 さっさとここから出ていったほうがいいぞ…","どうやらお前、頭がおかしくなったみたいだな、坊主。ちょっと腕を伸ばしたかったのか？悪いが、 ここはお前の来る場所じゃねえ。とっとと失せろ！");
				link.l1 = RandPhraseSimple("聞けよ、この状況を何とかしたいんだ…","この問題を解決するのを手伝ってくれ…");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+"、私は" + GetSexPhrase("","") + " 海での安全について話したいんだ。沿岸の兄弟団の連中が、私のつつましい身に過剰な興味を示しているんだ。 少し黙らせてもらえないか？";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("俺に言いたいことでもあるのか？ないのか？だったらさっさと失せろ！",
						"はっきり言ったはずだ、これ以上俺をイラつかせるな。","はっきり言ったはずだが、しつこく俺を苛立たせやがって！",
						"ああ、もうこの無礼にはうんざりだぜ。","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("もう行くぜ。",
						"ああ、"+npchar.name+"……",
						"悪いな、"+npchar.name+"…",
						"「いてっ……」",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "お前の囚人のことだ。";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}		
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "「お前の囚人のことだ。」";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "「やあ、神父さん、あんたの依頼で来たんだ。」";
				link.l1.go = "CapComission3";
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && CheckAttribute(pchar, "questTemp.LongHappy"))
			{ // лесник . похититель  ( после ДЛС ДиС ,когда барбазона уже нет)
				link.l1 = "囚人に関わる商売をやってるって聞いたぜ…";
				link.l1.go = "Marginpassenger";
			}
		break;
		
	//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "ハハッ。俺がここに囚人を一人しか持ってねえと思ってるのか？名前を言え。";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+"「……あいつはここにいるのか？」";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "ああ、そうだ。あいつは一週間前にここへ来ていたバルバドスのプランテーション主、ビショップ大佐に売ったんだ。";
				link.l1 = "くそっ……";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "ああ、やっと来たか。バルバドスのあのプランテーションの旦那にあいつを売ろうかと思ってたんだがな、 あいつは一週間か二週間でここに来る予定だ……身代金は持ってきたのか？";
				link.l1 = "見てくれ、ちょっとした問題があるんだ……実は、そんなに金を持ってねえ。でも、働く気はあるぜ。";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "奴をまだ売ってねえのは助かるぜ。ほらよ、１５万ペソだ。奴はどこにいる？"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "お前は遅すぎたな……それに、なぜあいつのことを気にする？俺が交渉してたのはあいつの身内だけだぜ。";
			link.l1 = "奴らが俺にここへ来いと言いやがったんだ。";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "おい、遅ぇじゃねえか。俺にはどうにもできねえ。";
			link.l1 = "聞けよ、いくらであいつを売ったんだ？秘密じゃねえなら教えろよ。"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "ええ、違うぜ。でも教えてやらねえ……言ったら笑うだろうからな。ハハハハ！じゃあな。";
			link.l1 = "またな。";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));																															 
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{
				dialog.text = "「さて、」 "+pchar.name+"、わかるか、そう簡単にはいかねえんだよ。金を持って戻ってきたら、その腑抜けを返してやるぜ、ははっ。";
				link.l1 = "ああ、じゃあな。";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "ほうほう……ちょっとした用事があってな……どこから話せばいいかも分からねえ。筋を越えた海賊を沈める必要があるんだ。";
				link.l1 = "ジャングルでそいつをぶっ殺すだけじゃダメなのか？";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "商売ってのはそういうもんじゃねえんだよ……あいつを殺す必要はねえ、ただ俺の取り分を横取りしようとする連中に思い知らせてやりたいだけだ。だが、 あいつが死んでも俺は後悔しねえぜ。";
			link.l1 = "「なんで自分の手下を送り込まねえんだ？」";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "ふむ……まあ、 "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" 何人かの海賊に、戦利品の取り分が俺たちの隠し場所、つまり の近くに保管されていると信じ込ませやがった "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+"。奴らの二隻の船『"+pchar.GenQuest.CaptainComission.ShipName1+"「と」"+pchar.GenQuest.CaptainComission.ShipName2+"「'はついさっき錨を上げて出航し、」 "+sLoc+"。これで俺が部下どもにこの仕事を任せられねえ理由がわかっただろう？";
			link.l1 = "ああ、知ってるぜ。俺にどれくらい時間がある？";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12日から15日、これ以上は駄目だ。やつらが隠し場所にたどり着かないことが俺には重要なんだ。もし着かれちまったら、 貴重な積み荷ごと沈める意味がねえ。そんな場合は、むしろここに運ばせた方がマシだな…";
			link.l1 = "よし、乗ったぜ。奴らを捕まえてやる。";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка																			   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			//pchar.GenQuest.CaptainComission.PirateShips = "sdatkwest";	// лесник - заменил проверку для сдачи сразу.
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "心配すんな。俺の部下があいつをお前の船まで連れて行くぜ。で、なんであいつのことが気になるんだ？";
			link.l1 = "知らねえよ。親族に頼まれて、あいつを連れてきただけだ。";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "ああ、それでいいんだぜ。お前の部下にあんな安値を提示して、ちょっと悪い気がしたくらいだ。ハハハハ。じゃあな。";
			link.l1 = "じゃあな。";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen	
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																																			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");		// лесник																											 
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "それで、 "+GetFullName(pchar)+"、俺の仲間を沈めたのか？へっへっへ……";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "いや、逃げられちまった。戻る途中でも奴らには会わなかったぜ。";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "ああ、やったぜ。奴らはサメの餌にしてやった。";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "くそっ！奴らに会ったかどうかなんて、今さら関係ねえ！で、次は何を提案するつもりだ？";
			link.l1 = "「もっと楽な仕事があるんじゃねえか？」";
			link.l1.go = "CapComission4_1";
			link.l2 = "「聞け、」 "+NPChar.name+"……囚人の値段を下げろ……";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "いやだ。";
			link.l1 = "じゃあな……";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "値下げしろだと！？お前の無能のせいで俺の隠し財産がパーになったんだぞ！だからこそ値上げしてやる！欲しけりゃ20万ペソ払え、嫌ならとっとと失せろ。";
			link.l1 = "高すぎるな……じゃあな……";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "くそっ、金貨を持っていけ。";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow");		// лесник																								   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правка	// лесник																											 
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "この腑抜けはくれてやるぜ…";
			link.l1 = "さらばだ。";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правки имени в сж лесник																										  
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "ホッホー！よくやったな！この腑抜けを連れて、とっとと失せろ。";
			link.l1 = "ありがとう。じゃあな。";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
			/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "身代金を持ってきたのか "+GetSexPhrase("","ラ")+"？俺があいつをプランテーションの連中に売るって言ったのは冗談じゃなかったぜ。";			
			link.l1 = "「聞け、」 "+NPChar.name+"…話があるんだが……そんな大金は持ってねえ。でも、俺はやる気はあるぜ"+GetSexPhrase("","「а」")+" 「ケリをつけるぜ。」";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "奴をまだ売ってねえのは助かるぜ。ほらよ、１５万ペソだ。奴はどこにいる？"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "金は持ってきたか？あの男をプランテーションに売るってのは冗談じゃねえぞ。";			
			link.l1 = "「金はねえんだ」 "+NPChar.name+"、だが今取り組んでるところだ。";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "奴をまだ売ってねえのは助かるぜ。ほらよ、これがお前の金だ――十五万ペソだ。奴はどこにいる？"link.l2.go ="CapComission2_3";
			}			
		break;

																																				 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "「俺が何をしようが、お前に関係ねえだろ？なあ、さっさと消えた方が身のためだぜ…」";
			link.l1 = "チッ、落ち着けよ。お前と話があるんだ。囚人の件だ。";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "ああ、いいだろう。誰を身代金で解放したいんだ？";
			link.l1 = "待て。俺は誰かを買い戻しに来たんじゃねえ、囚人を買うチャンスをお前にやるために来たんだ。まあ、 そいつで身代金を手に入れる機会もあるってわけだ。";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "ふん。それで、なんで俺の助けが必要なんだ？自分で直接金を手に入れたくねえのか？";
			link.l1 = "俺にとっちゃかなり危ねえな。役人どもに目をつけられるかもしれねえ。";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "はっは……まあいい。見せてみろ。お前の捕虜は誰だ？";
			link.l1 = "これは "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "なるほどな……嘘じゃねえなら、悪くねえ取引だ。こいつのために金を払ってやってもいいぜ "+iTemp+" ペソを払うか、面白い情報を差し出すかだ。好きにしろ。";
			link.l1 = "ペソをもらった方がいいな。この仕事にはもううんざりだ……";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "はっ！もっと話してみろよ。どうせ俺にとっちゃ面白いネタがあるんだろうな。";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "金だ。持っていけ。もうお前の問題じゃねえ。売り物はここに運べ。";
			link.l1 = "今ごろは町の門の近くにいるはずだ。\nありがとう！本当に助かったぜ。";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "どういたしまして、もっと持ってこい……じゃあな！";
			link.l1 = "…幸運を祈るぜ…";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "利口な男と取引するのは気分がいいぜ。さて、よく聞け：数日後に\n "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" 本土からスペインの遠征隊がやって来るぜ、貴重な積み荷を満載してな。やつらはその積み荷を運ぶ船を待っている。 お前が一週間以内にそこへ行けば、その積み荷を自分のものにできるチャンスがあるぞ。\n俺がお前の立場なら、もう自分の船に向かってるぜ。それと、囚人をここに連れて来い。";
					link.l1 = "ありがとよ！この品は俺の苦労に見合う報酬だぜ。乗客ならもう町の門の近くにいるはずだ。 すぐにお前のところへ連れてこさせる。";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "頭の切れる男と取引するのは悪くねえな。さて、よく聞け。だいたい一週間後に、スペインのブリガンティン『"+pchar.GenQuest.Marginpassenger.ShipName1+"「貴重な品を積んだ船が」から出航する "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" へ "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+"。急げば簡単に追いつけるぜ。\nまだここにいるのか？俺ならもう自分の船に向かってるぜ。囚人もここに連れてこい。";
					link.l1 = "助かったぜ！この品は俺の苦労に見合う報酬だ。乗客ももう町の門の近くにいるはずだ。 すぐにお前のもとへ連れてこさせる。";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen: Abl - это к Залив"ом", нужен дательный
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen : как-то странно, наводку даёт Захар, а в сж Добряк дефолтом
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen 
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("強盗だと！？そんなの許せねえ！覚悟しろ、 "+GetSexPhrase("坊主","娘")+"...","おい、そこで何してやがるんだ！？俺を盗れると思ったのか？もう終わりだぜ……","待て、なんだと！？手を離せ！やっぱりお前は泥棒か！ここで終わりだ、この野郎…");
			link.l1 = LinkRandPhrase("くそっ！","カランバ！！","くそったれ！！");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("どけ ","どけ")+" ここからだ！","俺の家から出ていけ！");
			link.l1 = "「おっと……」";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "くだらねえ話で俺に絡むな。次は痛い目見るぜ……";
        			link.l1 = "わかったぜ。";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("終わりだ、黙ってろ。","もうお前と話したくねえから、これ以上俺にちょっかい出すんじゃねえぞ。");
			link.l1 = RandPhraseSimple("お望みどおりに…","ふん、まあいいだろう…");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "もっと敬意を示して、無礼な態度をやめてくれるといいんだが？";
        			link.l1 = "安心しろよ、牧師。必ずやるぜ。";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Puertoprincipe_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "問題を解決しろだと？自分が何をやらかしたかわかってんのか？まあいい、とにかく百万ペソ持ってこい。 そうすりゃ俺が仲間どもを説得して、お前のやったことを忘れさせてやる。気に入らねえなら地獄へ行きな。";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "よし、払う準備はできてるぜ。";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "了解だ。俺は行くぜ。";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "よし！これでまた清くなったと思え。ただし、もう二度とそんな汚ねえ真似はするんじゃねえぞ。";
			link.l1 = "俺はやらねえ。高すぎるぜ、俺にはな。じゃあな……";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("今日はすでにこの件について話しただろう。",
				                                      "はっきり言わなかったか？",
				                                      "お前のしつこさにはうんざりだ。",
				                                      "もう我慢の限界だ。さっさと失せろ！",
				                                      "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("また今度にするよ...",
				                                   "もちろんだよ、"+npchar.name+"...",
				                                   "悪かったよ、"+npchar.name+"...",
				                                   "いてっ...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "ははっ！兄弟団の連中に目をつけられたんだな、" + GetSexPhrase("相棒", "お嬢さん") + "？まあ、しばらくの間なら大人しくさせておけるさ。ただし、それなりの金は必要だ。" + FindRussianDublonString(iBarbazonTotalTemp) + "払えば話はつけてやる。";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "もちろん、これが君の金だ。";
					else link.l0 = "仕方ないな。これが君の金だ。";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "また後で来るよ...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "お前、正気か" + GetSexPhrase("", "い") + "？うちの連中はお前を疫病のように避けてるんだ。消え失せろ、時間の無駄だ。";
				else
					dialog.text = "何言ってんだ、" + GetSexPhrase("相棒", "お嬢さん") + "？お前は厄介者だって犬でもわかる。誰もお前とは関わりたくないんだよ。";
				link.l1 = "わかったよ...";
				link.l1.go = "exit";
			}
		break;

		case "pirate_threat_pay":
			iGPThreatRate = 0;
			iGPThreat = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
			DialogExit();
			PiratesDecreaseNotif("");
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
