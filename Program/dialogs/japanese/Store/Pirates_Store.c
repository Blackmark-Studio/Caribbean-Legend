// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("さあ、何の用だ？","ちょうどその話をしていたところだ。忘れてしまったのか……","今日はこれで三度目だぞ、この質問を持ち出すのは……","聞け、ここは店だ。みんなここで物を買うんだ。邪魔しないでくれ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知っているだろう、」 "+NPChar.name+"、また今度かもしれませんね。","そうだ、なぜか忘れてしまっていた……","ああ、本当にこれで三度目だな……","ふむ、俺はやらない……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "「聞いてくれ、」 "+npchar.name+"、最近イスラ・テソロでミゲル・ディチョソを見かけましたか？";
				link.l1.go = "tieyasal";
			}
			// Addon 2016-1 Jason пиратскаЯ линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
			{
				link.l1 = ""+npchar.name+"「マーカス・タイレックスの代理で来た。あんたが仕事を頼みたい男を探してるって聞いたぜ。」";
				link.l1.go = "mtraxx";
			}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
			{
				link.l1 = ""+npchar.name+"「ロスボホム号」が発見され、拿捕されました。荷下ろしと積荷の確認を始めますか？";
				link.l1.go = "mtraxx_5";
			}
		break;
				
		// город майя
		case "tieyasal":
			dialog.text = "ああ、ここで彼が自分の船のために物資を買っていったよ。ちなみに、つい最近のことだ。 君はほんの数日違いですれ違ったわけだな。\nそれに、もしかすると彼はまだこの居住地にいるかもしれない。 私は他人のために探りを入れるようなことはしないんでね。もう少し周りに聞いてみたらどうだい、 もしかしたら旦那を見つけられるかもしれないぞ。";
			link.l1 = "わかった。情報をありがとう！";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
			pchar.quest.Mtraxx_PasqualeLate.over = "yes";
            dialog.text = "まさにその通りだ！ちょうどいい時に来てくれて助かった。さて、本題を話そう…";
			link.l1 = "お話をうかがいましょう。";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
            dialog.text = "今この瞬間、 "+sTemp+"「ロスボホム」という名のオランダ船が護衛艦一隻を伴って我々の海域に到着する。積荷は黒檀で、 ウィレムスタッドから出航し、もう一隻の護衛艦と合流してヨーロッパへの安全な航海を確保する予定だ。 どの航路を取るかは分からない――シント・マールテン経由かエスパニョール経由か――だが、合流地点の座標は把握している。\n君の任務は、その場所でオランダ船を見つけ、商船に乗り込み、積荷を私の元へ持ち帰ることだ。積荷が届き次第、 報酬は支払おう。";
			link.l1 = "承知した。日時と場所は？";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			int i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
			int n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
            dialog.text = ""+sti(pchar.questTemp.Mtraxx.Crdn.degN)+" "+i+" 北と "+sti(pchar.questTemp.Mtraxx.Crdn.degW)+" "+n+" 西だ。イスラ・テソロの南か南西あたりに違いない。俺はこういうのは苦手でな、船乗りじゃないからな。 でもお前は違う。仕事を終わらせるには、およそ五日間あるぞ。";
			link.l1 = "承知した……分かった。なら、ぐずぐずしてる暇はねえな！";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "ご武運を、船長。あなたと積み荷をお待ちしています。";
			link.l1 = "...";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_convoy";
		   i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
           n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
		   AddQuestRecord("Roger_4", "3");
		   AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")+ "Gen")));
		   AddQuestUserData("Roger_4", "sdegN", sti(pchar.questTemp.Mtraxx.Crdn.degN));
		   AddQuestUserData("Roger_4", "sminN", i);
		   AddQuestUserData("Roger_4", "sdegW", sti(pchar.questTemp.Mtraxx.Crdn.degW));
		   AddQuestUserData("Roger_4", "sminW", n);
		   SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		   SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;
		
		case "mtraxx_5":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
			if (iTotalTemp < 1)
			{
				dialog.text = "冗談じゃないぞ、若造！お前の貨物庫には黒檀の板一枚も入ってないじゃないか！これは厚かましい詐欺だ！出て行け！ このことはマーカスに報告するからな！さっさと出て行け！！！";
				link.l1 = "ふむ……";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < makeint(sti(pchar.questTemp.Mtraxx.Crdn.Ebony)/4))
			{
				dialog.text = "ふざけてるのか、坊や？お前の貨物室には黒檀のかけらしか入ってねえじゃねえか！こんな詐欺があるか！ さっさと出ていけ！マーカスにも報告してやるからな！出ていけ！！！";
				link.l1 = "ふむ……";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < sti(pchar.questTemp.Mtraxx.Crdn.Ebony)-20)
			{
				dialog.text = "ロズボホム号には少なくとも "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.Crdn.Ebony))+" 黒檀のことだ。なぜ少なく持ってきたんだ？";
				link.l1 = "うーん……戦いの最中に一部を処分しなきゃならなかったんだよ。それに、あのネズミどもめ……";
				link.l1.go = "mtraxx_7";
				break;
			}
            dialog.text = "よろしい。どれくらいお持ちですか？ "+FindRussianQtyString(iTotalTemp)+"？素晴らしい！1つにつき150ペソお支払いしましょう。";
			link.l1 = "150エイトか？黒檀はもっと高いはずだが。";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_6":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_angry";
		   DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_7":
            dialog.text = "ネズミか？ほう、ほう……まあいいだろう。一匹につき100ペソだ、それで好きにしていいぞ。";
			link.l1 = "100ペソだけだと？これは白昼堂々の強盗じゃねえか！";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			AddMoneyToCharacter(pchar, iTotalTemp*100);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "強盗があなたの稼業で、船長、私はただの商人です。金を持って行ってくれ、これ以上言い争うのはやめましょう。 あなたはすでに私の積荷の一部を他所で売って十分な儲けを得たのですから。";
			link.l1 = "じゃあ、くたばりやがれ！";
			link.l1.go = "mtraxx_9";
		break;
		
		case "mtraxx_9":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_fail";
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_10":
            dialog.text = "おっしゃる通りです、船長。しかしまずは、盗品を売ってみて、他の商人たちがいくら払うか確かめてみてください。 私が提示している価格は非常に高いのです。第二に、あれは私の情報でした。 あなた一人ではあの隊商を見つけることはできなかったでしょう。それに、他にも貴重品や商品がありましたが、 それらについては私は何も要求していません。第三に、 私はマーカス・タイレックスの目においてあなたに最高の信用を与えます。それは非常に価値のあることですよ、 信じてください。そして最後に、第四ですが、貧しい商人も何とかして生計を立てなければならないのです。";
			link.l1 = "おっと！そんな理屈を前にしちゃ退散するしかないな "+npchar.name+"。少し計算してみましょう。";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
			AddMoneyToCharacter(pchar, iTotalTemp*150);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "素晴らしい。代金を受け取ってくれ。お取引できて光栄だ。時々は私の店にも立ち寄ってくれよ。 航海に幸運が訪れることを祈っている！";
			link.l1 = "「そしてあなたの商売は……」";
			link.l1.go = "mtraxx_12";
		break;
		
		case "mtraxx_12":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_complete";
		   AddQuestRecord("Roger_4", "9");
		   pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		   pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		   pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		   bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
