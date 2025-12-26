int iBenuaPseudoGlobal;

// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "会えて嬉しいぞ、息子よ。借金を返しに来たのか？";
				if (PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "はい、お父様。私でございます。";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "遅れてしまって申し訳ないが、そのために来たわけじゃない。だが、すぐにそうなるから心配するな。";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "「何か必要なものはあるかい、息子よ？」";
				link.l1 = "はい、お父様。兄のミシェル・ド・モンペに会いたいのです。彼は……";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "「何かご用かい、息子よ？」";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua"))
			{
				dialog.text = "こんにちは、我が子よ。来てくれて嬉しい。君に話したいことがある。";
				link.l1 = ""+TimeGreeting()+"、神父様。お話を伺います。";
				link.l1.go = "SharlieEpilog_Benua_1";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_back"))
			{
				link.l99 = "父のことについて話したい。";
				link.l99.go = "SharlieEpilog_Benua_3";
			}
			//<-- Эпилог
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "はい、お父様。あなたの助けが必要です。私の名前は "+GetFullName(pchar)+"ミシェル・ド・モンペールがあなたに話すよう私に助言しました。";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "はい、お父様。ご助力が必要です。私の名前は "+GetFullName(pchar)+"。兄のミシェル・ド・モンペールにあなたと話すよう勧められました。";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "はい、神父様。ミシェルを助けるために船が必要ですが、私はカリブに着いたばかりで財布は空っぽです。 兄があなたならお金を貸してくれると教えてくれましたが……";
				link.l1.go = "FastStart_2";
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua"))
			{
				link.l1 = "ごきげんよう、お父様。少々風変わりな件でお力をお借りしたいのです。";
				link.l1.go = "WildRose_Abb_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2") && PCharDublonsTotal() >= 800)
			{
				link.l3 = "父上、必要な金額を用意しました。金八百です。";
				link.l3.go = "WildRose_Abb_14_pay";
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3"))
			{
				dialog.text = "ごきげんよう、息子よ。さて、君は自分の……ええと、その件の結果を聞きに来たのだろう？";
				link.l1 = "さすが父上、相変わらずお見通しですね。お待たせしないでください――さあ、あなたの部下が何を突き止めたのか教えてください。";
				link.l1.go = "WildRose_Abb_16";
				break;
			}
			//<-- Дикая Роза
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "はい、お父様。ご助力が必要です。";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "はい、お父様。私でございます。";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "いいえ、何もありません、お父様。";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			DelLandQuestMark(npchar);
			if(CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
				DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			dialog.text = "「どうして私のところへ来たのだ、息子よ？」";
			link.l1 = "こんにちは、お父様。お話しするように言われました。私の名前はシャルル・ド・モールです。 ミシェル・ド・モンペールを探しています。私の知る限り、彼はマルティニークのどこかにいるはずです。私は…彼の弟です。";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "ミシェル・ド・モンペールの弟か？ド・モール？妙だな……";
			link.l1 = "お父上、ご心配はごもっともです。私たちはただ名字が違うだけです。私の父はアンリ・ド・モンペールです。";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "ああ、なるほど。かつてアンリ・ド・モンペールとは個人的に親交がありました。もっと光の方を向いてください、 若者よ。そう！あなたは彼によく似ています。同じ顔立ち、同じ高貴な雰囲気です！ アンリ・ド・モンペールのご子息がこの教区に来てくださり、嬉しく思います。\nご質問についてですが、ミシェルはマルタ騎士団の高位の士官ですが……今は困難な状況にあります。幸いにも、騎士団の一人がちょうど私のもとを訪れております。彼なら、 あなたの不運な兄上のもとへ同行してくれるかもしれません――主が彼の運命に憐れみを与え給わんことを……";
			link.l1 = "この男は誰ですか、神父様？";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;		
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "息子よ、明日の朝また来なさい。今はもう話すことはない。";
			link.l1 = "「わかった。」";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		/* case "Benua_maltie":
			dialog.text = "こんにちは、息子よ。約束通り、昨日話した人物はすでにここで君を待っている。 彼は君を兄上のもとへ案内する準備ができているそうだ。聞くところによれば、兄上はひどい状態らしい。 主が彼の魂に憐れみを与えたまわんことを……";
			link.l1 = "「この男は誰ですか、神父様？」";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break; */
		
		case "escape":
			dialog.text = "ああ、シャルル、それは承知している。しかし、残念ながら君をがっかりさせねばならない。ミシェルはここにはいない。 ";
			link.l1 = "ここにいないってどういうことだ？彼はあなたの教会で私を待っていると言っていたはずだ！神父様、 何があったんですか？兄はどこですか！？";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "息子よ、お前の兄はここに来て、昨夜遅くに私のつましい住まいを出ていった。どこへ行ったのかは分からん。だが、 お前への手紙を残していったぞ。";
			link.l1 = "信じられない……あんなに尽くしてやったのに！その手紙をよこせ！";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "そんなに怒るな、シャルル。これが手紙だ。読んでくれ、それから…それからお前と話がしたい。だがまずは、兄上からの伝言を読んでくれ。";
			link.l1 = "俺は待ちきれなくて燃えてるぜ！";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "手紙を読んだようですね。さて、これからあなたに話したいことがあります、シャルル……";
				link.l1 = "しかし…そんなはずはないだろう？これは一体どういう戯言なんだ？兄が変わり者なのは知っているが、狂人じゃないんだぞ！";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "息子よ、手紙を読め。後で話そう。";
				link.l1 = "「はい、お父様……」";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "シャルル、私もあなたの兄上の行動には驚かされました。今でも困惑する瞬間があります。\n騎士団と三位一体の忠実なしもべであったはずなのに、まるで脱走兵のように振る舞っているのですから。";
			link.l1 = "こんな奇妙な行動の理由が何か思い当たることはあるか？";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "あいにく、私は知りません。しかし、彼には彼なりの動機があるのでしょう、しかも深い動機が。 自分の過去すべてを捨てるなんて、よほど重大な理由があるはずです。それが何なのか、私には想像もつきません。でも、 ものすごく悪いこと……いや、恐ろしいことが関わっている気がします。";
			link.l1 = "それは何でしょう、お父様？";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "息子よ、神父は目で見るのではなく、心で見るのだ。言葉で説明することはできぬが……お前の兄は、何か穢れたこと、忌まわしいことをしようとしている。 まさか自分の口からこんなことを言う日が来るとは思わなかった。しかし……";
			link.l1 = "まあ、兄貴が何か裏で企んでるのは疑ってないさ。何をやろうとしてるかも大体見当がつくよ。その「何か」 ってのは黄色くて、心地よいカチャカチャ音がするものだ。";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "お前の兄貴を突き動かしているのは、金への欲望じゃないと思うぜ。奴にはもっと大きなものが必要なんだろうな。";
			link.l1 = "私はミシェルから多くを学び、彼の考え方も理解できましたので、 彼にとって何が大切で何がそうでないかを見分けることができると思います。\nですが、お父上の貴重なお言葉も心に留めておきます。";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "神のご加護を、息子よ。行きなさい、さあ行くのだ。主があなたを見守ってくださいますように！";
			link.l1 = "ありがとうございます、お父様。さようなら！";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddDialogExitQuestFunction("Sharlie_Benua_BrotherEscape");
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "ミシェル・ド・モンペールの弟か？ド・モール？妙だな……";
			link.l1 = "お父上、ご心配はごもっともです。私たちは単に姓が違うだけです。私の父はアンリ・ド・モンペールです。";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "あ、ああ、なるほど。アンリ・ド・モンペールとは個人的に知り合いだったんだ。光の方を向いてごらん、若者よ……そうだ！君は彼にそっくりだ。同じ顔立ち、同じ貴族の風格！ アンリ・ド・モンペールの息子がこの教区に来てくれて嬉しいよ。\nミシェルのもとにヨーロッパから来た男が訪ねてきたという話はすでに聞いていたが、 まさか実の弟だったとは思いもしなかった。ミシェルを助けてやってくれ、彼はいま大変な時期を迎えている。さて、 私はどうお役に立てるかな？";
			link.l1 = "ミシェルが、もし私が当局にトラブルを起こしたら、あなたが助けてくれるだろうと言っていました。";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "それがミシェルが君に言ったことか？なるほど。まあ、そのような件なら私が力になれるかもしれない。 私は神聖ローマ教会とオランダ植民地に多少の影響力がある。だから、 君とスペインやオランダ当局との間を取り持つこともできるかもしれない。ただし、 君の不始末があまりにも深刻になっていれば、私にもできることは限られる――その場合は、せいぜい軽減する程度だ。完全な和解には何度かの仲介が必要になるだろう。それに、いずれにせよ、 慈善事業や旅費のために金のドゥブロンを私に用意してもらわねばならない。それと、 私が助けられるのは一度に一つの国だけだ。これらの条件が受け入れられるなら、遠慮なく私に相談してくれ。 何ができるか一緒に考えよう。";
			link.l1 = "ありがとう！心に留めておくよ。";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "どうしたんだい、息子よ？話してごらん、ちゃんと聞いているよ。";
			link.l1 = "「ミシェルが、もし私が当局にトラブルを起こした時は、あなたが助けてくれるだろうと言っていました。」";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "「どうしたんだ、息子よ？何か手伝えることがあるか？」";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater"))
			{
				link.l1 = "命令の配達に関する支払いの件に戻りましょう。";
				link.l1.go = "SharlieEpilog_Benua_DublonsLater_2";
			}
			if (CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				link.l1 = "命令を送りたいのですが…";
				link.l1.go = "SharlieEpilog_Benua_Delivery";
			}
			//<-- Эпилог
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "スペイン当局とトラブルになっちまったんだ。";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "オランダ当局とトラブルになっちまったんだ。";
				link.l2.go = "relation_hol";
			}
			link.l9 = "すまないが、今回は自分で何とかするつもりだ。";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "なるほど、貴族の旦那たちはお前をハバナの地下牢にぶち込みたくてうずうずしてるってわけか……";
			link.l1 = "まさにその通りでございます、お父上…";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "なるほど、賢い商人どもはお前をウィレムスタッドの地下牢に放り込みたくてうずうずしてるってわけか……";
			link.l1 = "「まさしくその通りです、お父様……」";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.BenuaNation));
			iBenuaPseudoGlobal = DiplomatDublonPayment(rate, "Benua", false);
			sTemp = FindRussianDublonString(iBenuaPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "はい、その噂は我々の教会にも届いております。あなたの悩みをお助けできますよ。それは解決できることです。 私に必要なのは\n " + sTemp + " あなたの窮地をうまく切り抜けるために。";
				if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
				{
					link.l1 = "素晴らしい！ほら、金貨だ。";
					link.l1.go = "agree";
				}
				link.l2 = "それなら、今こそ俺がドゥブロン金貨を見つける時だな。";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "ああ、君の「武勇伝」の噂は我々の教会にも届いているぞ。お前は自分の評判を汚してしまったな、息子よ。 もっと慎重になるべきだ。しかし、私が助けてやろう。私には必要なのだ\n " + sTemp + " あなたの窮地をうまく取り繕うために。";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "素晴らしい！ほら、金貨だ。";
						link.l1.go = "agree";
					}
					link.l2 = "ならば、今こそ俺がドゥブロン金貨を探す時だな。";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "はい、息子よ。お前も兄と同じくらい必死だな……これはきっと家系の性だろう。状況を完全に正すことはできんが、 それでもお前の惨めな窮地を少しは和らげてやれると思う。もし望むなら、あとでさらに供物を捧げることもできるぞ。 私が必要なのは\n " + sTemp + " 今はこれで、すぐにあなたの悩みを解決し始めましょう。";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "素晴らしい！ほら、金貨だ。";
						link.l1.go = "agree";
					}
					link.l2 = "では、今こそ俺がドゥブロン金貨を見つける時だな。";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iBenuaPseudoGlobal); // Sinistra legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "これから少なくとも二週間は待たなければなりません。その間に、私は適切な人々に会って話ができると思います。";
			link.l1 = "ありがとう、お父様！待っています……";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
			pchar.GenQuest.BenuaNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.BenuaNation));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "ド・モール？それにミシェル・ド・モンペールの兄弟なのか？妙だな……";
			link.l1 = "あなたの疑念は理解します、神父様。私の父はアンリ・ド・モンペールです。";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "あ、ああ、なるほど。アンリ・ド・モンペールとは個人的に知り合いだった。\nこちらへ、若者よ、光の中へお入りなさい。\nほう！その目、その気品ある顔立ち、そっくりだ！\nアンリ・ド・モンペールの息子が私の教会に来てくれて嬉しいよ。\n君が兄上を助けてくれることを願っている。最近、彼には不運が続いているからな。";
			link.l1 = "はい、神父様。ミシェルを助けるために船が必要ですが、カリブに着いたばかりで財布は空っぽです。 兄からあなたが少しお金を貸してくれると聞きました……";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			DelLandQuestMark(npchar);
			dialog.text = "「ミシェルがそう言ったのか？」";
			link.l1 = "神父様、私があまり信用できそうに聞こえないかもしれませんが、本当です。船を手に入れれば、 それだけ早く兄を牢獄から救い出せます。";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "なるほど、息子よ。お前が本当のことを話しているのは分かる。さて、ミシェルとお前の父上のために、私が手を貸そう。 少しばかり貯えがある、これを持っていけ。五万ペソと百ドゥブロンあれば十分だろう。";
			link.l1 = "ありがとうございます、神父様。条件は何ですか？";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "プレッシャーはないさ。返済は半年で十分だ。";
			link.l1 = "よろしいです、神父様。改めてありがとうございます！";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "私の祝福と共に行きなさい、息子よ。";
			link.l1 = "...";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "素晴らしいぞ、息子よ。その金が役に立ったことを願っておる。";
			link.l1 = "確かにそうだ！ありがとう！";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveDublonsFromPCharTotal(100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		// Jason Долго и счастливо
		case "LH_abbat":
			dialog.text = "シャルル、信じられないよ！どうしてここに来たんだ！？";
			link.l1 = "お許しください、聖なる神父様。良い知らせを持ってまいりました――私、結婚することになりました。ぜひ、私の結婚式で神父様に司祭を務めていただきたいのです。";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "息子よ、これは素晴らしいことだ！それで父上からの手紙を受け取って、 例によって自分の考えで行動することにしたのか？心から嬉しく思うぞ！\nだが、この教会で結婚する決心をしない限り、私には手助けできそうにないな。";
			link.l1 = "あなたの任務が行き詰まっているとお聞きしました、神父様。何かお手伝いできることはありますか？\n結婚式はスペインの礼拝堂で行われるとのことですが、もちろん、それも興味深い冒険ですが、 私はどうしてもマルティニークで祝宴を開きたいのです。\nほどよく華やかに、名のある証人や立派な客人たちの前で行いたいのです。";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "申し訳ないが、息子よ、君の権威などカトリック教会の最高位聖職者たちの頑固さの前では何の役にも立たんのだ、 とくにスペイン植民地ではな。カトリック布教団の影響力を我が国々でどう分け合うかという問題について、 まだ合意に至っていない。だから私は今、名誉ある客人であり、名誉ある人質としてここにいるのだ。 スペイン人たちは我々からもっと良い提案があるのを待っている。私はヨーロッパへ伝言を送った。 うまくいけば二ヶ月以内に返事が来て、交渉を再開できるだろう。もし二ヶ月で返事が来なくても、 遅くとも半年以内には届くはずだ。\nそれと、教皇とマザランがこの数週間で妥協に至ったとはいえ、本当に温かい関係を語るにはまだ早い。正直なところ、 我々が合意に至る日が来るかどうかも分からない。 パロッティは単に私を自分の政治的駆け引きのための切り札として扱っているだけのように思える。しかし、 言わせてもらえば、あの異端審問官のコーヒーは絶品だ！";
			link.l1 = "俺には半年も二ヶ月も猶予はない！父上の願いを果たさねば、無理やり結婚させられてしまうんだ。 しかも父上の健康も昔ほどじゃないし、できれば自分の選んだ人と、 未来のモンペール家のご婦人を紹介する時間も欲しいんだよ。";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "残念だが、息子よ、君の結婚式には別の神父を探さねばならんようだな。\nあいにく、わしはここに長く留まることになりそうじゃ。";
			link.l1 = "もし俺が異端審問官のコーヒーから君を連れ出したら、どう思う？";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "喜んであなたの助けを受け入れます。私がこの任務に選ばれたのは偶然ではないと思います。最悪の場合、 ベノワ神父のことなど誰も気に留めなくなるでしょう。そして、主は私に耐えるよう命じましたが、そのすべての「祝福」 にもかかわらず、私は自分の結論に重荷を感じています。しかし、繰り返しますが、 パロッティ神父があなたの願いを聞き入れる可能性は低いでしょう。";
			link.l1 = "それなら、無駄な説得はやめて時間を節約しよう。礼拝が終わったらすぐに教会を出て、俺の船へ直行するぞ。\nためらわないでくれ、神父様――あいつらは俺たちの会合を見ていて、俺の顔も覚えている。もし総督邸からあなたを連れ出す羽目になったら、 助けるのがずっと難しくなるからな。";
			link.l1.go = "LH_abbat_5";
		break;
		
		case "LH_abbat_5":
			dialog.text = "危険だぞ、息子よ、とても危険だ。外には私を屋敷まで護衛するために衛兵たちが待っているし、 街中にも兵士があふれている。";
			link.l1 = "奇襲で行きましょう、ブノワ神父。\n私を信じてくだされば、すべてうまくいきます。こういうことには…多少心得がありますので。";
			link.l1.go = "LH_abbat_6";
		break;
		
		case "LH_abbat_6":
			dialog.text = "かしこまりました。しかし、どうか無用な流血は避けてください！私もこういった経験は多少あります……導いてくれ、息子よ。私はすぐ後ろにいる。でも武器は取らないから、そのつもりでいてくれ。";
			link.l1 = "考えもしませんでしたよ、お父様。私に任せてください。ついてきてください、でも気をつけて、 撃たれるかもしれません。";
			link.l1.go = "LH_abbat_7";
		break;
		
		case "LH_abbat_7":
			DialogExit();
			LongHappy_SantiagoBenuaEscape();
		break;
		
		case "LH_abbat_8":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			dialog.text = "息子よ、私の釈放について礼を言う暇もなかったな。どうやらスペインの司教と異端審問官パロッティは、 我が枢機卿とローマ教皇庁の新たな関係を壊そうとしていたらしい。つまり、 君は完全に我が国の利益のために動いたのだ。今回も、だ。しかし「ありがとう」と言う者は、私以外にいないだろう。";
			link.l1 = "よくあることですよ、神父様。お力になれて嬉しいです。しかし、 私からもお尋ねしたいことがあるのを覚えていらっしゃいますよね？";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "もちろん！それでは楽しい話に移ろう――シャルル、君の大事な日の準備は順調かい？";
			link.l1 = "少しずつ形になってきたな。もっと簡単に、早く準備できた軍事作戦も知ってるが、これはやる価値があるぜ！";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "もちろんだ、息子よ！そしてこの機会に一つはっきりさせておきたい――お前は自分の結婚式をどのように考えているんだ？";
			link.l1 = "「つまり、どれだけ偉そうかってことか？」";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "もちろんです！私が教会の準備をいたしますし、あなたも大切な方々を招待なさりたいでしょう。";
			link.l1 = "特に何もありません、神父様。私が友人と思う者たちは別の場所で待っております。ここにいるのは、役人が数名、 私の部下、そしてただの見物人くらいです。";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "では、小さな寄付で何とかできそうですね。";
			link.l1 = "それはあまり怖そうに聞こえませんね。それで、そのような寄付は金貨でいくらですか？";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "聖歌隊、厳粛な式典、その他の費用で――百五十ドゥブロン、それ以上はいただきません。\nそれに新郎新婦からの通常の献金を加えて、合計で二百ドゥブロンです。";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "「どうぞ、神父様。」";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "あの軍事作戦の件だが……銀行まで歩いて行って、戻らねばならん。";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_14":
			DialogExit();
			npchar.dialog.currentnode = "LH_abbat_14_1";
		break;
		
		case "LH_abbat_14_1":
			dialog.text = "「あなたの寄付はどうなさいますか、息子よ？」";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "「どうぞ、神父様。」";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "「はいはい、すぐに持ってきます……」";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_15":
			RemoveDublonsFromPCharTotal(200); // Sinistra legendary edition
			dialog.text = "まだ答えなければならない問いが一つ残っている――花嫁を誰が引き渡し、彼女の代理として結婚の証人になるのか？";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "ブルーウェルドから来たヤン・スヴェンソン。彼はイギリス人だが、評判の良い男で、 ヘレンをまるで自分の娘のように大切にしている。そして彼女の養母はグラディス・マッカーサーだ。";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "ノエル・フォルジェ男爵、きっと私に光栄を与えてくださるでしょう。";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "フィリップ・ド・ポワンシー騎士、きっと私に光栄を賜ることでしょう。";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "さて、それで花婿の証人は誰が務めるんだ？覚えておけ、貴族の生まれで評判の良い男でなければならんぞ。";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "ノエル・フォルジェ男爵、きっと私に光栄を賜ることでしょう。";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "フィリップ・ド・ポワンシー騎士、きっと私に光栄を賜ることでしょう。";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "ファディはグアドループ出身の立派な商人だ。あとは彼のお気に入りの酒を仕入れるだけだな。";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "ファディはグアドループの立派な商人だ。俺はあいつの好物の酒を仕入れるだけでいいんだ。";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "素晴らしいですね。招待状を送りますが、客人たちが到着するまでには少し時間がかかります。\nすべての準備が整い、指定された方々も町に到着するのは一ヶ月後になると思います。";
			link.l1 = "よし！それなら、ちょっと用事を済ませる時間があるな。すぐにまた会いましょう、神父様、幸運を祈っていてください！ ";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "素晴らしい、招待状は私が送りますが、招待客が到着するまでには少し時間がかかります。\nすべての準備が整い、招待された方々も街に到着するのは一ヶ月後くらいになると思います。";
			link.l1 = "よし！それならちょっと用事を済ませる時間があるな。すぐにまた会いましょう、神父様、幸運を祈っていてください！";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "素晴らしい、私が招待状を送りますが、招待客がここに来るまでには少し時間がかかります。すべての準備が整い、 指定された方々が街に到着するのは一ヶ月後になると思います。";
			link.l1 = "よし！それなら、ちょっと用事を済ませる時間があるな。すぐにまた会いましょう、神父様、 どうか幸運を祈ってください！";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_18":
			DialogExit();
			AddQuestRecord("LongHappy", "11");
			SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
			if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
			{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true);//закрыть таверну Исла-Тесоро
			}
			npchar.dialog.currentnode = "First time";
		break;
		
		case "LH_abbat_19":
			dialog.text = "ついにこの日が来たな、息子よ！すべて準備は整った――あと数時間で始められるぞ。顔色が悪いぞ！";
			link.l1 = "「少し緊張しています、神父様。」";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "よくあることだ。今日は君の人生で最も大切な日だし、私もここに来た皆も心から祝福しているよ。 せめて基本的なお祈りくらいは覚えているだろうな――教会に熱心だったとは言えないからな？まあ、それでもどんな場合でも私が助けてやろう。\nそれからもう一つ――どうやら花嫁は自分の信念を曲げず、ドレス姿は見られないようだな？ふむ、 またしても君から上流社会へのサプライズというわけだ――本当に驚かされるよ。さて、行きなさい、息子よ、身なりを整えてきなさい。準備ができたら始めよう。";
			link.l1 = "はい、聖父様。やりましょう。";
			link.l1.go = "LH_abbat_21";
		break;
		
		case "LH_abbat_21":
			DialogExit();
			chrDisableReloadToLocation = true;
			WaitDate("", 0, 0, 0, 2, 0);
			DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;
		
		case "LH_abbat_22":
			pchar.questTemp.LongHappy.Mistake = 0;
			dialog.text = "天にまします我らの父よ、御名が聖とされますように、アド…";
			link.l1 = "「…御国が来ますように」";
			link.l1.go = "LH_abbat_23_1";
			link.l2 = "「…レクイエム・エテルナム・ドナ・エイス」";
			link.l2.go = "LH_abbat_23_2";
		break;
		
		case "LH_abbat_23_1":
			dialog.text = "…御心のままに、天におけるごとく地にもなさせたまえ。われらの日ごとの糧を今日も与えたまえ、 われらの負い目を赦したまえ、もし…";
			link.l1 = "……我らが負い目ある者を赦すごとく、我らの負い目をも赦したまえ";
			link.l1.go = "LH_abbat_24_1";
			link.l2 = "……初めにありしごとく、今も常に、世々に至るまで。アーメン";
			link.l2.go = "LH_abbat_24_2";
		break;
		
		case "LH_abbat_23_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "え、え……ふむ……";
			link.l1 = "";
			link.l1.go = "LH_abbat_23_1";
		break;
		
		case "LH_abbat_24_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "え、え……ふむ……";
			link.l1 = "";
			link.l1.go = "LH_abbat_24_1";
		break;
		
		case "LH_abbat_24_1":
			dialog.text = "「我らを誘惑に導かず、悪より救い給え。アーメン。」";
			link.l1 = "アーメン。";
			link.l1.go = "LH_abbat_25";
		break;
		
		case "LH_abbat_25":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "親愛なる皆様、私たちはここに神の御前、そしてこの会衆の前で、 この男と女を神聖なる結婚によって結び合わせるために集まりました。愛する皆様 "+sld.name+" そしてシャルル、あなたは神の御言葉に耳を傾け、人間の愛と結婚の意味を思い出させてもらいました。今、 聖なる教会を代表して、あなたの意思を問いただしたいと思います。\n"+sld.name+" 「そしてシャルル、あなたは主の御前で自らの意思と誠実な心をもって結婚の誓いを立てることを望みますか？」";
			link.l1 = "「はい。」";
			link.l1.go = "LH_abbat_26";
		break;
		
		case "LH_abbat_26":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_27":
			dialog.text = "「あなたたちは、健やかなる時も病める時も、喜びの時も悲しみの時も、 人生の終わりまで互いに誠実であり続けることを誓いますか？」";
			link.l1 = "「はい。」";
			link.l1.go = "LH_abbat_28";
		break;
		
		case "LH_abbat_28":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_22";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_29":
			dialog.text = "「あなたは、主がお与えになる子どもたちを愛し、受け入れ、キリスト教の信仰のうちに育てることを誓いますか？」";
			link.l1 = "「はい。」";
			link.l1.go = "LH_abbat_30";
		break;
		
		case "LH_abbat_30":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_31":
			dialog.text = "さあ、お互いに向き合って誓いを立てなさい。";
			link.l1 = "";
			link.l1.go = "LH_abbat_32";
		break;
		
		case "LH_abbat_32":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_33":
			dialog.text = "ここにいる者の中で、この二人が聖なる結婚によって結ばれてはならぬ理由を知る者があれば、今ここで申し出なさい。 さもなくば、永遠に沈黙を守りなさい。\nそれでは、主の御前と、ここに集う人々の前で、あなた方を夫婦と宣言します！In nomine Patris, et Filii, et Spiritus Sancti. アーメン。";
			link.l1 = "アーメン。";
			link.l1.go = "LH_abbat_34";
		break;
		
		case "LH_abbat_34":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_35":
			string sTemp;
			if (sti(pchar.questTemp.LongHappy.Mistake) > 1) sTemp = "(Whispering) Charles, my son, just move your lips, I beg you - don't try to make any sound...";
			else sTemp = "";
			dialog.text = "新婚の二人よ、ひざまずいて共に祈りなさい。オラティオ・フィデリウム。 "+sTemp+"";
			link.l1 = "";
			link.l1.go = "LH_abbat_36";
		break;
		
		case "LH_abbat_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.lastname = "de Maure";
			sld.SpecialRole = "wife";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "おめでとう、息子よ。お前の父上もきっと誇りに思うだろうし、私も誇りに思っている。\nこの困難な時代、お互いを大切にして幸せになりなさい。";
			link.l1 = "ありがとうございます、神父様。素晴らしいミサでしたし、あなたが司式してくださって本当に嬉しく思います。";
			link.l1.go = "LH_abbat_38";
		break;
		
		//--> Дикая Роза
		case "WildRose_Abb_2":
			dialog.text = "それで、私のところに相談しに来たのか、子供たちよ？\nよろしい、話を聞こう。";
			link.l1 = "むしろ助けを求めてきたんです、神父様。人脈が広く、あらゆる人を知っている方の助けを……";
			link.l1.go = "WildRose_Abb_3";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua");
		break;

		case "WildRose_Abb_3":
			dialog.text = "お話の途中で失礼します、息子よ、しかし私はただの慎ましい修道院長であって、密偵などではありませんぞ。";
			link.l1 = "しかし、慎ましい修道院長でも密偵を知っているかもしれませんよね？少なくとも、 どうやって接触できるか教えてくれるのではありませんか？";
			link.l1.go = "WildRose_Abb_4_fortune";
			link.l2 = "我々をここに導いた件は、まさしく長い間忘れ去られていた秘密に関わるものだ……。\n我々はただ、それらを再び日の下に引きずり出そうとしているだけなのだ。";
			link.l2.go = "WildRose_Abb_4_stealth";
		break;

		case "WildRose_Abb_4_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "さて、若造、これは気に入らんな。要点を話せ。それからどう助けてやるか――いや、助けるかどうかを考えよう。";
			link.l1 = "はい、お父様。手短に申し上げます……";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_4_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = ""+pchar.name+"、謎めいた言い方はやめてくれ――正直、うんざりだ。";
			link.l1 = "はい、お父様。手短に申し上げます……";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_5":
			dialog.text = "行きなさい、息子よ。";
			link.l1 = "私の仲間、メアリー・キャスパーは父親を探しています――少なくとも彼に関する何らかの手がかりを求めているのです。\n彼がイギリス海軍の士官であり、1638年にカポ・カトチェで難破したブリッグ船『ラングラー』に乗っていたことを突き止めました。";
			link.l1.go = "WildRose_Abb_6";
		break;

		case "WildRose_Abb_6":
			dialog.text = "それで、あなたは彼がまだ生きていると望んでいるのか？こんなにも長い年月が経ったのに？";
			link.l1 = "たとえ彼が難破から生き延びなかったとしても、メアリーは自分の父がどこから来たのか、どんな人物だったのか、 どんな人生を送ったのかを知りたがっているのです……公式な書類には詳しいことはほとんど書かれていませんが、それでも何かしら価値あるものが見つかるかもしれません、 そう思いませんか、神父様？";
			link.l1.go = "WildRose_Abb_7";
		break;

		case "WildRose_Abb_7":
			dialog.text = "お前の考えはもっともだ、息子よ。お前の行いは立派で神にかなっている。しかし、私に何を求めているのか、 いまひとつ分からぬのだ。";
			link.l1 = "父上はこの諸島に長くお住まいですね。もしかして、 イギリス海軍の士官に関する植民地の記録にアクセスできる方をご存知ありませんか？";
			link.l1.go = "WildRose_Abb_8_stealth";
			link.l2 = "我々には、イギリス海軍士官の記録が保管されている植民地の公文書館に出入りできる男が必要です。\nきっとご存知でしょう、神父様。";
			link.l2.go = "WildRose_Abb_8_charisma";
		break;

		case "WildRose_Abb_8_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "お前が何を頼んでいるのか分かっているのか、息子よ？ 問題は単にその情報が軍事機密かもしれないということだけではないのだ…";
			link.l1 = "「それで、他には何があるのですか、神父様？率直に申し上げますが…」";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_8_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "お前が何を求めているのか分かっているのか、息子よ？ 問題は単にその情報が軍事機密かもしれないということだけではないのだ…";
			link.l1 = "それで、他には何があるのですか、神父様？率直に申し上げますが…";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_9":
			dialog.text = "問題はまさにその植民地の記録にあるんだ。二十年前、ジャマイカはスペイン人の支配下にあり、 セントジョンズやブリッジタウンは常に襲撃の脅威にさらされていた。\nそこに王立海軍の艦船が駐留していたとは考えにくい……";
			link.l1 = "「ロンドンの海軍本部の記録庫のことですか、お父様？」";
			link.l1.go = "WildRose_Abb_10";
		break;

		case "WildRose_Abb_10":
			dialog.text = "たぶんね。書類は海軍本部に送られているはずだ。手に入れるのは簡単じゃないぞ。";
			link.l1 = "「でも、それはできるんでしょう、神父様？」";
			link.l1.go = "WildRose_Abb_11";
		break;

		case "WildRose_Abb_11":
			dialog.text = "不可能なことは何もない、息子よ。しかし努力……そして報酬が必要だ。";
			link.l1 = "もちろんでございます、お父様。お金はあなたにお渡しすればよろしいですか、 それとも他の方にお会いする必要がございますか？";
			link.l1.go = "WildRose_Abb_12";
		break;

		case "WildRose_Abb_12":
			dialog.text = "私自身で他の者に会うつもりだ、息子よ。お前に必要なのは……八百ドゥブロンだ。";
			link.l1 = "承知しました、お父様。どれくらい時間がかかりますか？";
			link.l1.go = "WildRose_Abb_13";
		break;

		case "WildRose_Abb_13":
			dialog.text = "俺の見立てじゃ二ヶ月ってとこだな。それと、ところで、お前が探してる奴の名前をまだ聞いてねえぞ。";
			link.l1 = "その男の名はジョシュア・キャスパーだ。";
			link.l1.go = "WildRose_Abb_14";
		break;

		case "WildRose_Abb_14":
			dialog.text = "覚えておきます。もし今すぐ全額を用意できるなら――早ければ明日にも知らせを送りましょう。";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "もちろんでございます、お父様。はい、どうぞ。金貨八百枚です。";
				link.l1.go = "WildRose_Abb_14_pay";
			}
			link.l2 = "いいえ、お父様、私にはそんなお金は持ち合わせておりません。しかし、すぐに戻って持ってまいります。";
			link.l2.go = "WildRose_Abb_14_nopay";
		break;

		case "WildRose_Abb_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "「よろしい、」 "+pchar.name+"。二ヶ月後に戻ってきてくれ——その頃には、何らかの答えを必ず用意しておく。";
			link.l1 = "ありがとうございます、お父様。また会う日まで！";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2");
		break;

		case "WildRose_Abb_14_nopay":
			dialog.text = "おっしゃる通りです、息子よ。";
			link.l1 = "すぐに戻る。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			pchar.questTemp.WildRose_Etap3_Benua_2 = true;
		break;
		
		case "WildRose_Abb_16":
			dialog.text = "彼はジョシュア・キャスパーと彼の船の両方について知った――ただし、その船は「ラングラー」ではなかった。王立海軍にその名のブリッグが所属したことは一度もないのだ。";
			link.l1 = "ふむ……ジョシュア・キャスパーが乗っていた船は確かにその名だったはずだ。そして、肝心のジョシュア本人はどうした？";
			link.l1.go = "WildRose_Abb_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3");
		break;

		case "WildRose_Abb_17":
			dialog.text = "あの男は多くの功績と勲章を持つ立派な士官だった――すべて彼の個人記録に記されている。\n真の信仰には属していなかったが、立派な船長だった。\nマドモアゼルはそのような血筋を誇りに思ってよいでしょう。";
			link.l1 = "それは良い知らせですね、お父様。ですが、もしよろしければ船に戻りましょう。\n「ラングラー」号でなかったのなら、その船の名前は何だったのですか？";
			link.l1.go = "WildRose_Abb_19";
			AddQuestRecordInfo("WildRose_Records_3", "1");
		break;

		case "WildRose_Abb_19":
			dialog.text = "『コーンウォール』。彼は1638年1月にプリマスを出港し、アンティグアとプロビデンスの駐屯地に給料を届ける任務を受けていた。";
			link.l1 = "信じられない……";
			link.l1.go = "WildRose_Abb_20";
			AddQuestRecordInfo("WildRose_Records_4", "1");
		break;

		case "WildRose_Abb_20":
			dialog.text = "その船が最終目的地に到達したかどうか、私には分かりません。\nしかし、セントジョンズには寄港しました。港の事務所には、その年の6月2日付けでキャスパー船長が提出した報告書が残っています。";
			link.l1 = "お父様、あなたが見せかけほど単純な方ではないと分かっていました！この書類には、 何か重要な内容が記されているのでしょうか？";
			link.l1.go = "WildRose_Abb_21_charisma";
			link.l2 = "私たちは永遠にあなたに借りができました、神父様。さて、その書類についてお話しになりましたが――何か重要なことが書かれているのでしょうか？";
			link.l2.go = "WildRose_Abb_21_honor";
			AddQuestRecordInfo("WildRose_Records_5", "1");
		break;

		case "WildRose_Abb_21_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "「アゾレス沖でスペインのガレオン船『トロ』との戦闘報告しかない。乗組員の三分の一が命を落とした――報告書を読めば全て分かる。」";
			link.l1 = "もう一つ質問だ。アンティグア港の記録に目を通したなら、 ジョシュア・キャスパーの名前を他のどこかで見かけたりしなかったか？";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_21_honor":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "アゾレス近海でスペインのガレオン船『トロ』との戦闘報告しかない。乗組員の三分の一が命を落とした――報告書を読めばすべて分かるぞ。";
			link.l1 = "もう一つ質問だ。アンティグア港の記録に目を通せたなら、 ジョシュア・キャスパーの名前を他のどこかで見かけたりしなかったか？";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_22":
			dialog.text = "私に多くを求めるな、息子よ。もしあの難破から彼が生き延びて、その後艦隊に戻ったかもしれないと言いたいのなら――私はとてもそうは思えん。";
			link.l1 = "「主の御業は神秘的ですね、神父。」";
			link.l1.go = "WildRose_Abb_23";
		break;

		case "WildRose_Abb_23":
			dialog.text = "確かに、息子よ。しかしな、彼の個人記録にはジョシュア・キャスパーは1586年生まれと記されているのだ…";
			link.l1 = "「もしかすると、お父様の言う通りかもしれません。」";
			link.l1.go = "WildRose_Abb_24_fortune";
			link.l2 = "父上、カリブで過ごした年月の中で、私が目にしたものは、どんなあり得ない話でも信じられるほどでした。";
			link.l2.go = "WildRose_Abb_24_charisma";
		break;

		case "WildRose_Abb_24_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "確かに、あのような士官は戦場で死ぬに値しただろう。しかし、哲学的に言えば、あれもまた一つの戦いだったのだ……";
			link.l1 = "私は哲学者ではありません、神父様。でも、いろいろとありがとうございました……";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_24_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "確かに、あのような士官は戦場で死ぬに値しただろう。\nだが、哲学的に言えば、あれもまた一つの戦いだったのだ……";
			link.l1 = "私は哲学者ではありません、神父様。でも、いろいろとありがとうございました……";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_25":
			dialog.text = "主がこの道へとお導きくださるのです、我が子たちよ。あなた方を助けるのが私のつつましい務めでございます。\nしかし、この件に関しては、これ以上私にできることはないのではと恐れております……";
			link.l1 = "承知しました、お父様。それでは、これにて失礼いたします。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_5");
		break;
		//<-- Дикая Роза
		
		//--> Эпилог
case "SharlieEpilog_Benua_1":
			dialog.text = "私は君の父上の容態を深く案じている。彼が手紙の中で君に打ち明けたかは分からないが、 私への書簡ではこう告白していた。体の力が衰えてきており、長くはもたないだろう、と。";
			link.l1 = "病が快方に向かわないとは言っていましたが……自分の不安については、どうやら触れていなかったようです。";
			link.l1.go = "SharlieEpilog_Benua_2";
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua");
		break;

		case "SharlieEpilog_Benua_2":
			dialog.text = "私から言えるのはそれだけだ。彼が伝えてきたのは以上だが、一つだけ確かなことがある。君にもう一度会えぬまま、 主の御前に立つことを恐れているのだ。";
			link.l1 = "そのことは話していました。正直に言えば、私自身も彼を訪ねようと考えてはいたのですが……しかし……。";
			link.l1.go = "SharlieEpilog_Benua_3";
		break;

		case "SharlieEpilog_Benua_3":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_1"))
			{
				dialog.text = "我が子よ、我ら一人ひとりに与えられた時の長さを知るのは主のみだ。再会を先延ばしにしてはならぬ。一度の抱擁が、 千の祈りにも勝る安らぎを魂にもたらすこともある。";
				npchar.SharlieEpilog_BenuaRazgovor_1 = true;
			}
			else
			{
				dialog.text = ""+pchar.name+"、もう彼のもとへ向かうのを先延ばしにするつもりはないだろうな？ 時は君の味方ではないのだ……。";
			}
			link.l1 = "おっしゃる通りです、神父様。すぐに出航の準備を始めます。今の立場を考えると、 すべてを片付けるにはかなりの時間が必要になるかもしれませんが……。";
			link.l1.go = "SharlieEpilog_Benua_5";
			link.l2 = "ご心配は理解しています、神父様。必ず考えてみます。ただ、今はどうしても先延ばしにできない重要な用事があります。 この話は、また後ほどにしましょう。";
			link.l2.go = "SharlieEpilog_Benua_4_exit";
		break;
		
		case "SharlieEpilog_Benua_4_exit":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_2");
		break;
		
		case "SharlieEpilog_Benua_5":
			dialog.text = "もし借金があるのなら、まずは返済から始めることを勧めよう、我が子よ。高利貸しというものは非常に執念深い。 彼らは君の評判を、そして旧大陸においてさえ家名全体を傷つけかねない。\n"+
			"その他の件については――君の父との友情と主の御名にかけて――私ができる限りの助力をしよう。必要な指示を書面で託せば、私が責任をもって宛先に届けさせる。ただし、 使者への報酬だけは君が支払う必要がある。すべての書簡の配達には、二百ダブロンもあれば十分だろう。";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "ありがとうございます、神父様。お力添えは本当に心強い。どうぞ、こちらをお受け取りください。";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "ご配慮に感謝します、神父様。残念ながら、今は必要な額を持ち合わせていません。この件は、また後ほどに。";
			link.l2.go = "SharlieEpilog_Benua_DublonsLater";
			SharlieEpilog_Benua_Dlg_1();
		break;
		
		case "SharlieEpilog_Benua_DublonsLater":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_3");
		break;
		
		case "SharlieEpilog_Benua_DublonsLater_2":
			dialog.text = "もちろんだ、"+pchar.name+"。二百ダブロンを持ってきてくれたのだな？";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "ええ、もちろんです。どうぞお受け取りください。";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "申し訳ありません、まだ必要な額が用意できていません。";
			link.l2.go = "exit";
		break;
		
		case "SharlieEpilog_Benua_6":
			dialog.text = "見事だ、我が子よ。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			RemoveDublonsFromPCharTotal(200);
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater");
		break;
		
		case "SharlieEpilog_Benua_Delivery":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				dialog.text = "さて、どこから始めたいのですか？";
				npchar.SharlieEpilog_BenuaRazgovor_2 = true;
			}
			else
			{
				dialog.text = "誰に、何を知らせたいのですか？";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona"))
			{
				link.l1 = "かつて地図に載っていない島を見つけたことがあります。そこには既に数人の入植者がいて、 私は彼らの後見人となりました。私が出航する今、その島には新しい「総督」が必要でしょう。";
				link.l1.go = "SharlieEpilog_Benua_IslaMona";
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Baron"))
			{
				link.l2 = "ラ・ベガのマーカス・ティラックス宛に手紙を送りたいのです。大した用事ではありませんが、 期日までに届けなければならないのです。";
				link.l2.go = "SharlieEpilog_Benua_Baron";
			}
			if (CheckCharacterItem(PChar, "patent_fra") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Patent"))
			{
				link.l3 = "私は有効なフランスの特許証を持っています――カプスターヴィルの庁に私の決意を通知したいのです。";
				link.l3.go = "SharlieEpilog_Benua_Patent";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Money"))
			{
				link.l4 = "神父様、この地で過ごした年月の間に、私にはかなりの財産が貯まりました。しかし、それが私の家族のものになる前に――その血に汚れているかもしれないその財産を清めたいのです。それを戦利品を持つ山賊としてではなく、 良心と名誉が社会の目に清い者としてこの地を去りたいのです。";
				link.l4.go = "SharlieEpilog_Benua_Money";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Svenson") && CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona_France"))
			{
				link.l5 = "私はブルーヴェルドのヤン・スヴェンソンに私の出発を知らせたいのです。この群島を去るにあたり、 彼に知らせずに行くのは無礼でしょう。";
				link.l5.go = "SharlieEpilog_Benua_Svenson";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Houk"))
			{
				link.l6 = "私はマルーンタウンのハウク一家に、旅立ちを知らせたいです。";
				link.l6.go = "SharlieEpilog_Benua_Houk";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Jino"))
			{
				link.l7 = "私はセントジョンズのジーノ・グイネリに、旧世界への出立を知らせたいです。";
				link.l7.go = "SharlieEpilog_Benua_Jino";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_S") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_M") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_L"))
			{
				link.l85 = "以上です、父よ……旅立つ準備はできたようです。";
				link.l85.go = "SharlieEpilog_Benua_TimeToGoHome";
			}
			link.l99 = "失礼します、神父様、行かねばなりません。";
			link.l99.go = "SharlieEpilog_exit";
		break;
		
		case "SharlieEpilog_exit":
			DialogExit();
			LAi_SetStayType(npchar);
			NextDiag.CurrentNode = "First time";
		break;
		
		case "SharlieEpilog_Benua_Jino":
			dialog.text = "もちろんです、息子よ。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Jino_2";
			pchar.questTemp.SharlieEpilog_Jino = true;
		break;
		
		case "SharlieEpilog_Benua_Jino_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Jino_3";
			AddQuestRecord("SharlieEpilog", "8_1");
		break;
		
		case "SharlieEpilog_Benua_Jino_3":
			dialog.text = "...";
			link.l1 = "完了。発送してもらって構いません。";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Houk":
			dialog.text = "もちろんです、息子よ。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Houk_2";
			pchar.questTemp.SharlieEpilog_Houk = true;
		break;
		
		case "SharlieEpilog_Benua_Houk_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Houk_3";
			AddQuestRecord("SharlieEpilog", "8");
		break;
		
		case "SharlieEpilog_Benua_Houk_3":
			dialog.text = "...";
			link.l1 = "完了。発送してもらって構いません。";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Svenson":
			dialog.text = "ブルーヴェルドのヤン・スヴェンソン……覚えておきましょう。では手紙を頂いて――今日中に発送しましょう。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Svenson_2";
			pchar.questTemp.SharlieEpilog_Svenson = true;
		break;
		
		case "SharlieEpilog_Benua_Svenson_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Svenson_3";
			AddQuestRecord("SharlieEpilog", "7");
		break;
		
		case "SharlieEpilog_Benua_Svenson_3":
			dialog.text = "...";
			link.l1 = "ヤンの家を見つけるのは簡単です。住民に聞けばいい――ブルーヴェルド中で誰一人として、彼が誰でどこに住んでいるかを知らない者はいないでしょう。";
			link.l1.go = "SharlieEpilog_Benua_Svenson_4";
		break;
		
		case "SharlieEpilog_Benua_Svenson_4":
			dialog.text = "心配するな、息子よ。我々の者たちは仕事をよく心得ている。手紙は必要な相手に、しかも期日通りに届けられるだろう。 ";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;
		
		case "SharlieEpilog_Benua_Money":
			dialog.text = "貴方は、教会に――犯罪によって得られた金を祝福してほしいと？";
			link.l1 = "むしろ――フランスとその陛下のために尽くしたことで得た金です。";
			link.l1.go = "SharlieEpilog_Benua_Money_2";
		break;
		
		case "SharlieEpilog_Benua_Money_2":
			dialog.text = "分かっている、息子よ。私はこう言うこともできる――教会は金を清めたり、どのようにして得られたかを取り消したりはしない、と。しかしそれで何の益があるだろう？ 飢えた者が飢え続け、路上で寝る者が路上で夜を明かし、助けを求める病人が助けられずに死にゆくというのに。 私は祝福を与える用意がある。ただし、その金のほんの一部が、あなた自身ではなく――助けを必要とする者たちに役立つならばの話だ。";
			link.l1 = "もちろんです、神父様。私は貴方が言う分を寄付する覚悟があります。";
			link.l1.go = "SharlieEpilog_Benua_Money_3";
		break;
		
		case "SharlieEpilog_Benua_Money_3":
			dialog.text = "では、いくら持っていきたいのだ？";
			link.l1 = "一千万ペソ。";
			link.l1.go = "SharlieEpilog_Benua_Money_4";
			if (sti(pchar.Money) >= 250000)
			{
				link.l2 = "二千五百万ペソ。";
				link.l2.go = "SharlieEpilog_Benua_Money_5";
			}
			if (sti(pchar.Money) >= 500000)
			{
				link.l3 = "五千万ペソ。";
				link.l3.go = "SharlieEpilog_Benua_Money_6";
			}
		break;
		
		case "SharlieEpilog_Benua_Money_4":
			dialog.text = "それでは、十万ペソの寄付で十分でしょう。この資金があれば、困っている人々に数ヶ月も食事を提供できます。 今すぐこの金額を納める準備はできていますか、息子よ？";
			link.l1 = "もちろんです。どうぞ、お受け取りください。真に助けを必要としている人々を支援できることを嬉しく思いますし、 あなたの監督のもと、この金が賢く、そして誠実に使われると確信しています。";
			link.l1.go = "SharlieEpilog_Benua_Money_4_1";
			link.l2 = "申し訳ありませんが、もう一度よく考えたいのです。";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_5":
			dialog.text = "では、二十五万ペソの寄付が必要になります。この資金で孤児のための施設を建てることができ、あなたの名が称えられ、 その最初の運営を支えるでしょう。今すぐこの金額を納める準備はできていますか、息子よ？";
			link.l1 = "もちろんです。どうぞ、お受け取りください。真に助けを必要としている人々を支援できることを嬉しく思いますし、 あなたの監督のもと、この金が賢く、そして誠実に使われると確信しています。";
			link.l1.go = "SharlieEpilog_Benua_Money_5_1";
			link.l2 = "申し訳ありませんが、もう一度よく考えたいのです。";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_6":
			dialog.text = "ふむ、どうやら時間を無駄にしていなかったようだな、"+pchar.name+"。五十万ペソの寄付で十分だと思います。これだけの資金があれば病院を建て、長年にわたり必要なものを提供できます。 今すぐこの金額を納める準備はできていますか、息子よ？";
			link.l1 = "もちろんです。どうぞ、お受け取りください。真に助けを必要としている人々を支援できることを嬉しく思いますし、 あなたの監督のもと、この金が賢く、そして誠実に使われると確信しています。";
			link.l1.go = "SharlieEpilog_Benua_Money_6_1";
			link.l2 = "申し訳ありませんが、もう一度よく考えたいのです。";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_4_1":
			dialog.text = "素晴らしいことです、息子よ。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -100000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "10000000");
			AddQuestUserData("SharlieEpilog", "tSum", "100000");
			pchar.questTemp.SharlieEpilog_gold_S = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;

		case "SharlieEpilog_Benua_Money_5_1":
			dialog.text = "素晴らしいことです、息子よ。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -250000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "25000000");
			AddQuestUserData("SharlieEpilog", "tSum", "250000");
			pchar.questTemp.SharlieEpilog_gold_M = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;

		case "SharlieEpilog_Benua_Money_6_1":
			dialog.text = "素晴らしいことです、息子よ。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -500000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "50000000");
			AddQuestUserData("SharlieEpilog", "tSum", "500000");
			pchar.questTemp.SharlieEpilog_gold_L = true;
			pchar.questTemp.SharlieEpilog_Money = true;
			Achievment_Set("ach_CL_205");
		break;

		case "SharlieEpilog_Benua_Patent":
			dialog.text = "それは、どのようなものになるのですか、息子よ？";
			link.l1 = "長い旅が私を待っていますが、特許状も、フランスと国王への忠誠心も保持したいと思います。";
			link.l1.go = "SharlieEpilog_Benua_Patent_2";
			link.l2 = "私は特許状を返上することにしました。先は長く、いつ戻るか分かりません。任務や規則を守れないかもしれないので、 重荷を抱えずに旅をしたいのです。";
			link.l2.go = "SharlieEpilog_Benua_Patent_6";
			pchar.questTemp.SharlieEpilog_Patent = true;
		break;

		case "SharlieEpilog_Benua_Patent_2":
			dialog.text = "そのような決断を下したことを嬉しく思います、息子よ。我が国は今、 これまで以上に強く勇敢な騎士たちを必要としています。しかし、"+pchar.name+"、落ち着き、家を持ち、常に命を危険にさらす生活から離れることを考えたことはありませんか？ 人は永遠に炎の中に身を置くべきではないのです。";
			link.l1 = "神父様、じっとしているのは難しいかもしれません。しかし、聖書にあるように「主の兵士にも、 労苦の終わりに安息がある」と書かれています。私の務めがまだ終わっていなくとも、 いつか剣を鞘に納める日を自ら選べることを願っています。";
			link.l1.go = "SharlieEpilog_Benua_Patent_3";
		break;

		case "SharlieEpilog_Benua_Patent_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_4";
			AddQuestRecord("SharlieEpilog", "5_2");
		break;

		case "SharlieEpilog_Benua_Patent_4":
			dialog.text = "素晴らしいことです、息子よ。陛下もあなたの忠誠と献身を見過ごすことはないでしょう。";
			link.l1 = "今の私の思いは全く別のところにあります... 父が私に屋敷での生活を勧めないことを願っています。私はその準備ができていないのです。でも幸い、 よく考える時間はあります。";
			link.l1.go = "SharlieEpilog_Benua_Patent_5";
		break;

		case "SharlieEpilog_Benua_Patent_5":
			dialog.text = "...";
			link.l1 = "では、現世のことに戻りましょうか。";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Patent_6":
			dialog.text = "それは賢明な判断です。しかし、あなたが去ることで、 この海域におけるフランスの力が大きく損なわれることは確かです。";
			link.l1 = "陛下の下には、フランスの偉大さを支えるにふさわしい船長が他にも多くいるはずです。";
			link.l1.go = "SharlieEpilog_Benua_Patent_7";
		break;
		
		case "SharlieEpilog_Benua_Patent_7":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_8";
			AddQuestRecord("SharlieEpilog", "5_1");
		break;

		case "SharlieEpilog_Benua_Patent_8":
			dialog.text = "...";
			link.l1 = "これで終わりか。肩の荷が下りたようだ。正直に言えば、ここカリブに来た時の自分がどんな人間だったかすら、 もう忘れていたよ... 様々なことを経験してきた。";
			link.l1.go = "SharlieEpilog_Benua_Patent_9";
		break;

		case "SharlieEpilog_Benua_Patent_9":
			dialog.text = "おそらく、何度も耳にしたであろう、息子よ──主の道は計り知れぬ。天の意志として与えられた道を、あなたは立派に歩んできた。しかし私は信じている──あなたの試練はまだ終わっておらず、むしろ、あなたの栄光は今まさにその頂点に向かって昇っているのだと。";
			link.l1 = "栄光は重荷なのです、聖父様。それを求める者すべてが、その重みに耐えられるとは限らず...そして、引き際を見誤ることもあります。";
			link.l1.go = "SharlieEpilog_Benua_Patent_10";
		break;

		case "SharlieEpilog_Benua_Patent_10":
			dialog.text = "...";
			link.l1 = "では、現世のことに戻りましょうか。";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Baron":
			dialog.text = "息子よ、海賊たちの頭と関わりがあるのか？";
			link.l1 = "あなたはコーデックスの守り人をご存じですか？";
			link.l1.go = "SharlieEpilog_Benua_Baron_2";
			pchar.questTemp.SharlieEpilog_Baron = true;
		break;

		case "SharlieEpilog_Benua_Baron_2":
			dialog.text = "コーデックスの守り人か？いや、私は彼を知らぬ。だがマルクス・ティラクスなら知っている──あの処刑人だ。彼の背後には多くの血が流れている。いかに祈ろうとも、神の許しを得るには百年でも足りぬだろう。 それでも...本当に彼と取引をしているのか？";
			link.l1 = "ミシェルを牢獄から救うために、彼の信頼を得る必要がありました。とはいえ、私は自らの過ちを理解し、 彼との関係を断つ決意をしました。この手紙によって、最後の繋がりを断ち切ります。";
			link.l1.go = "SharlieEpilog_Benua_Baron_3";
			link.l2 = "今となっては重要ではありません。私は諸島を去り、彼との道も自然と分かれるでしょう、聖父様。";
			link.l2.go = "SharlieEpilog_Benua_Baron_7";
		break;

		case "SharlieEpilog_Benua_Baron_3":
			dialog.text = "その繋がりとは何なのだ、息子よ？無実の者たちの血で染まっていないことを祈る。";
			link.l1 = "私は形式上、ル・フランソワという海賊の町の長を務めていました。実際の支配者は他にいましたが。今日をもって、 私は海賊男爵の称号を完全に、そして永遠に放棄します。";
			link.l1.go = "SharlieEpilog_Benua_Baron_4";
		break;

		case "SharlieEpilog_Benua_Baron_4":
			dialog.text = "あなたが正しき道へと歩みを進めたことを嬉しく思います、息子よ。あなたの魂の救済を願い、祈りましょう。 誰しも過ちを犯すものですが、主は心から悔い改める者をこそお赦しになります。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Baron_5";
		break;

		case "SharlieEpilog_Benua_Baron_5":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_6";
			AddQuestRecord("SharlieEpilog", "4_1");
		break;

		case "SharlieEpilog_Benua_Baron_6":
			dialog.text = "素晴らしいことです、"+pchar.name+"。その手紙を私に渡しなさい──必ずや相手に届くように手配しましょう。そして、祈りを忘れてはなりません、息子よ。悔い改めと祈りこそが、 魂に刻まれたどんな重罪も洗い流すのです。";
			link.l1 = "ありがとうございます、聖父様。もしかすると、まだ私にも救いの道が残されているのかもしれません。";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Baron_7":
			dialog.text = "どれほどの罪であろうと、息子よ、赦しの扉は常に開かれている。悔い改めと祈り、そして善き行いは、 魂を石の塵を洗う雨のように清めてくれるのだ。";
			link.l1 = "時が来れば、聖父様。今は現世の務めに専念しなければなりません。";
			link.l1.go = "SharlieEpilog_Benua_Baron_8";
		break;
		
		case "SharlieEpilog_Benua_Baron_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_9";
			AddQuestRecord("SharlieEpilog", "4_2");
		break;
		
		case "SharlieEpilog_Benua_Baron_9":
			dialog.text = "...";
			link.l1 = "どうぞ、お受け取りください。";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_IslaMona":
			dialog.text = "その人々のことを気にかけ、忘れずにいてくれたとは素晴らしいことです、息子よ。その島を誰に託したいのですか？";
			link.l1 = "私はフランスの旗を掲げるべきだと思います。遅かれ早かれこの島は発見され、他国に奪われる恐れがあります。 私はそれを許すわけにはいきません。";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France";
			link.l2 = "この島とその住人たちは王権の庇護の下でなく、自由に生きるにふさわしい。 友人であるブルーヴェルドのヤン・スヴェンソンに手紙を送り、この土地を託すつもりです。ただし、聖父様、 この話は秘密にしてください──彼らの安全と幸せのために。";
			link.l2.go = "SharlieEpilog_Benua_IslaMona_Pirate";
			pchar.questTemp.SharlieEpilog_IslaMona = true;
		break;

		case "SharlieEpilog_Benua_IslaMona_France":
			dialog.text = "賢明な判断です、"+pchar.name+"。国王の庇護のもと、この島には秩序と安全がもたらされるでしょう。";
			link.l1 = "カプステルヴィルの役所と島の住人たちに向けた手紙を出します。封筒には島の座標を記載しておきます。";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_2";
		break;

		case "SharlieEpilog_Benua_IslaMona_France_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_France_3";
			pchar.questTemp.SharlieEpilog_IslaMona_France = true;
			AddQuestRecord("SharlieEpilog", "3_1");
		break;

		case "SharlieEpilog_Benua_IslaMona_France_3":
			dialog.text = "...";
			link.l1 = "どうぞ、お受け取りください。陛下の艦隊が来る前に、そちらの方々が島を見つけてくださることを願っています。";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_4";
		break;

		case "SharlieEpilog_Benua_IslaMona_France_4":
			dialog.text = "心配はいりません、息子よ。この手紙は最も信頼できる使者に託します。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate":
			dialog.text = "あなたの道が正しいかどうか、私が判断することではありません、息子よ。遅かれ早かれ、この島は誰かに発見され、 列強の一つが手を伸ばすでしょう。それは時間の問題です。しかし、あなたがその決断を下したということは、 それが神の御心なのかもしれません。心配はいりません──私はあの人々を危険にさらすことなく、彼らのために祈りを捧げましょう。";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_Pirate_2";
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_Pirate_3";
			pchar.questTemp.SharlieEpilog_IslaMona_Pirate = true;
			AddQuestRecord("SharlieEpilog", "3_2");
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate_3":
			dialog.text = "ブルーヴェルドのヤン・スヴェンソン、ですね？";
			link.l1 = "その通りです、聖父様。そしてもう一通の手紙は島に直接届ける必要があります。座標は封筒に記してあります。";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_TimeToGoHome":
			dialog.text = "素晴らしいことです、息子よ。たしか、あなたはピナース船「"+GetShipName("Ulysse")+"」でここに来たのでは？";
			link.l1 = "その通りです。でも、どうしてそのようなことを？";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_2";
		break;

		case "SharlieEpilog_Benua_TimeToGoHome_2":
			dialog.text = "その船は最近、競売にかけられました。そしてあなたにはチャンスがあります、シャルル──その船で、今度は艦長として故郷へ戻るという。";
			link.l1 = "ふむ... これは確かに魅力的な提案ですね。港の管理局に行ってみるべきでしょう。ありがとうございます、聖父様。";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_3";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome_3":
			DialogExit();
			NextDiag.CurrentNode = "First Time";
			AddDialogExitQuestFunction("SharlieEpilog_PU_Ulysse_1");
		break;
		//<-- Эпилог
		
		case "LH_abbat_38":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
