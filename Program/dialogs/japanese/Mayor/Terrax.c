// Маркус Тиракс, барон Ла Веги
int iTerraxTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;
	bool bOk;

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
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "ああ、王子、やっと来やがったな。せめてお前だけでも顔を出したか！仕事が山積みなのに、みんな消えちまいやがって！ 一体全員どこ行きやがったんだ！？";
					link.l1 = "さっぱり分からねえ……マーカス、俺はもう限界だ。もうたくさんだぜ。死んだ連中が夢に出てきやがるし、 ルシファー本人が俺の首筋に息を吹きかけてやがる。最近は血が流れすぎたんだよ。";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason НСО
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "俺に“仕事”でもあるか？";
				link.l1 = "よう、Marcus。ああ、「仕事」が一つあるぜ。儲かるし、実用的だ。";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "金は持ってきたか？";
				link.l1 = "俺がやった。";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "そいつが俺たちの客だ！仕事は終わったぜ、お前のバロンは厳重に警備された地下牢にぶち込まれてる。見に行きたいか、 へっへっへ！？";
				link.l1 = "それをやる時間ならたっぷりあるぜ、ハハ。あいつはちゃんと扱われてるのか？";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "チャールズ、なんだよ、くそっ！？";
				link.l1 = "マーカス、すべてがうまくいかなかった。俺は来ることも、お前に知らせることもできなかったんだ…";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "「こいつが俺たちの操り師だぜ！」";
				link.l1 = "ハハハ！見世物は最高だったぜ！";
				link.l1.go = "patria_x29";
				break;
			}
			
			link.l0 = ""+npchar.name+"、私は" + GetSexPhrase("","") + " 海での安全について話したいんだ。沿岸の兄弟団の連中が、私のつつましい身に過剰な興味を示しているんだ。 少し黙らせてもらえないか？";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("俺に言いたいことでもあるのか？ないのか？だったら俺に構うな！","「はっ、」 "+pchar.name+"「おい！俺に用か？ねえなら、邪魔すんじゃねえぞ。」")+"","はっきり言ったはずだぜ……出て行けって言ったのに、しつこく俺をイラつかせやがって！","ああ、もうこの無礼にはうんざりだぜ。","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("もう行くぜ。","ああ、マーカス…","悪いな、Marcus…","「おっと……」",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("気でも狂ったのか？屠殺屋ごっこがしたかったのか？海賊どもはみんなお前に怒ってるぜ、坊主、 さっさとここから出ていったほうがいいぞ…","どうやらお前、頭がおかしくなったみたいだな、坊主。ちょっと腕を伸ばしたかったのか？悪いが、 ここはお前の来る場所じゃねえ。とっとと失せろ！");
				link.l1 = RandPhraseSimple("聞けよ、この状況を何とかしたいんだ…","この問題を解決するのを手伝ってくれ…");
				link.l1.go = "pirate_town";
				break;
			}
			// Сага - завершаем искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason пиратская линейка патч 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "マーカス、いつまで俺に怒ってるつもりだ？お前の仲間のヴィンセント――一緒にカルタヘナを襲った奴――も助けてやったし、お前の首も救ってやったんだぜ！それとも、バーナードはその話すらお前にしてねえのか？";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "なぜそんなに無礼なんだ、マーカス？ベルナールは俺のこと何も言わなかったのか？";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "仕事を探してるんだが……何か儲かる話でもあるか？";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "俺は売る絹があるんだ。";
				link.l2.go = "Mtraxx_silktrade";
			}
			if (pchar.questTemp.Mtraxx == "silk_14")
			{
				link.l1 = "買い手を見つけてやったぜ。ポートロイヤルの船大工だ。あいつは自分の造船のために船用の絹が必要でな、 毎月百反ずつ、一反につき五ドゥブロンで買い取るって話だ。奴の手下が10日から15日の夜にネグリル岬で品を受け取る。合言葉は「リヨンの商人」だ。 ハゲのジェフリーが最初の分はもうジャマイカに届けてあるぜ。";
				link.l1.go = "mtraxx_13";
			}
			if (pchar.questTemp.Mtraxx == "silk_15")
			{
				link.l1 = "買い手を見つけてやったぜ。ポートロイヤルの船大工だ。自分の造船に使う船用シルクが必要で、毎月百反ずつ、 一反あたりドゥブロン金貨五枚で買い取れるそうだ。奴の手下が10日から15日の夜にネグリル岬で品物を受け取る。合言葉は「リヨンの商人」だ。 この買い手を見つけるのに二ヶ月以上かかったんだぞ。ゲフリーはもうシルクを密輸業者に売っちまったかもしれねえ。 すまねえな、マーカス。";
				link.l1.go = "mtraxx_15";
			}
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
			// Jason НСО
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "チャールズ、なんだこれは！？";
				link.l1 = "マーカス、すべてがうまくいかなかった。俺は来ることも、お前に知らせることもできなかったんだ…";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "会えて嬉しいぜ、相棒！";
				link.l1 = "俺も会えて嬉しいぜ。素晴らしい見世物をありがとう！";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "会えて嬉しいぜ、坊主！どうした、何か用か？";
				link.l1 = "お前に提案があるぜ。海賊にぴったりだろう！";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "そいつが俺たちの客だ！仕事は終わったぜ、お前のバロンは厳重に警備された地下牢にぶち込まれてる。見に行きたいか、 へへっ？！";
				link.l1 = "それをやる時間ならたっぷりあるさ、ははは。あいつはちゃんと扱われてるのか？";
				link.l1.go = "patria_10";
				break;
			}
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "俺にやらせたい仕事でもあるのか？";
				link.l1 = "よう、Marcus。ああ、一件だけだ。儲かるし、海賊らしい仕事だぜ。";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "金は持ってきたか？";
				link.l1 = "俺がやった。";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "そいつが俺たちの客だ！仕事は終わったぜ、お前のバロンは厳重に警備された地下牢にぶち込まれてる。見に行きたいか、 へへっ？！";
				link.l1 = "それをやる時間ならたっぷりあるぜ、はは。あいつはちゃんと扱われてるのか？";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "チャールズ、なんだよ、くそっ！？";
				link.l1 = "マーカス、すべてがうまくいかなかった。俺は行くことも知らせることもできなかったんだ…";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "「こいつが俺たちの操り人形使いだ！」";
				link.l1 = "ハハハ！見世物は最高だったぜ！";
				link.l1.go = "patria_x29";
				break;
			}
			// Тени прошлого
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "会えて嬉しいぜ、坊主！どうした、何か用か？";
				link.l1 = "マーカス、話があるんだ。気に入らねえかもしれねえが、それでもお前の助けが必要なんだ。";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "「はっ、ここにいたか、」 "+pchar.name+"……お前の到着を待っていたぜ。トルトゥーガの件で森の悪魔に悩まされてるって話、まったく困ったもんだ……";
				link.l1 = "奴が言ってたぜ、お前が解決策を見つけたってな。俺の言う通りか？";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "俺は絹を売りたいんだ。";
				link.l2.go = "Mtraxx_silktrade";
			}
			
			link.l0 = ""+npchar.name+"、私は" + GetSexPhrase("","") + " 海での安全について話したいんだ。沿岸の兄弟団の連中が、私のつつましい身に過剰な興味を示しているんだ。 少し黙らせてもらえないか？";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+"、会えて嬉しいぜ！今回は何の用だ？","何の用だ？","またか？用がねえなら人の邪魔すんじゃねえ！","お前は "+GetSexPhrase("腕の立つ私掠船長","いい娘だ")+"、だから今は生かしておいてやる。だが、もうお前とは話したくねえ。","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("ただ会いに来ただけだぜ。","「何もねえ。」","わかった、マーカス、悪かったな。","くそっ、本当にすまねえ、Marcus！",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("強盗だと！？許せねえ！死ぬ覚悟しろ、このクズ野郎…","おい、そこで何してやがる？！俺を盗もうってのか？もう終わりだぜ……","待て、なんだと！？やっぱりお前は泥棒じゃねえか！ここで終わりだ、この野郎…");
			link.l1 = LinkRandPhrase("くそっ！","「カランバ！」","「ああ、くそっ！」");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("消えろ","消えろ")+" ここからだ！","俺の家から出ていけ！");
			link.l1 = "「おっと……」";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "くだらねえ話で俺の仕事の邪魔をするな。\n次はただじゃ済まねえぞ……";
        			link.l1 = "了解だ、Marcus。";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("お前にはもううんざりだ。","俺はお前と話したくねえんだ。だから、俺に近づくんじゃねえぞ。");
			link.l1 = RandPhraseSimple("「さて……」","ふん、まあいいだろう…");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "これ以上くだらねえ話で俺を邪魔するんじゃねえぞ、さもないと殺すしかなくなるからな。正直、 そんなことはしたくねえんだがな。";
        			link.l1 = "それは間違いないさ、Marcus、俺は絶対に……";
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
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
//--> -----------------------------Сага - Искушение Барбазона завершающие этапы---------------------------
		case "Temptation":
			dialog.text = "はっ！トルクの英雄だと？荒っぽい挨拶ですまねえな、坊主。 ベルナールからお前の目覚ましい活躍のことはもう聞いてるし、俺への罠についても何やら話してたぜ。 詳しい話を聞かせてもらおうか…";
			link.l1 = "まさしく罠だったな。奴らが狙っていたのはお前で、ベルナールじゃねえ。あいつはただの囮だったんだ。";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "計画は単純だった。お前は仲間を救い出し、一番乗りで『セパレーター』に乗り込むはずだった。\nそしてその瞬間、やつらは船に砲撃を浴びせて木っ端微塵に吹き飛ばす手はずだったんだ。\nあのブリガンティンは、まるで地獄の硫黄みたいに火薬を積み込んであったのさ。";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "くそっ！誰の狂った考えだ、あれは！？それに、どうやってバーナードの隠れ場所を見つけろってんだよ！？";
			link.l1 = "その計画を立てたのはジャックマンと弟のデイビッドだ。\n「セパレーター」がトークス南の湾でお前の助けを待っていると、使者がお前に伝えるはずだった。\nその使者役に俺を選んだ――それが奴らの失敗だったのさ。";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "わからねえ！お前はこの一件でどんな役割なんだ？";
			link.l1 = "俺はあの野郎ジャックマンをずっと見張ってきたんだぜ。ヤン・スヴェンソンと組んでる、知らねえなら覚えとけ。 森の悪魔と俺で、あいつの正体を暴くことにしたんだ。ヤンはブレイズの死は全部あいつのせいだと確信してるし、 スティーブンは無実で罪を着せられたってわけだ。";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //патч 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "へっ！だがな、ブレイズの死体からイニシャル入りのサメの歯が見つかったんだ――S.D.――これはスティーヴンのもんだって誰でも知ってるぜ…";
			link.l1 = "全部仕組まれていたんだ。ジャックマンは大きな賭けに出た。ナサニエル・ホークを排除してマルーンタウンの座を奪い、 さらにシャープを殺してその罪をシャークに着せたんだ。奴の悪事の証拠は十分にある。ジェイコブの箱で見つけたんだ。 そこにシャープの地図の後半とホークの破片があった。";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "くそっ！じゃあスティーブンは無実だったのか？それで、なんでジェイコブがこんなことをしたんだ？";
			link.l1 = "奴は自分がバッカニア同盟の頭になるつもりで、イスラ・テソロに関わる何かを期待していたんだ。 お前とスヴェンソンの支持を得られなかったから、二人まとめて始末しようと決めた。最初に狙われたのはお前だ。 最も危険なヤンは二番目だった。";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "あの野郎はどこだ！？ぶっ殺してやる！";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "ジャックマンとその弟、それに奴の猟犬どもは全員死んだ。俺が直々に片付けてやったぜ。 あのクソ野郎はもう誰にも害を及ぼさねえ。\nマーカス、スティーブン・ドッドソンに票を入れてくれねえか？これは俺の個人的な頼みだ。";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "ジャックマンとその弟、それに他の猟師どもも全員くたばったぜ。俺が直々に片付けてやった。 このクソ野郎はもう誰にも手出しできねえ。残念だが、スティーブンは殺された……";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "ああ、もちろん投票するぜ！ブレイズの次にふさわしいのはシャークだと、ずっと思ってたんだ。しかも、 あいつが有罪だって、ほとんど信じかけてた。俺たちみんなそうだった！ほら、俺の欠片を持っていけ。";
			link.l1 = "よし！これで自由に息ができるぜ。";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "そうだな……お前はシャークの利権を代表してるってわけか？";
			link.l1 = "ああ。ヤン・スヴェンソンと俺だ。よし、マーカス、またな！";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "死んだだと！？どうやってだ？これもジャックマンの仕業か？";
			link.l1 = "いや、あいつのボースンがやったんだ。名前はチャド・キャッパーだ。もう報いは受けたさ……マーカス、スヴェンソンはお前こそが新しいバラナーズの頭にふさわしいと思ってる。 他のバロンどももこの決定を支持するだろう。受けるか？\n";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "へっ！そんなこと、いちいち聞くなよ。兄弟団の頭になるのは大きな名誉だぜ！俺が反対するなんて、 考えるんじゃねえぞ。";
			link.l1 = "いいだろう。これを受け入れてくれて嬉しいぜ。";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "ほら、俺の欠片を持っていけ。スヴェンソンに届けろ。奴が仕切ってるんだろう？";
			link.l1 = "ああ、そうだ。よし、マーカス、またな！";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "ああ、そして俺の友人ベルナールを助けてくれて礼を言いたいんだ。ほら、この金貨の詰まった袋を受け取れ。";
			link.l1 = "ありがとう！じゃあな！";
			link.l1.go = "Temptation_exit";
		break;
		
		case "Temptation_exit":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("You have received 300 doubloons");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "25");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "Temptation_13":
			dialog.text = "ああ、チャーリー・プリンスがタークスに華々しく現れたって話は聞いたぜ…俺の命を救ったって？どうやってだ？バーナードが罠について何か言ってたが…";
			link.l1 = "ああ、罠だったんだぜ。お前が標的で、ベルナールはただの囮だったんだ…";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "ハハハ、森の悪魔の下で働いてるのか、旦那？で、俺と組んでた時より稼げてるのか？正直に言えよ！";
			link.l1 = "マーカス、過去のことはもう水に流そうぜ。今は共通の目的がある、それは隊商を襲うよりもずっと大事だ。くそっ！ 今はそれが一番重要なんだ！兄弟団の未来がかかってるんだぞ！";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "わかったぜ、旦那。お前は自由な私掠船乗りだもんな、森の悪魔のために働くのはお前自身の選択だったってわけだ……悪くない決断だぜ……で、スティーブンのことだが……お前、あいつが中傷されたって言ったよな？";
			link.l1 = "まったくその通りだ。";
			link.l1.go = "Temptation_4";
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "ああ、できる限り手を貸すぜ！続けろよ。";
			link.l1 = "見てみろ、マーカス……これはサメの歯だ。これについて何か知ってるか？";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "ははっ！それはスティーブン・ドッドソンが女の子にいいところを見せようとして仕留めたホオジロザメの歯だぜ。 あいつはそれ以来「シャーク」って呼ばれてる。あんなもんをサーベル一本で水中で仕留められる奴なんて、 そうはいねえよ。でもあいつは若くて無鉄砲だったし、ベアトリス・シャープはカリブ一の美女だったからな……で、お前はどうやってそれを手に入れたんだ？";
			link.l1 = "それはセント・ジョンズの元死刑執行人からもらったものだ。この歯で一人の男を殺した。その名は……ジョシュア・リードビーターだ。";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "それは昔の話だ。スティーブンがその男を殺したんだ。ベアトリスの死にショックを受けて、 リードベーターだけがその責任者だと思い込んでいた。しかし後になって、ジョシュアの死体から何枚かの書類を見つけ、 それを調べて自分の行いを悔いたんだ。\nベアトリスの死は仮面のせいじゃない。仮面が必要としていたのはブッチャーだけだったんだ。全部仕組んだのは、 ブッチャーの嫉妬深い元恋人ジェシカだったのさ。";
			link.l1 = "「その書類を読んだか？」";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "なんで俺がそんなことしなきゃなんねえんだ？もちろん違うぜ。あいつらには興味なかったんだよ。ただな、 もし暇があるなら、仮面野郎がブッチャーを追いかけてた理由を教えてやってもいいぜ。 酔っ払いのスティーブンが何度もこの話を聞かせてくれたからな。";
			link.l1 = "時間ならあるぜ。信じろ、俺の興味にはちゃんと目的があるんだ。下手すりゃこの話を俺が書いてもいいくらいだ。";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "お前が時間を無駄にしない奴だってことは知ってるぜ。じゃあ聞け。 ジョシュア・リードビーターはイギリス海軍の艦長で、伝説の『ネプチューン』はあいつの指揮下にあったんだ…";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "…だがリードビーターは生き延びて、通りかかった船に拾われた。傷は彼の顔を醜くし、それ以来ずっと仮面をつけている。 しばらくして、人々は彼を「仮面」と呼ぶようになった。自分に一生消えない傷を負わせた男への復讐だけが、 彼の唯一の目的となった。";
			link.l1 = "そうか……全部書き留めたぜ。もう一度読み返して、今持ってる情報と照らし合わせる必要がありそうだな。まったく、悲しい話だ。 お前、ジェシカを見たことがあるか？";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "ああ、もちろんだ！ジェシカはブッチャーの全ての航海に付き添っていたが、 ブッチャーがベアトリスのために彼女を捨てるまでだった。そのことはジェシカには絶対に許せなかった。人々は彼女を 「ブッチャーの護符」と呼んでいた、なぜなら彼女がそばにいる間は、いつもブッチャーに幸運が訪れていたからだ。\n信じるかどうかはお前次第だが、ブッチャーがバルバドスでジェシカを手放した途端、奴の運は尽き始め、 戦利品もショボくなり、『ネプチューン号』はイサ・テソロの造船所の常連になった。でも、 それはブッチャーがほとんどの時間を船尾甲板じゃなくて、ベアトリスとキャビンで過ごしていたせいだとも言えるな。\nベアトリスはジェシカとは違っていた。冒険や戦争に夢中じゃなかったし、ニコラスが剣術や航海術を教えたけど、 海のロマンスは好きでも、彼女には十分な鋼がなかった。ブッチャーの『ネプチューン号』 は彼女にふさわしい場所じゃなかった。結局、それが彼女の命を奪ったんだ。";
			link.l1 = "「それで、ジェシカはどうするんだ？」";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "ああ、あいつは本当にすごかったぜ……「ネプチューン号」の船乗りは皆、彼女の命令に従ったんだ。ただ船長の女だからってだけじゃねえ。 ジェスは剣術も航海術も一流だった。ブッチャーの努力は無駄じゃなかったってわけさ。 あいつは気が強くて向こう見ずで、しかもとびきりの美人だった。多くの男が一晩を共にしたがったが、 ジェスが欲しかったのはブッチャーだけだった。ちょっかいを出すのは命知らずの所業だったな。 実際に痛い目を見た奴も多いし、しつこい連中には剣術の稽古が人生最後の授業になったもんだ。 ジェスはカリブで唯一の特別な剣を持っていた。どこで手に入れたのかは俺も知らねえ。炎のように波打つ刃の剣だ。 素手で掴むなんて無理だし、ちょっと触れただけでひどい傷を負う。ジェスは生まれつきの冒険者じゃなく、 志で冒険者になった女だ。そうだ、もっと知りたきゃお前の知り合いに聞いてみな。俺よりずっと詳しく話してくれるぜ。 \n";
			link.l1 = "本当か？それで、そいつは誰だ？";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "ヤン・スヴェンソン。森の悪魔は決して認めなかったが、ジェシカに対して何か企みがあったんだ。あの頃、 すでに西メインを手中に収め、名声も羨まれるほどで、だからこそあの女豹は彼にふさわしかったのさ。\nブッチャーがジェスを始末した後、ヤンはやけに頻繁にバルバドスへ顔を出すようになり、 駐屯兵たちを恐怖で震え上がらせていた。知っての通り、ジェシカはブリッジタウンのプランターの娘だった。\nまあ、彼の意図は裏社会では有名だったが、誰もそれについて口に出す勇気はなかった。 今でこそヤンはブルーウェルドで尻を据えているが、当時は彼に対して下手なことを言えば命取りだったぜ。\n結局、二人はうまくいかなかった。ジェスはブッチャーの裏切りの痛みに耐えられず、一年後、 仮面の助けを借りて復讐を果たした。この復讐は全員にとって最悪の結末となった――ブッチャーも、ベアトリスも、仮面も、そしてジェス自身も。みんな死んじまったのさ。";
			link.l1 = "いや、ブッチャーはまだ生きてるぜ。";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "「なんだと！？俺の聞き間違いか！？あいつが生きてるだと！？」";
			link.l1 = "ああ。ブッチャー船長は絞首刑にならなかった。いや、実際にはなったんだが、 ジェイコブ・ジャックマンと首吊りヘンリーが死刑執行人を脅かしたおかげで、生き延びたんだ。 絞首刑はただの見せかけだった。証拠もあるぜ。";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "信じられねえ！で、そいつは今どこにいるんだ？";
			link.l1 = "奴の名はローレンス・ベルトロップ、ポートロイヤルに住んでいる。\nだが、どうやら相変わらず危険な野郎のままだぜ。ブレザレンの中で散々厄介ごとを起こしてきたジャックマンも、 奴の命令に従っていたんだ。";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "くそっ！結局、四分士が自分の船長を見つけやがったか！何年も経ったってのに……ベルトロップだと……待てよ！今わかったぜ、ブレイズの書類にあったあの妙な尋問手順の理由が……どうやらブレイズはブッチャー＝ベルトロップについて何か面白いことを掴んだらしいな……";
			link.l1 = "何の話だ？";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "俺がこの屋敷を手に入れた時、ブレイズの書類を少し調べる時間を取ったんだ。\nサミュエル・ブルックスという名の人物に関する尋問記録を見つけたぜ。\nそこには、有名な海賊でニコラス・シャープの一番の親友、トーマス・ベルトロープの冒険について詳しく書かれていた。 \nどうやらそいつがブッチャーの親父らしいな。";
			link.l1 = "面白いな。ベルトロップとシャープのガキどもが親父たちの仕事を引き継いだってわけか……";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "そうらしいな……なあ、友よ、なんでお前はとっくにくたばった連中の過去なんかにそんなに興味があるんだ？一体何のつもりだ？\n";
			link.l1 = "エレン・マッカーサーがベアトリス・シャープの娘であり、ニコラス・シャープの孫であること、 そしてこの姓を名乗る正当な権利があることを証明する書類が必要だ。\nたとえ彼女の姓がベルトロップかもしれなくても、そんなことはどうでもいい。";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "ブレイズの記録にはエレン・マッカーサーについて何も見つからなかった。\nベアトリスが自分の姪の誕生をブレイズに知らせなかったのは奇妙だ。彼女らしくないな。";
			link.l1 = "聞けよ、シャープの書類にこの話について他に何か書いてねえか？俺は手に入る限りの詳細が必要なんだ！";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "ふむ……そうかもな。ブレイズの記録によれば、奴は妹が死んだ島を探していたらしい。 リードベーターの討伐遠征に関する公文書の写しもあるが、面白いものは何もねえ、緯度の数字がいくつかあるだけだ。\nこの緯線はカリブ海の北部を横切っている。だが経度の手がかりはねえ。明らかにブレイズの探索は失敗したんだろうな。 その緯度にどれだけ小島があるか、想像もつかねえぜ。";
			link.l1 = "「で、緯度はどうなってるんだ？」";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "そうだな……ほら、21度32分北だ。これがどう役に立つかは知らねえがな。";
			link.l1 = "できるさ。マーカス、正直な話をしてくれて本当にありがとう。また会おうぜ！";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "さて、俺がお前のためにできることがあるぜ。知っての通り、トルトゥーガの治安はラ・ロシュ砦だけじゃなく、 島の沿岸を常に見張ってる海賊艦隊によっても守られてるんだ。トルトゥーガの港は安全だ、あいつらは腕が立つし、 強力な船を持ってる。ルヴァスールは長い間、こういう船長たちを引き寄せてきたんだ。\nあいつらは戦列艦隊相手でも戦える連中で、本気の敵になるぜ。だからな、俺は掟の番人であり、 コースト同盟の頭でもあるから、こいつらの番犬どもをトルトゥーガの沿岸から引き上げさせることができるってわけだ。 ";
			link.l1 = "「それで全部か？」";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "それで十分じゃねえか？これ以上は手伝えねえんだよ。砦をぶっ壊すしかねえが、 少なくともあの護衛艦どもとは戦わなくていい。信じろ、あいつらは砦より危ねえからな。俺の助けがあれば、 少しは楽になるぜ。";
			link.l1 = "まあ、どうせ襲うことになるなら、海賊艦隊が出て行くのは本当に助かるぜ。ありがとな、マーカス！\nいつトルトゥーガを攻撃できるんだ？";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "いつでも好きな時にしろ。俺の合図で護衛船は出発するぜ。";
			link.l1 = "いいだろう。今から準備しなきゃならねえ。";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// Левассера - к барьеру!
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		break;
		
		case "pirate_town":
            dialog.text = "問題を解決しろだと？自分が何をやらかしたかわかってんのか？まあいい、とにかく百万ペソ持ってこい。 そうすりゃ野郎どもにお前のやったことを忘れさせてやる。気に入らねえなら、とっとと地獄へ行きやがれ。";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "よし、払う準備はできてるぜ。";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "さらば……";
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
            dialog.text = "よし！これでまた潔白だと思え。ただし、もう二度とそんな汚ねえ真似はするんじゃねえぞ。";
			link.l1 = "俺はやめとくぜ。俺には高すぎるんだ。じゃあな…";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		// Addon 2016-1 Jason ------------------------- пиратская линейка --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "まずは自分の船を手に入れろ、それから仕事を頼め。陸のネズミに用はねえんだ。とっとと失せろ！";
				link.l1 = "ふむ……なるほどな。";
				link.l1.go = "exit";
				break;
			}
			if(ChangeCharacterHunterScore(Pchar, "spahunter", 0) > 10)
			{
				dialog.text = "頭がおかしくなったのか？スペインの半分がてめえを追ってるんだぜ。お前が動けば余計に面倒が増えるだけだ。 まず自分の問題を片付けてから出直せ。それだけだ！さっさと失せろ！";
				link.l1 = "ふむ……なるほどな。";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "何か面白いことを探してるのか、あぁ？ハハッ！いいだろう…だが警告しておくぜ、坊主。俺と一緒にいる限り、安らぎなんてねえぞ。火薬の匂いが怖いとか、 血を流すのができねえなら、とっとと出て行け。臆病者は大嫌いなんだ。 仲間の取り分を盗むようなチクリやネズミ野郎も、俺の下じゃ長くは生きられねえ。どうする？乗るのか？";
			link.l1 = "俺はやるぜ、マーカス。戦うのは怖くねえし、俺を臆病者とか裏切り者だなんて言える野郎は一人もいねえ。";
			link.l1.go = "Mtraxx_1";
			link.l2 = "おいおい、そりゃ俺には荷が重すぎるぜ！悪いな、マーカス、だが俺はここで失礼させてもらうぜ…";
			link.l2.go = "Mtraxx_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "なんだ、まだここにいるのか？";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "俺は売りたい絹があるんだ。";
				link.l2.go = "Mtraxx_silktrade";
				link.l1 = "もう行くぜ。";
				link.l1.go = "exit";
				break;
			}
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "ハハッ、さてさて、俺の勇敢なちびっこ海賊よ、じゃあ取引の話でもしようか。\nサントドミンゴにいる俺の情報屋が教えてくれたんだが、スペインの船長でな、 青い琥珀を持ちすぎて娼婦にまでばらまいてる奴がいるらしい。\n青い琥珀って聞いたことあるか？";
			link.l1 = "あるぜ。珍しくて貴重な石だ。";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "その通りだ。ここでも銀行家や宝石商はそれにいい金を払うし、古き良きヨーロッパじゃ十倍の値がつく。 カリブじゃ琥珀自体は珍しくねえが、青い琥珀となりゃ話は別だ。そして今、カスティーリャのずる賢い野郎が、 キューバやイスパニョーラの銀行家どもが持ってる黄色い琥珀を全部合わせたよりも、 青い琥珀をたくさん持ってるって自慢してやがるんだ。";
			link.l1 = "酔っ払ったスペイン野郎の話なんざ信用できるか？ドゥブロン金貨を三枚拾っただけで、 エルドラドを見つけたってみんなに吹聴してやがる\n";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "俺ならやらなかったが、あいつは実際に青い琥珀を娼婦どもにばらまいてたんだ。 自慢話にも多少は真実があるってことだろうな。サントドミンゴへ行って調べてこい。もし青い琥珀の鉱床を見つけたら、 なおさらいいぜ。これをやり遂げたら、ラ・ベガでの報酬と尊敬は保証してやる。";
			link.l1 = "もしお前の情報が役に立たなかったらどうするんだ？";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "なら、そのカスティーリャ野郎が嘘つきだって証明してみろ。";
			link.l1 = "よし。サント・ドミンゴでのお前の情報源は誰だ？";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 60 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 60) 
					{
						sTemp = ". Wait a minute, take a trading license for 60 days."; 
						GiveNationLicence(HOLLAND, 60);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ". Wait a minute, take a 60-day trade license and a Spanish flag to land in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
						GiveNationLicence(HOLLAND, 60);
						STH_SetJokerFlag(SPAIN, true);
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 60) 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here you go, a 60-day trading license, longer than yours. As well as the Spanish flag for landing in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							GiveNationLicence(HOLLAND, 60);
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here, take the Spanish flag for the Santo Domingo landings. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "ガブリエラ・チャパドという娼館の女が必要だ。俺の名前と合言葉「琥珀の首飾り」を伝えろ。 詳しいことはあいつが教えてくれる。\n時間を無駄にするなよ――情報はまだ新しいが、一日二日もすれば古くなるかもしれねえからな。"+sTemp;
			link.l1 = "了解だ、Marcus。サントドミンゴに向かうぜ。";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // конфликт с делом чести
			pchar.questTemp.ZA.Block = true;			// конфликт с квестом "Заносчивый аристократ"
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
			AddMapQuestMarkCity("SantoDomingo", false);
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "お前の到着はもう聞いてるぜ。さっさと報告しろ！";
			link.l1 = "あの青い琥珀好きの野郎は片付けたぜ、楽じゃなかったがな。奴の隠し場所を突き止めて、しっかり奪ってきた。 お前に持ってきたぞ\n "+FindRussianQtyString(i)+" 青い琥珀のかけら。";
			link.l1.go = "mtraxx_8";
			DelLandQuestMark(characterFromId("Terrax"));
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "ほうほう……息子よ、俺がネズミになる危険について警告したのを覚えてるか？そのときお前はなんて言った？ 誰にも責められねえってか？俺をバカだと思ってるのか、ガキ。お前が略奪したことぐらい、ちゃんと分かってるぜ\n "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" モスキート海岸の青い琥珀のかけらだ。さあ、走れ、小ネズミ。走ってろ、二度と俺と会わねえようにな！";
				link.l1 = "くそっ！";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
				// belamour legendary edition забрать флаг обратно
				if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
				{
					DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
					STH_SetJokerFlag(SPAIN, false); 
					log_info("You have given spanish flag");
				}
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "よくやったな、坊主！やるじゃねえか。厄介な仕事をうまく片付けて、奪ったものも全部持ってきたな。いい働きだぜ！ 俺の見込みが間違ってなかったってわけだ。";
				link.l1 = "俺の取り分はどうなってるんだ、マーカス？";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty)/2;
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+FindRussianQtyString(i)+" pieces of blue amber");
			TakeNItems(pchar, "jewelry7", i);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given spanish flag");
			}
            dialog.text = "まさに本物の海賊の口ぶりだな、ハハハ！戦利品の半分はお前のもんだ。持っていけ。";
			link.l1 = "ありがとな、船長。俺に他に用はあるか？";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_Set("ach_57");
		break;
		
		case "mtraxx_10":
            dialog.text = "腕の立つ奴にはいつでも仕事があるぜ。今回はお前に頼みたい繊細な案件があるんだ。カプスターヴィルに停泊している 「スネーク」号って船がある。指揮してるのはジェフリー・ブルック、通称ハゲのジェフリーだ。あいつは俺の手下だよ。 戦いは抜群に強いし、銃や刃物のことなら何でも知ってるが、それ以外のことになるとまるっきりのバカだ。まあ、 ハゲをあまり責めてやるな、完璧な奴なんていねえからな、ははは！\nさて、そのタフガイがサン・マルタン北方でオランダの護送船団を襲って、小麦袋を積んだバーク船を拿捕したんだ。 だがな、袋の中から隠してあった船用の絹を見つけやがった。しかもかなりの大荷物だ。 この品はとんでもなく貴重で珍しい。オランダ人が軍用のためだけにヨーロッパから運んでくる代物だ。 その絹は特別な帆に使われて、船の速度や風上航行能力を上げるんだ。まず手に入らねえし、 売るのは簡単でも値段をうまく引き出すのが難しい。あのクソ商人どもはいつも値切りやがる！\nだがな、カリブにはこの絹をドブロン金貨でちゃんと買う気のある奴らがいるって俺は知ってる。お前の仕事は、 そういう奴を見つけることだ。何？キャラバンを襲うのは馬鹿でもできるが、 商売は脳みそが少しでも詰まってる奴にしかできねえんだよ。俺はこれから毎月船用の絹を売るつもりだから、お前は1ロールにつき最低4枚の金ドブロンを払う定期の買い手を見つけろ。猶予は2ヶ月だ。いつまでもハゲのジェフリーをカプスターヴィルに置いておけねえからな。以上だ。 さっさとカプスターヴィルへ行って、ジェフリーがその荷を密輸業者に二束三文で売り飛ばす前に話をつけてこい。 あいつがちょっと「単純」だってのはもう言ったよな。";
			link.l1 = "ふん…わかった。もう向かってるぜ。";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "はっ！ここに勇敢な船長が来たぜ "+GetFullName(pchar)+"「！買い手はどうするんだ？」";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "買い手を見つけてやったぜ。ポートロイヤルの船大工だ。あいつは自分の工房で使う船用の絹を必要としていて、 毎月百反ずつ、一反につき五ドゥブロンで買い取るってよ。奴の手下が10日から15日の夜にネグリル岬で品物を受け取る。合言葉は「リヨンの商人」だ。 こんな買い手を見つけるのに二ヶ月以上かかったぜ……ゲフリーはもう絹を密輸業者に売っちまったかもしれねえな。悪いな、マーカス。";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "買い手を見つけてやったぜ。ポートロイヤルの船大工だ。あいつは自分の造船に使う船用の絹が必要でな、毎月百反ずつ、 一反につき五ドゥブロンで買い取るってさ。10日から15日の夜にネグリル岬で、あいつの手下が品物を受け取る。合言葉は「リヨンの商人」だ。 ハゲのジェフリーが最初の分をすでにジャマイカに届けてるぜ。";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "そいつはいいな、相棒！よくやったじゃねえか。両手と頭を使える奴なんざ、なかなかいねえんだよ。20日後に俺のところへ来い、報酬を渡してやる。その頃にはハゲのジェフリーが最初の取引の金を持ってきてるはずだ。"; // правки прогона 3
			link.l1 = "よし、Marcus。またすぐ会おうぜ。次の仕事も用意しておけよ。";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "ああ、やってやるぜ。また後でな。";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // правки прогона 3
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "惜しいが、それでも大成功だ。よくやったな！ジェフリーの分け前はやらねえが、報酬はやる価値があるぜ。\n一か月後に俺のところへ来い。その頃には最初の品をお前の買い手に売ってるはずだ。そしたら話をしようじゃねえか。";
			link.l1 = "よし、Marcus。またすぐ会おうぜ。次の仕事も用意しといてくれよ。";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			//pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "「そこにいたか、」 "+pchar.name+"。報酬について話そうか。";
			link.l1 = "こういう話は好きだぜ、ハハハ！全部聞いてやるよ。";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "ハゲのジェフリーが、お前の買い手に最初の船用シルク105反を売ったぜ。俺は1反につき4ドゥブロンで売るつもりだったから、その差額をお前に渡すのが筋だろう。そう決めた。お前の取り分は105ドゥブロン、さらにボーナスとして1反ごとに1ドゥブロンだ。合計で210ドゥブロンになる。ほら、受け取れ。";
			link.l1 = "ありがとう、Marcus！";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 210);
			PlaySound("interface\important_item.wav");
            dialog.text = "もう一つ言っておくぜ。これでさらに儲けることもできるぞ。";
			link.l1 = "面白いな……続けろ。";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "お前の買い手は、今後二ヶ月の間に百反以上の絹を欲しがっている。もし持っているなら、 二十反から百反までを一反五ドゥブロンで俺のところに持ってこい。この取引は二ヶ月間有効だ。";
			link.l1 = "いいだろう！まだあればもっと持ってきてやるぜ。";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// торговля шелком
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "どれだけ持ってるんだ？";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
            dialog.text = "上出来だ。金を持っていけ――約束通り、一回につき5ドゥブロンだ。";
			link.l1 = "感謝だぜ！";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 500);
            dialog.text = "百本もらうぜ。金を受け取れ――一本につき五ドゥブロン、約束通りだ。";
			link.l1 = "感謝だぜ！";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "もっと差し迫った話をしようぜ、危ねえことに関わる気はあるか？";
			link.l1 = "ああ！俺と部下たちはすぐにでも出航できるぜ。";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "くそったれ、 "+pchar.name+"「おい、どこほっつき歩いてやがったんだ？俺が会いに来いって言ったの覚えてるか？ お前にやらせる仕事があったんだがな、見事なタイミングのせいで全部パーだ。まったく、俺を怒らせてくれるぜ、坊主。 消えろ、信用できねえ奴とは仕事しねえんだよ。」";
			link.l1 = "くそっ……";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) 
					{
						sTemp = ", as well as a trade license for 40 days."; 
						GiveNationLicence(HOLLAND, 40);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ", as well as a trade license for 40 days. Besides, how are you going to fool the bungler in the fort?! You will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
						GiveNationLicence(HOLLAND, 40);
						STH_SetJokerFlag(SPAIN, true);
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 40) 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here, a trading license for 40 days, more than yours. As well as the Spanish flag for landing in Maracaibo. You will return it upon arrival. The new generation, pah...";
							GiveNationLicence(HOLLAND, 40);
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "じゃあ、よく聞け。二ヶ月前、ジャン・ピカードって名の船長――ジャン・ザ・ハンサムとも呼ばれてる奴――と会う約束をしてたんだが、奴は現れなかった。俺はそいつと重要な話をするつもりだったから、行方を調べてみた。 そしたら、あの勇敢な私掠船乗りとそのブリガンティンが、 ドン・エドゥアルド・デ・ロサド指揮下のスペイン重ガレオンと戦闘になったらしい。しかもあの野郎、手強いんだよ。 その結果、ジャンと生き残った部下どもはマラカイボに連れて行かれて、現地のプランテーションに売り飛ばされた。 今はそこで、真面目に働いてるってわけだ。\nお前の任務はこうだ。まず第一に、奴の不運の詳細を調べろ。次に、奴をプランテーションから生きて連れ出して、 ここまで連れて来い。奴の話の詳細がどうしても必要なんだ。そのために「モレイ」ってバルク船の船長を一人、 お前の補佐につけてやる。船長の名はポール・チャント、通称ペリー・ザ・カトラスだ。ジェフリーを覚えてるか？ あいつと同じくらいバカだが、戦いは得意だ。\n奴はバルバドスのラゲット岬でお前を待ってる。「モレイ」とその船長を見つけて、マラカイボへ向かえ。 カトラスは余計な質問もせずにお前の命令に従う。いや、そもそも質問なんかしねえ。 とにかく仕事を片付けて戻ってこい、ここで待ってる。将来の出費に備えて一万ペソやる。"+sTemp+"。何か質問はあるか？";
			link.l1 = "いや、問題ねえ。全部はっきりしてる。バルバドスへ向かうぜ。";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "じゃあ、幸運を祈るぜ。急げよ、カトラスと可哀想なジャンを待たせるんじゃねえぞ。";
			link.l1 = "あいよ、親分！今行くぜ。";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			// belamour legendary edition по пути могут заскочить к Московиту, если рабов нет
			pchar.questTemp.Mtraxx.GiveMeSlaves = "Baster";
			AddQuestRecord("Roger_3", "1");
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "おかえり、俺の勇敢なコルセアよ、ハハッ！スペインの艦隊をぶっ潰したのか？ピカールからもう聞いてるぜ。 よくやったな！";
			link.l1 = "ああ、マラカイボから逃げる時に、俺の連中があいつらをしっかりぶちのめしてやったぜ。";
			link.l1.go = "mtraxx_28";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup3"))
			{
				dialog.text = "おかえり、俺の勇敢なコルセアよ、ハハハ！ピカードからもう聞いてるぜ。よくやったな！";
				link.l1 = "...";
				link.l1.go = "mtraxx_28";
			}
		break;
		
		case "mtraxx_28":
            dialog.text = "お前の目を見りゃ、報酬を待ってるのがわかるぜ。まあ当然だな。ジャンが払うさ、 結局あそこで助けようとしたのはあいつの命だったからな。請求書は後で送れ――あの坊主は今、船も仲間もいねえんだ。あいつはお前と同じで頭の切れる奴だ、だから今の状況もすぐに変わるだろうよ。 ";
			link.l1 = "ふん…まあ…しばらく様子を見るとするか。何か仕事はあるか、マーカス？誰かを助けたり探したりするやつじゃねえだろうな？";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "一番の切れ者でいるのが嫌になったか？残念だが、がっかりさせてやるぜ。 カトラスみたいな脳筋野郎はもう十分いるからな。お前の腕前はちゃんと使わせてもらう。 ひと月後に仕事をやらせるつもりだ。今はイスラ・テソロへ向かって、パスカル・ラヴォワジエに会ってこい。 あいつはシャープタウンの商人だ。\nあいつが言うには、すぐにでも腕っぷしの強い海賊を寄越してほしいってさ。大仕事らしい――お前の好み通り、頭を使うより弾をぶっ放す方が多そうだな。あいつに顔を出す猶予は一週間だ。 ぐずぐずしてるとこの任務はパーになるぜ。それから、礼儀はわきまえろよ。ごまかそうなんて考えるな。 あの男は兄弟連中の間でも一目置かれてる。さあ行け、そしてひと月後にまた俺の前に現れろ。遅れるんじゃねえぞ！";
			link.l1 = "ああ、マーカス。またな！";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given spanish flag");
			}
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "おいおい！死人が戻ってきたぜ！お前はもう埋めたはずだ、坊主！だが、どうやらまだ生きてやがるな\n";
			link.l1 = "見ての通りだ、マーカス……";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "じゃあ、なぜマラカイボからイスパニョーラまでそんなに時間がかかったんだ？お前はもう俺の組織の人間じゃねえ、 坊主。生きて会えて本当に嬉しいが、ここにお前の仕事はもうねえぞ。";
			link.l1 = "えっ！……なんてこった……";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35 && !bImCasual) // опоздал
			{
				dialog.text = "くそったれ "+pchar.name+"「おい、どこほっつき歩いてたんだ！？一ヶ月後に来いって言っただろうが！ここは軍隊じゃねえが、 少しは規律ってもんがあるんだよ！消え失せろ、もうお前とは仕事しねえ！」";
				link.l1 = "お望み通りに……";
				link.l1.go = "mtraxx_33";
				break;
			}*/
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // рано пришёл
			{
				dialog.text = ""+pchar.name+"「一ヶ月後に会いに来い」と言っただろうが。今はお前に割く時間なんてねえんだよ。";
				link.l1 = "……いいだろう……";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "ラヴォワジエの手先が、お前があいつの黒檀を台無しにしたって言ってたぜ。 俺はお前にネズミみたいな真似はするなって、パスクァーレにはちゃんと筋を通せって警告したはずだ。 お前は俺のルールを両方とも破ったんだ。頭は切れる奴だが、これは許せねえ。さっさとここから失せろ、 二度とこの場所への道を思い出すんじゃねえぞ。";
				link.l1 = "くそっ……";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "ラヴォワジエの手先が言ってたぜ、お前があいつの黒檀を横取りしたってな――全部持ってこなかったらしいな。もし相手が脳みそカラッポのカトラスやボールドだったら、 荷を全部奪えなかったって話も信じたかもしれねえが、お前みたいに頭の切れる奴が……パスクワーレを騙すつもりだったのか？俺は言ったよな、「あいつを裏切るな」って！もうお前には一切信用もねえし、 用もねえ。さっさと失せろ、二度とここへの道は忘れろ！";
				link.l1 = "お前のラヴォワジエも自分がネズミじゃねえか！";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират // правки прогона 3
				dialog.text = "ははっ！チャーリー・プリンス、勇敢な船長だとよ！ラ・ベガじゃそれが新しいあんたの名前だぜ、知らなかったか？で、 乱暴者ごっこは楽しめたか？いや？今回は運の女神に見放されたってわけか？俺の脳なしの手下ども、 カトラスみたいな奴らはこうやって生きてるんだぜ。今日は売春宿で稼いだ金を全部使い果たして騒ぎ、 来週には俺のところに来て、同じような馬鹿どもに給料払うために何千か恵んでくれって泣きついてくる。まあいい。 仕事の話に入るか？";
				link.l1 = "ああ、いいぜ！";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "はっ！チャーリー・プリンス、勇敢な船長だな！ははは！ラヴォワジエの手先が、 お前がうまくやったと俺に言ってきたぜ。うちの守銭奴に少しは敬意を示せたようで、俺も嬉しいぜ。";
			link.l1 = "もう少し気前が良けりゃ悪くねえんだがな…";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // правки прогона 3
            dialog.text = "俺が言っただろ、脳みそが足りねえ野郎や盗品買いの話をよ？そうだ、それだ。 こんな仕事は今後絶対に引き受けるんじゃねえ。カトラスみてえな奴らに任せとけ。\nさて、本題に入るか？";
			link.l1 = "ああ、いいぜ！";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "いいぞ！ジャン・ピカールがここに来る、もっと詳しく話してくれるさ。お前とジャンはこの任務で一緒に働くんだ。 それに、あいつが借りを返すチャンスでもある……ほら、来たぞ！";
			link.l1 = "...";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// преобразуем Пикара
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
		
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "bullet", 40);
			TakeNItems(sld, "gunpowder", 40);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			sld.greeting = "Rocur_03";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "俺の部下があんたの襲撃に加わるぜ。名前はルカ・バヤール、通称ルーク・レプラコーンだ。 あいつとその手下どもはバッカニア――イスパニョーラの森で人生の大半を過ごしてきた狩人だ。だからジャングルを進むのはお手の物さ。 あんたの戦士たちと奴らを組ませりゃ、メリダはもうあんたのもんだ。戦利品の三分の一をやる。 残りはジャンの取り分だ。ジャン、お前は自分の取り分からこの勇敢な船長への借りを返せ。 それが済んだら残りを俺のところに持ってこい。そこで俺たちの間の清算をする。\n質問はあるか？\nよし、最高だ！レプラコーンは港で待ってるぜ。幸運を祈るぞ、コルセアども、ハハハ！";
			link.l1 = "...";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "おかえり、俺の勇敢な殺し屋！お前の襲撃の噂はもう俺たちの耳に入ってるぜ。";
			link.l1 = "聞きたくもねえな。そんなことは知らねえ方がいいんだよ……";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "信じろよ、あいつらがまともだった試しはねえぜ、相棒。まあいい。ピカードはお前への借金を返したのか？";
			link.l1 = "ああ。";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "上出来だな。ルーク・レプラコーンはお前にいい印象を与えたか？";
			link.l1 = "あいつがやった。";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "それで完璧だな。みんな満足してるし、みんな報酬も受け取ってるぜ。";
			link.l1 = "「俺に仕事はあるか、Marcus？」";
			link.l1.go = "mtraxx_44";
			// belamour legendary edition отказ после событий Мериды
			link.l2 = "なあ、マーカス、いろいろ考えたが、この仕事は俺には向いてねえ。悪いが、もう決めたんだ。";
			link.l2.go = "mtraxx_44a";
		break;
		
		case "mtraxx_44":
            dialog.text = "まだ本格的な仕事はねえ。ただ、個人的に頼みたいことがあるんだ。興味あるか？";
			link.l1 = "ああ、親分。どんな頼みだ？";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "ラ・ベガの岸近くに「キティ」というピナスが停泊している。何日もそこにいて、 ブリッジタウンへの護衛を待っているんだ。あんなところに一隻で行かせるわけにはいかねえ、理由は言わずもがなだ。 お前、あいつを護衛してやってくれねえか？戻ってきたら本当の仕事をやらせてやるぜ。もちろん、 この護衛の報酬もちゃんと払うからな。\n";
			link.l1 = "取引成立だ。";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "いいぞ！見事な航海だな。";
			link.l1 = "ありがとよ！";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		// belamour legendary edition -->
		case "mtraxx_44a":
            dialog.text = "「なんだと！？俺がお前を路地から拾い上げて、琥珀や宝石で懐を満たしてやったんだぜ！それでこの仕打ちか？」";
			link.l1 = "メリダで俺は、この仕事にはまだ非情さが足りねえって思い知らされたぜ。お前やお前の部下ほど冷酷にはなれねえ。 だが、残酷にはなるなよ。";
			link.l1.go = "mtraxx_45a";
		break;
		
		case "mtraxx_45a":
            dialog.text = "弱虫め！さっさと失せろ！貨物でも運んでろ、いや、それより他の負け犬どもみたいに酒でも飲んでくたばっちまえ！";
			link.l1 = "...";
			link.l1.go = "mtraxx_46a";
		break;
		
		case "mtraxx_46a":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "First time";
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			sld = characterFromId("Mtr_KittyCap");
			sld.lifeday = 0;
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx = "fail";
			if(CheckAttribute(pchar, "GenQuest.HunterLongPause")) DeleteAttribute(pchar, "GenQuest.HunterLongPause");
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <--- legendary edition
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "おう、来やがったな……待ってたぜ。『キティ』の護衛の礼だ、1万だ。";
			link.l1 = "ありがとう……お前と話したいことがあるんだ、Marcus。";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "そうかよ！？ハハッ！撃てよ…";
			link.l1 = "ジャン・ピカールが奴隷にされたのを覚えてるか？最初はイギリスの私掠船と一緒にオランダの隊商を襲ったが、 今度はスペインの重ガレオンに同じ目に遭わされたんだ。";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "覚えておけ。で？";
			link.l1 = "ブリッジタウンでイグナシオ・マルコに声をかけられた。あのイングランドに仕えるポルトガルの私掠船乗りだ。 キュラソーとトリニダードの間にある無人島の近くで、オランダの隊商を襲わないかと持ちかけてきた。";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "ほう、ほう……承諾したのか？";
			link.l1 = "ああ、やったぜ。まずは、いい取引だったからな。次に、ピカールの話を思い出して調べてみることにしたんだ…";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "どうせやったんだろうな。";
			link.l1 = "ああ。キャラバンがいてな、俺たちはきっちり仕事を片付けたぜ。\nそれから陸で戦利品を分けたが、その前にこっそり見張りを望遠鏡持たせて丘に登らせたんだ。\nそしたら案の定、すぐ後に重ガレオンを旗艦にしたスペインの艦隊が現れやがった。";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "相棒はきっと逃げやがったから、スペイン野郎どもがお前を追いかけたってわけか？";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "その通りだ。奴らはあいつに見向きもしなかった。奴らにとっちゃ運が悪かったな。 俺たちはスペイン野郎どもと死ぬほどやり合って、絶対に忘れられねえ戦いをしてやった。 カスティーリャの連中は腕が立ったが、結局、俺たちはあいつらの艦隊を丸ごとぶっ潰したぜ。";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "その通りだ。奴らはあいつに見向きもしなかった。俺はどうにか逃げ出せたが、それも見張りのおかげだ…";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "へっ！エドゥアルド・デ・ロサドの艦隊をぶっ潰すとはな！お前はまさに海の悪魔だぜ、坊主！ スペイン野郎どもはもうお前のケツを狙って追っ手を差し向けてるに違いねえな。";
			link.l1 = "奴らには運が悪かったな……だがよ、このクズどもは片付けてやるべきだぜ、イグナシオ。言いたいことは分かるだろう。";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "へっ！お前がカスティーリャ野郎どもの手から抜け出したと気づいた時の大騒ぎが目に浮かぶぜ！やるじゃねえか！";
			link.l1 = "奴らの問題だ、俺には関係ねえ。だがな、イグナシオ、このクズどもは片付けておくべきだろう。 言いたいことは分かるだろう？";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "俺が片付けてやる。このイグナシオ・マルコについてもっと調べた方がいいな。誰かの手先かもしれねえ。 俺の部下に興味を持ってるのも怪しいぜ。あいつはどんな船を持ってやがる？";
			link.l1 = "ポラッカ船、『トレロ』か。独特な船だな、きっとオリジナルの設計だぜ。";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "よし、それならあの女の足取りも追いやすいな……わかったぜ。で、お前には仕事があるんだ、プリンス。やる覚悟はできてるか？";
			link.l1 = RandSwear()+"もちろんだぜ、親分！";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "じゃあ、よく聞け。少し前、この辺りに妙な海賊が現れた。名前はウルフリック・イオガンセン、通称レッドウルフ。 なかなか派手な奴だったぜ。北欧から数年前にここへ来たバイキングでな、ルヴァスールに用心棒代も払わねえ、 仲間も作らず、いつも一匹狼だった。とにかく秘密主義でな、奴の船の乗組員で生きて帰った者はいねえ。噂じゃ、 襲撃の話を酒場でベラベラしゃべった奴の舌を、本人が切り取ったって話だ……俺たちの多くと違って、ウルフリックは女や酒に金を使わねえし、戦利品を安売りもしなかった。銀行屋も信用せず、 船も乗り換えなかった。『フレイヤ』っていう上等なコルベットと、よく働きよく黙る忠実な乗組員を揃えていた。 たぶん、できるだけ金を貯め込んでヨーロッパに戻り、王様みてえに暮らすつもりだったんだろう。だが、 スペインの追っ手のおかげで、その目論見は潰えた。あいつはスペインに莫大な損害を与えたから、 討伐隊がイスパニョーラ沖で追い詰めて、『フレイヤ』を沈め、乗組員もろともウルフを殺した。 浅瀬でスペイン船に囲まれて、レッドウルフは死んだってわけだ。だがな、 ラ・ベガの連中はみんなウルフの財宝の噂を知ってて、沈んだ『フレイヤ』も見つけたが、 地元の潜水夫もインディオの潜水夫も宝は見つけられなかった。奴も馬鹿じゃねえ、きっとあの辺りのどこか、 奴と乗組員しか知らねえ場所に莫大な隠し財産を持ってたはずだが……まあ、奴らに聞くことはできねえ理由は分かるよな。だが、ここからが面白え話だ。 俺は奴の無傷の航海日誌を手に入れた。船の金庫に隠されてたやつだ。財宝の手がかりははっきり書かれてねえが、 行間を読めば何か掴めるかもしれねえ。日誌を読んで、 カリブで二年荒稼ぎしたバイキングが財宝をどこに隠したか突き止めて、見つけてこい。もし成功したら、 三分の二はお前のもんだ。やるか？";
			link.l1 = "ふん…真っ暗な部屋で黒猫を探すようなもんだな。航海日誌はどこだ？";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "ほら、持っていけ。幸運を祈るぜ！";
			link.l1 = "助かるぜ、これから必要になりそうだからな……";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "おう、勇敢な船長が来たな。レッドウルフの財宝はどうなった？";
			link.l1 = "今やってるところだ。これにはお前の助けが必要なんだ。";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "聞いてやるぜ。";
			link.l1 = "ウルフリックの航海日誌に「ゴード」という未知の言葉が何度も書かれている。\n調査を進めるためには、その意味を知る必要がある。";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "ふん…ゴードだと…俺も聞いたことねえな。まあいい、一週間後にまた来い。船の会計係をやってる頭の切れる連中に相談してみるぜ。 少なくとも、奴らは数えたり字を読んだりできるからな。何か手がかりが得られるかもしれねえ。";
			link.l1 = "ああ、マーカス。また一週間後に会おうぜ。";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "答えを教えてやるよ。頭の切れる野郎が教えてくれたんだ。ゴルドってのは、自由なヤールの要塞化された集落のことだ。 ";
			link.l1 = "自由なヤールだと？そいつは誰だ？";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "バイキングの海賊提督みたいなもんだ。例えば、俺は自由なヤールで、ラ・ベガは俺のゴルドってわけさ。 レッドウルフはご先祖の歴史がよっぽど好きだったんだろうな、はは！この情報、役に立ったか？";
			link.l1 = "まだ分からねえ。まずはメモを照らし合わせるべきだな。つまりゴルドは集落って意味か……助かったぜ、マーカス！";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "どうだ？その得意げなツラを見ると、うまくやったんだな。";
			link.l1 = "ああ。レッドウルフの財宝は見つけたぜ！だが、簡単じゃなかったな。";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "俺たちのヴァイキングはどれだけ隠したんだ？";
			link.l1 = "７５万ペソと９００ドゥブロンだ。";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "ほうほう！よくやったな、王子。俺の取り分はどうなってるんだ？";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "ほら、これを受け取れ。約束通りだぜ：25万ペソと300ドゥブロンだ。";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "ペソもドゥブロンも全部俺の船室にあるんだ。ちょっと待ってろ、すぐ持ってくるぜ！";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "俺の取り分、持ってきたか？";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "ほら、これを受け取れ。約束通りだぜ：25万ペソと300ドゥブロンだ。";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "ああ、ああ、今行くぜ！";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveDublonsFromPCharTotal(300); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "上出来だ。またやりやがったな。よくやったぜ！";
			link.l1 = "マーカス、イグナシオ・マルコについて何か分かったか？";
			link.l1.go = "mtraxx_70";
			// mitrokosta возможность отстройки исламоны
			pchar.questTemp.IslaMona = "start";
		break;
		
		case "mtraxx_70":
            dialog.text = "ああ、だがまずは確認しねえとな…";
			link.l1 = "何だと？";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "マルコが誰かと繋がっている気がする……それを突き止めてほしいんだ。マルティニークへ向かえ。サン・ピエールに船を置いて、 ジャングルを抜けてル・フランソワまで行け。俺たちの仲間があそこに現れたって話だ。 周りの海賊どもに聞き込みなんてするな、ただ見張って観察しろ。見つけたら、そいつの後をつけて、どこへ行くか、 誰と会うかを見極めろ。絶対にそいつや船を襲うな、今俺が仕込んでる計画が台無しになるからな！警告はしたぞ！ しっかり見張って、十分に分かったら俺のところに戻れ。あのクソ野郎の首を締めたくてたまらねえのは分かるが、 頭は冷静に保て。さあ行け。三週間やる。幸運を祈るぜ。";
			link.l1 = "行くぜ、親分。";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			//SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // опоздал
			{
				dialog.text = "ちくしょう、プリンス！お前がもう少し素早ければ、復讐もできたし、とんでもねえ大金も手に入ったんだぜ！ お前にはこんな失態は期待してなかったが、まあ、お前はいい奴だから許してやる。 俺の目にふさわしい名誉を取り戻すチャンスを一ヶ月後にやる。みんなを集めて襲撃を企んでるんだ！\n一ヶ月後、強力だが一隻だけの船で俺のところに来い。ルーク、カトラス、ジェフリー、それにジャンも参加するぜ。 一日たりとも遅れるんじゃねえぞ！";
				link.l1 = "わかったぜ、Marcus。もう二度とやらねえよ！";
				link.l1.go = "mtraxx_73x";
				break;
			}*/
			dialog.text = "いいタイミングだ！今すぐ俺に報告しろ。";
			link.l1 = "俺の債務者をル・フランソワまで追跡したぜ。奴のポラッカはコルベットとフリゲートで構成された戦隊の一部だった。 マルコ本人はバルバゾンを訪ねて、そいつの屋敷で二時間会談した。他の客は護衛に追い返された。その後、 マルコは陰気な二人組と一緒に屋敷を出た。一人は赤毛で髭面、リターの胸甲を着ていた。 もう一人は口髭で重いトレンチアーマーを身に着けていた。三人とも港へ向かい、 俺がサン・ピエールに着く前に出航しちまった。";
			link.l1.go = "mtraxx_74";
		break;
		
		/*case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
		break;*/
		
		case "mtraxx_74":
            dialog.text = "それでいい。これで全体像が見えたぜ。お前が見たあの二人のクソ野郎どもは、バルバゾンかジャックマンの手下だ。 俺のバルドとカトラスみたいなもんだが、あいつらの方が腕が立つ。赤毛の方はプロウラーって呼ばれてて、『 カトルフィッシュ』ってコルベットの船長だ。口ひげの男はグール、『マーシレス』ってフリゲートを操ってる。で、 俺たちの友人イグナシオだが――あいつはイギリス人やスペインのドン・ロサドだけじゃなく、バルバゾンのためにも動いてやがる。 だからお前とピカールを陥れようとしたのさ。";
			link.l1 = "なぜだ？";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "バルバゾンの命令だ。お前は知らなかっただろうが、ジャックはいつも俺の邪魔をする機会を逃さねえ。 表立って俺に逆らうことは絶対にしねえ、理由は明白だがな。だから陰で俺に楯突くんだ。 ピカールもお前も俺の手下だってことはあいつも知ってた。お前に刺客を差し向けたのも、まさにあいつのやり口だぜ。 しかも、見ての通り、間抜けなんかじゃなくてな。";
			link.l1 = "マルコの始末がついたら、すぐにバルバゾンのところへ行ってやるぜ…";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "そんなくだらねえ考えは捨てろ！バルバゾンと正面からやり合っても勝ち目はねえ。 あいつにゃ簡単にぶっ潰されるだけだ。だが、あいつの手下どもを狙って、奴のやり口で仕返ししてやるぜ。 やる覚悟はあるか？\n汚え仕事だがな。";
			link.l1 = "俺の得意分野じゃねえか！";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "イグナシオ・マルコ、プロウラー、グール、そしてバルバゾンの手下でジョーカー・ジムと呼ばれるもう一人が、 黄金艦隊のスペイン船の一隻を奪う計画を立てている。この作戦全体はバルバゾン自身が考え出したもので、 俺は間者からその詳細を聞き出すことに成功した。黄金艦隊の重ガレオン一隻がハバナの造船所に長居していたが、 他の艦隊はすでにスペインへ向けて出発している。そのガレオンは修理を終え、 まもなく他の二隻と共にヨーロッパへ向かう予定だ。艦隊はキューバから北東へ航行するが、正確な航路は分からねえ。\nスペイン船はサントドミンゴへ向かい、 それからプエルトリコ沿岸を通ってそのまま大洋へ出るつもりだと知らされている。バルバゾンもそれを知っている。 ただし、イスパニョーラ島は南側だけじゃなく北側からも回り込めるから、 航路を変えてサントドミンゴに寄らずタークスやイスラ・テソロ経由で大洋へ抜けることもできる。 だからジャックは用心して、ずる賢い狐イグナシオをキューバに送り込んだってわけだ。\nマルコの任務は、キューバから出港する予定のスペインのガレオンの出航スケジュールを手に入れることだ。 奴はスペイン人の間にコネがあるから、この任務は問題なくこなせるはずだ。 バルバゾンの一味の残りはサン・マルタンでマルコを待っている。そこがこの獲物を狙うには最適な場所だからな。ただ、 マルコとオランダ人は仲が悪いから、サン・マルタンの海域には入れねえ。 だから遠くから仲間に伝令を送るしかねえんだ……";
			link.l1 = "ここで俺が何をすればいいか、だいたい分かってるつもりだぜ…";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "お前はなかなか頭が切れるようだが、まだ話は終わっちゃいねえ。 俺はガブリエラ・チャパーダの協力でこの計画をぶち壊したんだ。あの女のことは知ってるだろう？一緒にスペイン側に、 海賊の待ち伏せがプエルトリコの近くで仕掛けられるって知らせてやったのさ。 だからガレオン船はその海域を通らねえが、代わりにこっそりと海賊狩りの艦隊をそこに送り込んでやがる。 お前にはいくつか仕事がある。まず最初は『トレロ』を見つけて拿捕することだ。その船長にどうするかは、 わかってるだろうな。";
			link.l1 = "当然だぜ…";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "次に、スペインの黄金ガレオンの本当の航路を突き止める必要がある。マルコがその航路表を持っているはずだ。 それを手に入れて、俺のところに送れ。";
			link.l1 = "どうやって？";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "空からだ。カゴを持っていけ……こいつはスパイク、ここラ・ベガで生まれ育った伝書鳩だ。トリニダードからでも必ずここに戻ってくる。 予定表を手に入れたら、メモを書いてスパイクの足にくくりつけて放て。数時間以内にスパイクが俺のもとへ飛んでくる。 大事に扱えよ、坊ちゃん！";
			link.l1 = "「もちろんだぜ、親分！」";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "三つ目だが、「トレロ号」でサン・マルタンへ向かえ。必ずその船だけで行くんだ！そうじゃなきゃ、 すぐに怪しまれるぜ。やつらにはプエルトリコへ向かうよう合図を送れ。スペイン人どもが待ち構えてるからな。 合図の暗号はマルコの書類にあるはずだ。もしくは本人から直接聞き出してもいいぞ。";
			link.l1 = "なるほどな。バルバゾンの手下どもをスペイン人に送り込むとは、なかなか頭が回るじゃねえか、ハハ！";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "その通りだ！俺は奴を影から仕留めるぜ。あいつがやったようにな。\nそれからもう一つ、合図を送ったらすぐに出航してスペインのガレオン船とその護衛を迎え撃て。\nぐずぐずしてる暇はねえぞ。";
			link.l1 = "ポラッカ船でだと？重ガレオンと他に二隻、しかもスクーナーなんかじゃねえんだろ？奴らにバラバラにされちまうぜ！";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "女の子みたいに泣くんじゃねえ！なんで俺にスパイクをよこすと思ってるんだ？増援なしで放り出したりしねえよ。ただ、 キャラバンを逃がすな、海にたどり着かせるな。わかったか？";
			link.l1 = "「ああ、親分。」";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "報酬はたんまりの金貨とマルコのポラッカ船だ。あれは評判のいい船らしいぜ。質問はあるか？任務は理解してるな？";
			link.l1 = "俺はカトラスじゃねえ、やるべきことは分かってる。「トレロ」をどこで待ち伏せすりゃいいんだ？";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "俺たちがこうして話してる間にも、船はキューバからフィリップスバーグへ一直線に進んでるはずだ。 今ごろトルトゥーガの近くか、もう少し東かもしれねえ。だから錨を上げてサン・マルタンへ向かえ、島の近くで『 トレロ』を捕まえるんだ。ただしバルバゾンの手下どもに戦いを見られるなよ、 そうじゃねえと俺の計画が台無しになるからな。";
			link.l1 = "すぐに行くぜ！";
			// belamour legendary edition испанский флаг к выдаче -->
			if(IsCharacterPerkOn(pchar,"FlagSpa")) link.l1.go = "mtraxx_86";
			else link.l1.go = "mtraxx_85f";
		break;
		
		case "mtraxx_85f":
			STH_SetJokerFlag(SPAIN, true);
			log_info("You have received a spanish flag");
			pchar.questTemp.GiveMeSpaFlag = true;
            dialog.text = "なんだと？火かき棒でぶん殴ってやろうか、プリンス。 こんな基本的なことまで説明しなきゃならねえとは思わなかったぜ。スペインの旗をしっかり持っとけ、 じゃねえと全部台無しになる前に終わっちまうぞ。旗を返せ。さっさと失せろ！";
			link.l1 = "もう海に出てるぜ、親分";
			link.l1.go = "mtraxx_86";
		break;
		// <-- legendary edition
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			/*pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";*/
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // время на перехват Тореро, снимать при потоплении или захвате
		break;
		
		case "mtraxx_87":
            dialog.text = "「で、王子よ、お前は何もかもぶち壊しにしやがるんだな？」";
			link.l1 = "やったぜ。今回の任務は思ってたよりずっと手強かったんだ。怒鳴りつけて追い出してくれても構わねえよ。";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88": // belamour legendary edition увеличиваем срок
            dialog.text = "まあまあ、やめとけよ。そんなこともあるさ。お前は腕のいいコルセアだし、誰だってたまには失敗するもんだ。 あの金を手に入れられなかったのは残念だが……一つの場所でダメでも、他で手に入れりゃいいんだ、はは！名誉を取り戻すチャンスはあるぜ。 三週間後に俺のところへ来い、できればもっと強い船でな。ただし一隻だけだ――俺たち全員で艦隊を組むからな。みんなで襲撃に行くぞ！\n三週間後、強力な船一隻で俺のところへ来い。ルーク、カトラス、ジェフリー、それにジャンも参加する。 遅れるんじゃねえぞ！";
			link.l1 = "やらねえよ、親分！";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given a spanish flag");
			}
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			//SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "ホッホー、よう、坊主！ここで俺に会うとは思ってなかっただろ？ハハハ！結局スペインの隊商を見つけたぜ……";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // был абордаж
			{
				link.l1 = "ああ、親分、やったぜ。だけど楽じゃなかった。";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "ああ、だがゴールデン・ガレオンは金ごと沈められちまったんだ。";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "「いくら金貨を手に入れたんだ、旦那？」";
			if (iTotalTemp < 1) link.l1 = "えぇ…何でもねえ。";
			else link.l1 = "へっ…… "+iTotalTemp+" 全部で！";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "ちくしょう！スペイン野郎どもが俺たちに渡さねえために海に投げ捨てやがったんだろう。まあ、 やつらにはそれなりの代償を払わせたけどな。バルバゾンの手下どもも同じ目に遭わせてやったし、 これも勝利ってもんだな…";
				link.l1 = "金のことは悪かったな……で、どうするんだ、マーカス？これからラ・ベガに行くのか？";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "情けねえな。こんなんじゃ、ここまで来た旅費にもならねえ。スペイン野郎どもが、 俺たちに渡らねえように海に投げ捨てやがったんだろうよ。まあ、やつらもちゃんと代価は払ったぜ。 バルバゾンの手下どもも同じく、これもまた勝利ってわけだな…";
				link.l1 = "金のことは悪かったな……だが、とにかく分けようぜ。";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "これはしけた獲物だな。経費をまかなうのがやっとだぜ。スペイン野郎どもが、 俺たちに渡らねえように一部を海に投げ捨てやがったんだろう。まあ、奴らも代償は払った。 バルバゾンの手下どもも同じく、これも勝利ってわけだな…";
				link.l1 = "金のことは悪かったな…まあ、とにかく山分けしようぜ。";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "悪くねえが、もっといいもんを期待してたぜ。スペイン野郎どもが、 俺たちに渡らねえように一部を海に投げ込んだんだろうな。まあ、やつらも代償は払った。 バルバゾンの手下どもも同じく、これも勝利ってわけだな……";
				link.l1 = "戦利品を分けようぜ！";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "素晴らしいぜ！いい獲物を手に入れたな、相棒！それにバルバゾンの手下どもも報いを受けたってわけだ、ハハッ！";
			link.l1 = "へっ、ずいぶんと金貨があるじゃねえか！分けようぜ！";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "…いつものようにバッカニア同盟でやる通りだ――全員に公平な分け前をやるぜ。『トレロ』はお前の獲物だ、好きにしな。";
			link.l1 = "次はどうするんだ、Marcus？ラ・ベガに行くのか？";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4": // belamour legendary edition увеличиваем срок до 3х месяцев
            dialog.text = "俺は必ずラ・ベガにいるぜ、そこで三週間待っててやる。準備ができたら来い。できればもっと強い船で来いよ、 ただし一隻だけだ――俺たちは艦隊を組むんだからな。全員に出発の準備をさせてる。お前は俺の指揮下に入る、ジャン・ハンサム、 ハゲのジェフリー、クリーバー・ペリー、それにルーク・レプラコーンも一緒だ。覚悟しとけ。今回は本格的な遠征で、 かなりの戦利品が期待できる。詳しいことは後で教えてやる。";
			link.l1 = "わかったぜ、親分！三週間後にラ・ベガで会おう。";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "じゃあな、殺し屋野郎！ハハッ！";
			link.l1 = "...";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given spanish flag");
			}
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "他に何かあるか？";
			link.l1 = "いや、そうは思わねえ。もう自分の船に向かってるんだ。";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "へっ！それは誰のせいだ、王子？お前のせいか？";
			link.l1 = "悪いな、親分。でも俺たち二人とも十分やれたぜ……あんたも撃つの上手かったな。ついでに言うと、狙いもなかなかだったぜ……";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "どうでもいいさ。俺たち二人とも悪いんだ。だが手ぶらじゃねえ――バルバゾンの手下どもには渡すもんをちゃんとくれてやった、それだけでも勝利ってもんだろう…";
			link.l1 = "金のことは悪かったな……で、次はどうする、Marcus？ラ・ベガに行くのか？";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "旦那、頭でもおかしくなったのか？一隻だけ連れて来いって言っただろうが！余計な船はさっさと処分して、 すぐ戻って来い！今すぐだ！";
				link.l1 = "「わかった、わかった！」";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // торговые
			{
				dialog.text = "旦那、俺の二番手のカトラスになるつもりか？なぜ交易船なんか持ってきやがった？俺はお前に期待してたんだぜ！ さっさと本物の軍艦を持ってこい！今すぐだ！";
				link.l1 = "「わかった、わかった！」";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "旦那、驚いたぜ。俺はお前に軍艦を持って来いと言ったはずだ！こんなボロ船でどうやって俺を助けるつもりだ？ 最低でも三等艦か二等艦で戻って来い、それ以上でもそれ以下でも駄目だ！今すぐだ！俺は誰も待つ気はねえぞ。";
				link.l1 = "「わかった、わかった！」";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "「旦那、なんでソブリン・オブ・ザ・シーズなんか持ってきやがったんだ？俺が戦列艦を持ってこいって言った時、 まさかあんな化け物級の一等戦列艦を連れて来いとは言ってねえぞ！三等か二等艦で出直して来い！今すぐだ！ 俺は誰も待たねえからな。」";
				link.l1 = "「わかった、わかった！」";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "いいタイミングだな、コルセア！無事で何よりだぜ！航海の準備はできてるか？";
			link.l1 = "ああ、親分。いつでも準備万端だぜ。";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "ところで、お前がプエルトリコに送ったバルバゾンの艦隊について知りたいか？";
			link.l1 = "すっかり忘れてたぜ。もちろん知りたいさ。奴らは死んじまったのか？";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "ああ、まさにその通りだぜ！旗艦――ジョーカー・ジムのフリゲート艦『オウル』は水面まで燃えちまった。ジョーカー・ジム本人は跡形もなく消えた。 トランプとグールはひどくやられたが、なんとか逃げ延びた。トランプはトルトゥーガ、ラ・ロチャの大砲の守りの下に、 グールはイスラ・テソロへ。パスクァーレの話じゃ、グールはシャープタウン近くのリーフに座礁して、 どうにか船を引き上げたらしい。アレクサス親方もこれから大変だろうな、へへ。全体的に、 スペイン野郎どもにはちょっとがっかりしたぜ。全員ぶっ殺すかと思ってたのによ。";
			link.l1 = "へっ。どうでもいいが、バルバゾンの野郎のブーツにしっかり小便ひっかけてやったぜ。 あいつにメッセージを送ったってわけだ。";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "そうだな。さて、本題に入ろうぜ。";
			link.l1 = "聞いてやるぜ。";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "俺の諜報網――つまり俺の親友ベルナール・ヴァンサンからの報告だが、 スペイン野郎どもがカルタヘナに大量の金塊を隠してやがるらしい。しかも要塞の下だ、間違いねえ。 普通ならスペインの黄金艦隊のものってことになるが、今回は俺たちの獲物だぜ。スペイン領本土へ向かい、 カルタヘナを襲撃するぞ。\n";
			link.l1 = "うおっ！今の聞き間違いじゃねえよな？まさか砦まである植民地まるごと襲うってのかよ？";
			link.l1.go = "mtraxx_95";
			// belamour legendary edition отказ от великого похода
			link.l2 = "俺はお前と一緒にカルタヘナには行かねえぞ、マーカス。街ごと焼き払うなんて、俺のやり方じゃねえ。";
			link.l2.go = "mtraxx_94a";
		break;
		
		case "mtraxx_95":
            dialog.text = "聞いた通りだ。それがまさに俺たちのやることだぜ。俺の軍艦が砦を叩く、もちろんお前の協力付きでな。 ジェフリーの野郎は新しく手に入れたイースト・インディアマンで陸兵を運ぶ――オランダから盗んだやつだ。ペリーもようやくボロボロのブリガンティンを手放して、まともなコルベットを手に入れた。 もちろん俺の金も使わせてやったがな。ポール・チャントとお前は哨戒艦隊の始末を任されてる。 お前らの部下も強襲に加わるし、チャールズ、お前は腕利きの戦士で船長だ、俺と一緒に砦をぶっ壊してもらうぜ。 ジャン・ピカールは現れなかった。変な話だ、あいつのコルベットはポート・ロイヤルで見かけられてるのによ。まあ、 スペインの金塊に興味がねえなら知ったこっちゃねえ。くたばれってこった。 その代わりに俺の友人ベルナール・ヴァンサンが襲撃に加わる。 さらにレプラコーンとそのバッカニアどもも俺たちの部隊を手伝ってくれる。砦から金を奪い、街から身代金も取る。 奴らは一生忘れられねえだろうな、ははは！\nさあ、今は休んでおけ。そして今夜は俺や他の船長たちと一緒に酒場に来い！俺たちの大義に乾杯しようぜ！ バーテンには地元の酔っぱらいどもを全部追い出させておく。だから酒場には俺たち六人と、 ちょっとした可愛い娘たちだけだ。今夜は仲間と飲むんだ、明日の朝にはお前が艦隊を率いて進路を決める。 できるだけ早くカルタヘナに着けてくれ。分かったか？";
			link.l1 = "あいよ、親分！";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // уберем враждебные энкаунтеры
		break;
		// belamour legendary edition -->
		case "mtraxx_94a":
            dialog.text = "てめえ…てめえ…狂った王子め！俺をハメる気か！？いいか、くたばれ！お前には兄弟団に加わるチャンスがあった、 くだらねえクズどもから抜け出すチャンスもな。だが、お前は臆病にもその機会を逃したんだ。 泣き言言いながらとっとと失せろ！腰抜けが！もう一度でも会ったら、犬どもをけしかけてやるからな！";
			link.l1 = "...";
			link.l1.go = "mtraxx_95a";
		break;
		
		case "mtraxx_95a":
            DialogExit();
			QuestSetCurrentNode("Terrax", "First time");
			CloseQuestHeader("Roger_8");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida");
			DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
			LocatorReloadEnterDisable("LaVega_town", "reload6", true); // закрыть на месяц
			SetFunctionTimerCondition("Mtraxx_CartahenaLateOpen", 0, 0, 30, false);
			Mtraxx_TerraxReset(8);
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <-- legendary edition
		case "mtraxx_97":
            dialog.text = "やっと来たな、旦那！見ろよ、野郎ども――せっかく旦那のために贈り物を用意したってのに、どこほっつき歩いてやがるんだ！さあ座れ、始めるぞ！\nさて、勇敢なコルセアどもよ！カルタヘナの黄金が俺たちを待ってるぜ、ハハ！そして俺は雷に誓ってそれを手に入れる！ だがな、働く者にはしっかり休みも必要だ！だから今夜はこの上等な店で思いっきり楽しもうぜ。ラムを注げ、 たっぷりとな！ジョッキをなみなみと満たせ！財宝の風に、幸運の風に乾杯だ！最後の一滴まで飲み干せ！\n旦那には、うちの酒蔵から一番の酒と、この島で一番の美女たちを用意してやったぜ、ハハハ！\nそれからチャールズ、お前には俺たちから――立派な帽子だ。さあ被れ、文句言うな！\nコルセアども、歌え！俺たちのお気に入りの歌をな！..";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			GiveItem2Character(PChar, "hat8");
			EquipCharacterByItem(PChar, "hat8");
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "俺たちが何者か見せてやる時だ、コルセアども。\nレプラコーン！お前は部下を連れて城門を制圧しろ。\nやつらが要塞に援軍を送れないようにするんだ！俺たちが要塞の兵を突破したら、後ろから思いっきり叩け！";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = "プリンスとポール！三隻の軍艦の艦隊を見ただろ、あいつらを片付けろ。砦には近づくな、やつらの船にも乗り込むな。 戦利品をどうこうしてる暇も余裕もねえんだ。わかったか！？プリンス、特にお前に言ってるんだぞ。 お前の英雄気取りは知ってるが、それは後で好きなだけやらせてやる！\n砦には近づきすぎるな、この船どもを沈めて戻ってこい！ここで待っててやるぜ。わかったな？よし、ハハハハ！突撃だ！ ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "そうか、スペイン艦隊は完全に消えたな。今こそ「レッドドラゴン」の出番だぜ。カタルヘナの砦を瓦礫の山にしてやる。 \n俺と一緒に来るか？";
			link.l1 = "ああ、いいぜ！";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "「レッドドラゴン」はとても頑丈な船で、強力な大砲を備えている。お前の船じゃ到底敵わねえぜ。だから気をつけろ、 英雄気取りはやめて、俺の砲の射程には近づくんじゃねえぞ！";
			link.l1 = "...";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
	
			Weather.Wind.Angle = 0.0;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
			SetFunctionExitFromLocationCondition("Mtrxtofort", pchar.location, false);
		break;
		
		case "mtraxx_104":
            dialog.text = RandSwear()+"すげえ戦いだったな！これで終わりだ、俺の勇敢なコルセアども！カルタヘナは俺たちのものだ！抵抗は潰した！ よくやったな、レプラコーン！俺と一緒に砦へ来い――バーニーはもう金を見つけてるはずだ。プリンス、カトラスを連れて総督のところへ行き、身代金25万ペソを払わせろ！あいつら金は持ってる、だからしつこくいけ。お前ならできるってわかってるぜ。";
			link.l1 = "へっ！喜んでだぜ、親分！";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// запрещаем драки в городе, резиденции, форте
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "調子はどうだ、プリンス？";
			link.l1 = "全て順調だぜ。カルタヘナの一番の金持ちどもから35万ペソを無理やり巻き上げてやった。";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "ホッホー、さすが俺の息子だぜ！だが、金はどこだ？";
				link.l1 = RandSwear()+"すぐに持ってくるぜ！";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "ほうほう、さすが俺の息子だ！お前とカトラス号には、素早さと機転へのボーナスとしてそれぞれ五万ずつやる。 残りは後で全員で分けるぜ。";
				link.l1 = "「ほらよ！」";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "どうした？ぐずぐずしてねえで、さっさと金貨を持ってこい！";
				link.l1 = "今行くぜ！";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "よし！お前とカトラス号には、素早さと機転を評価してそれぞれ五万をボーナスとしてやるぜ。 残りは後で全員で分けるからな。";
				link.l1 = "ほらよ！";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -300000);
            dialog.text = "俺たちの金のことが気になるんだろう？見つかったぜ――5,000ユニットだ。すでに俺たちの船に運ばれてる。分け前ももう決まってて、連中も納得してる。 カトラスもお前も文句はねえよな？";
			link.l1 = "俺の取り分はどうなってるんだ？";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "この作戦は全部俺が計画したし、「レッドドラゴン」が砦攻略という一番厄介な役目を引き受けたからな、 俺と俺の手下どもが戦利品の半分をもらうぜ。残りの半分は、他の四隻の船の船長たちに、 それぞれの乗組員の数に応じて分けてやる。お前には\n "+GetCrewQuantity(pchar)+" お前の手下、取り分は "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" 金貨と "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+" ペソ。";
			link.l1 = "「まあ、みんながこれでいいなら、俺も構わねえぜ！」";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "素晴らしい。今回の航海の成功、おめでとう、コルセアども！ここにもう用はねえ、帰るぞ。全員、俺も含めて、 一ヶ月の休暇だ。ただし、お前は違うぞ、プリンス。お前には別の任務がある。いいか、 トルトゥーガの娼館の女主人ジャネットが、お前について文句を言ってきたんだ。 チャーリー・プリンスはあの店に全然興味も愛情も示さねえってよ。だから命令だ、トルトゥーガに行って、 ジャネットの店に顔を出して、そこでボーナスを使え。お前はその権利がある。女主人と女たちを喜ばせてこい。 トルトゥーガでしっかり休むまで、俺の前に現れるんじゃねえぞ、ハハハ！";
			link.l1 = "了解だ、親分。こんなに嬉しい任務は初めてだぜ。必ずやってやる！";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "さらばだ、野郎ども！船に戻って出航しろ！ラ・ベガでまた会おうぜ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "mtraxx_113":
            dialog.text = "「なんだと！？ジャンは今やイギリス野郎の犬かよ、ボールドとカトラスは消えちまったし、 レプラコーンとその手下どももどこにもいねえ！で、今度はお前かよ！？」";
			link.l1 = "マーカス、俺は決めたぜ。俺は十分稼いだし、お前も俺でかなり儲けただろう。だが、もう終わりだ。俺は出ていく。";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "お前もピカードと同じで、自分一人で稼げると思ってるのか？ああ？俺がいなくてもやっていけるつもりか？ハハハ！ さっさと失せろ、プリンス。俺はお前なんか引き止めねえ。すぐに、いや本当にすぐに、 自分がどれだけ間違ってたか思い知るだろうよ。それで泣きついて戻ってくるんだろうが――どうなると思う？俺は絶対に許さねえ！ハハ！さっさと俺の前から消えろ！";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "ほうほう！ここに来て正解だぜ！さっさと言えよ！";
			link.l1 = "海賊を恐れねえ奴がいるんだ。俺たちを舐めてやがる。礼儀ってもんを叩き込んでやる必要があるな。\nただし、殺すんじゃねえぞ。";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "ふん！こりゃあ、他でもないあの爺さんチャールズじゃねえか！どうせまた何かに首突っ込んでるんだろう？\nさあ、詳しく聞かせてもらおうか。今度の標的は誰で、そいつに何を教えてやりゃいいんだ？";
			link.l1 = "ヨーロッパからの客人、フランス財務省の監察官――ノエル・フォルジェ男爵だ。あいつはここにフランス東インド会社を設立したがっているが、 俺と親しい仲間は反対している。オランダ人やイギリス人、 そして何よりルヴァスールが倒れてから増えた海賊どものせいで、 ここでの交易は非常に危険だと男爵を説得しようとしたが、耳を貸さなかった。やつに恐怖を味あわせてやる必要がある、 身をもって思い知らせてやるんだ。";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "ほうほう！ここに来て正解だぜ！さっさと言えよ！";
			link.l1 = "海賊を恐れない奴がいるんだ。俺たちをなめてやがる。礼儀ってもんを叩き込んでやる必要があるな。いいか、 殺すんじゃねえぞ。";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "ふん！なんで急に海賊なんか雇う気になったんだ？まあ、金さえ払ってくれりゃ俺はどうでもいいぜ。\nで、詳しい話をしようか。今回は誰が標的で、そいつに何を思い知らせてやるんだ？";
			link.l1 = "ヨーロッパからの客人、フランス財務省の監察官――ノエル・フォルジェ男爵だ。こいつはここにフランス東インド会社を設立したがっているが、 俺の親しい仲間と俺は反対している。男爵には、ここでの交易はオランダ人やイギリス人、 そして何よりルヴァスールが倒れた後の海賊どものせいで非常に危険だと説得しようとしたが、全く耳を貸さなかった。 やつに恐怖を味わわせてやる必要がある、自分の身で思い知るようにな。";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "ああ、ああ……本物の男爵だぜ！奴の船を襲うか？";
			link.l1 = "計画はこうだ。あいつの船はもうすぐポルトープランスからキャップスターヴィルへ出航する。 お前はセントキッツ付近でバロンを捕まえて人質にしろ。船を沈めたり乗組員を殺したりしない方がいい。 フランス人は俺たちの味方だからな。できるか？";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "まあ、何も約束はできねえが、やってみるさ。どの船だ？";
			link.l1 = "「ファヴォリー」という名のブリッグだ。";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "ブリッグなんざ俺の『レッドドラゴン』の敵じゃねえ。楽勝だぜ。降伏すりゃ、全員生かしてやるさ。";
			link.l1 = "完璧だ。奴らに恐怖を与えつつ、降伏の機会も与えろ。その後、バロンをネズミだらけの船倉にぶち込め。 できるだけ汚い場所を探せ、だが一日以上は置くな、病気になって死なれたら困るからな。次に船室に移して、 誰にも見つからない場所に閉じ込めろ。部下の何人かに捕まったフランス商人のふりをさせて、しっかり演技させろ。 三日間ぶっ通しで、海賊にどれだけ無慈悲に追われ、奪われ、身代金を要求され、拷問されたか……必要な細部まで全部語らせろ。";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "ハハハ！こんなに笑える仕事は久しぶりだぜ！よし、坊主、最高の役者どもを見つけてやるよ。心配すんな、 あいつらの話を聞いたらお前のバロンもチビるぜ！剣や焼けた銃杖でできた傷跡まで見せてやるからな…";
			link.l1 = "完璧だ！それなら、あいつにデ・ポアンシー宛ての身代金要求の手紙を書かせろ。 大物のくせに三百五十万なんて大した額じゃねえだろ。";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "いいだろう。次はどうする？";
			link.l1 = "それからお前はバロンをタークスへ連れて行くんだ。そこで身代金を受け取って、バロンを俺に渡せ。さらに、 フランス野郎どもはトルトゥーガとルヴァスールの件で必ず報いを受けるって、 しかも一度きりじゃ済まねえと伝えておけ。";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "ハハハ！そいつぁとんでもねえ芸当だな！俺たちがレヴァスールに何をしたかはお前も知ってるだろうが、今度は……ハハハ！\nよし、坊主。やってやるぜ！で、船はもうすぐ到着するってわけか？";
			link.l1 = "すぐだ。警戒しておけ。";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "ハハハ！とんでもねえ芸当だな！この茶番の代金はいくら取ればいいんだ？まあいい、十万で手を打ってやる。 金をよこせ。";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "受け取れ。";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "よし、持ってきてやる。";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "完璧だ！船がもうすぐ到着するって言ったか？";
			link.l1 = "すぐだ。警戒しておけ。";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "気にするな、俺はお前を失望させねえ。これは俺が直々に片付ける。\nバロンが捕まったって噂を聞いたら、俺のところに来い。";
			link.l1 = "いいだろう。感謝するぜ、Marcus。";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "もちろんだ、坊主。約束通りだぜ。容赦ねえ海賊どもの恐ろしい話、無垢なフランス商人を皆殺しにし、鞭の音、 うめき声と悲鳴。炭火の入った火鉢と焼け焦げた手錠。まさにこれでいいんだよ。";
			link.l1 = "おいおい！落ち着け！そいつは生かしておく必要があるんだ";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "心配すんな、あいつは生きてるぜ。手が震えながらこの手紙を書いたんだ。ほらよ。";
			link.l1 = "そこには何て書いてある？あいつ、ポワンシーに助けを求めてやがるのか？";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "そうだぜ、坊主！あいつは泣きついてやがる、ははっ！";
			link.l1 = "この手紙は捨てろ、いや、いっそ燃やせ。1週間後にタークスで会うぞ。身代金を集める時間が必要に見せかけるんだ。";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "了解だ。一週間後、タークスの北湾だぜ。金を持ってくるのを忘れるなよ、見栄えが大事だからな。\n全部終わったら俺のところに来い、話をつけようじゃねえか。";
			link.l1 = "もちろんだ、またな、Marcus！";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "おい、カエル食い！止まりやがれ！";
			link.l1 = "俺は動かねえ。";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "ほらよ、バロンを連れてきたぜ。ちょっとくたびれてるが、まあ一応無事だ。まだ見分けつくか？ハハハ！";
			link.l1 = "ああ…まあな。";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "完璧だ。さあ、金を渡せ、さもねえとあいつは終わりだぜ！ごまかそうなんて思うなよ、 こっちはお前を狙ってるんだからな！";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "ほら、持っていけ。";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "くそっ！船に置いてきちまった……";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "ハハハ！お前、なかなか頭が回るじゃねえか、フランス野郎。ほらよ、“閣下”を持っていけ。それとポワンシーに伝えとけ、金を用意しとけってな。 ルヴァスールとトルトゥーガにやったことのツケは払わせてもらうぜ。お前らの商人どもも、 商品と船で俺たちに払うことになるんだ。ハハハ！それから、もっとバロンどもをこの諸島に連れてこいよ、 あいつらはたっぷり儲けを運んでくるからな！ハハハ！";
			link.l1 = "頼む、俺の船に行け、バロン。";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "追ってくるなんて考えるんじゃねえぞ、船長。俺が誰だか分かってるだろう。カエル食いどもをもっと捕まえてるんだ。 もし俺が時間通りに帰らなきゃ、全員処刑されるぜ。分かったか？";
			link.l1 = "時が来れば、俺たちがお前ら呪われた冒涜者どもを始末してやるぜ！";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "ハハハハ！もちろんやるだろう！";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "ふざけてんのか！？これが何かの罠かよ！？";
			link.l1 = "ちょっと待て、今持ってくる…";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "うおお、Marcus、てめえの間抜けが何しやがったんだ！";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "チャールズ、何してやがったんだ？金はどこだ？俺の手下どもにはこれが偽物だなんて言ってねえ……だからこのバカが、お前が俺たちを騙そうとしたと思い込みやがったんだ……";
			link.l1 = "大変だ！バロンが死んじまった……これからド・ポワンシーはどうするつもりだ？";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "チャールズ、何してやがったんだ？金はどこだ？俺の手下どもにはこれが偽物だなんて言ってねえ……そしたらこのバカが、お前が騙そうとしてると思い込みやがったんだよ……";
			link.l1 = "大変だ！バロンが死んじまった……これからド・ポアンシーはどうするつもりだ？";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "まあ坊主、それはお前のせいだぜ、わかってるだろうな。\nまあ、死んじまった奴はもう何も悪さできねえから、それでいいのかもな。";
			link.l1 = "なんて俺はバカなんだ！全部台無しにしちまった。まあいい、ポワンシーのところへ行くぜ…こんなバカで悪かったな、マーカス、またな。";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "まあ坊主、お前のせいだぜ、わかってるだろうな。\nたぶんその方がいいのかもしれねえ。";
			link.l1 = "なんて間抜けなんだ、俺は！全部台無しにしちまった。まあいい、ポワンシーのところへ行くぜ…こんな馬鹿で悪かったな、マーカス、またな。";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "休めよ、お前、腕が鈍ってきてるぜ。たまには俺のところに来い、ラム酒といい女を用意してやるからな。";
			link.l1 = "ありがとう、都合がついたらお前のところに顔を出すぜ。";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "どういたしまして、坊主。今年一番楽しかったぜ！俺と手下どもで大笑いしたからな！だから礼を言わせてもらうぜ。 ほら、金だ。";
			link.l1 = "お前の働きに見合う分は取っておけ。";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "金を持っていけよ、「策士」さんよ。ハハッ！面白かったぜ。";
			link.l1 = "助けてくれてありがとう、Marcus。幸運を祈るぜ！";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "気にするな。これは俺たちの友情のためにやったんだ。コースト同盟はお前にもっと大きな借りがあるってのに、 お前はドゥブロン金貨一枚も要求しなかったじゃねえか。";
			link.l1 = "それでも、お前の働きと償いとして少なくとも五万は受け取れ。ありがとう、マーカス！";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "どういたしまして。チャールズ、時間がある時はいつでも俺のところに来いよ！";
			link.l1 = "喜んでだぜ！";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "一週間も遅れてきやがったな！俺の連中にはこれが偽物だなんて言ってねえ……もう待ちきれねえってよ、お前のバロンを片付けることにしたぜ！";
			link.l1 = "なんて間抜けなんだ、俺は！全部台無しにしちまった！ポワンシーに何て言えばいいんだ！？";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "一週間も遅れて来やがって！俺の手下どもにはこれが嘘だなんて言ってねえ…もう待ちきれねえってよ、お前のバロンをぶっ殺すって決めやがったんだ！";
			link.l1 = "なんて間抜けなんだ、俺は！全部台無しにしちまった！ポアンシーに何て言えばいいんだ！？";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "さて、坊主、これはお前のせいだぜ、わかってるだろうな。\nもしかしたら、その方がお前にとって良いかもしれねえな。";
			link.l1 = "わかった、ポワンシーに行くよ……馬鹿だった俺を許してくれ、マーカス、またな……";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "自業自得だぜ、この騒ぎはお前自身のせいだ。";
			link.l1 = "じゃあな、たぶんまた会うだろう…";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "休めよ、お前、腕が鈍ってきてるぜ。たまには俺のところに来い、ラム酒といい女を用意してやるからな。";
			link.l1 = "ありがとう、時間ができたら訪ねるぜ。";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			DelLandQuestMark(npchar);
			
			if (pchar.questTemp.Mtraxx == "full_complete")
			{
				dialog.text = "久しぶりだな、プリンス。";
				link.l1 = "この名前が俺にもたらしたのは不運だけだと思うぜ、Marcus。";
				link.l1.go = "PZ_Prince1";
			}
			else
			{
				dialog.text = "ド・モール！何の用だ？";
				link.l1 = "ああ、Marcus。ちょっと聞きたいことがあるんだ。";
				link.l1.go = "PZ_DeMaure1";
			}
		break;
		
		case "PZ_Prince1":
			dialog.text = "どうやら全く逆のようだな。何の用でここに来たんだ？";
			link.l1 = "「トルトゥーガに新しい売春宿ができたって聞いたか？」";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_DeMaure1":
			dialog.text = "それなら遠慮なく聞けよ。俺は形式ばったのが嫌いなんだ、さっさと本題に入れ。";
			link.l1 = "「トルトゥーガに新しい売春宿ができたって聞いたか？」";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "酔ってるのか？なんだその質問は？本当にそれが話したいことなら、俺の時間を無駄にするな。";
			link.l1 = "知らねえのか？最近、あそこに新しい売春宿ができたんだぜ――すげえ高級で、最高に美人で健康的で着飾った女しか働いてねえんだ。";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "「ああ、それか！もちろん聞いたことがあるぜ――知らねえ奴なんていねえだろ？」";
			link.l1 = "まあ、俺がそれを知ったのはついこの前だぜ。";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "ハハハハ、てめえ、この野郎、驚いたぜ！だがよ、なんで俺に相談するんだ？ まずはホークスに当たってみりゃいいじゃねえか？へっへっ。もっとも……もうあそこでひと暴れしてきたのか？";
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				link.l1 = "あるぜ。ところで、あいつらはドゥブロン金貨しか受け取らねえんだ。";
				link.l1.go = "PZ_Fucked1";
			}
			else
			{
				link.l1 = "俺はその場所に行ったが、サービスは受けてねえ。だがな……";
				link.l1.go = "PZ_NoFucked1";
			}
		break;
		
		case "PZ_Fucked1":
			dialog.text = "見せびらかしに来やがったか！はは、なんて悪党だ。";
			link.l1 = "実は違うんだ。本当はお前に聞きたいことがあるんだ、マーカス。";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_NoFucked1":
			dialog.text = "やらなかったのか！？お前はバカだな、ド・モール。俺だったら……";
			link.l1 = "お前なら本格的な乱痴気騒ぎを始めてただろうな、知ってるぜ。だが、俺が話したかったのはそれじゃねえんだ。";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "何だ？さっさと言えよ、じらすんじゃねえ。";
			link.l1 = "俺はあそこの店の女主人を探してるんだ。あんたに会って、商売の投資話を持ちかけたいって伝言があったぜ。 間違えようがねえよ――中国人の女だ。";
			link.l1.go = "PZ_6";
		break;
		
		case "PZ_6":
			dialog.text = "ほっほっほ。いや、最近は中国女と会う機会なんざなかったぜ。だが、もし会えるなら、 その女の商売に投資してやってもいいと思ってる。\nなんせ、ルヴァスールの縄張りにのこのこ入っていけるわけじゃねえしな。お前の王の臣下ってことになりゃ、 あいつは俺の“ドラゴン”を見つけた瞬間、沿岸の船で砲撃してくるはずだぜ。";
			link.l1 = "まずはポルトープランスを考えているようだな……";
			link.l1.go = "PZ_7";
		break;
		
		case "PZ_7":
			dialog.text = "そう思うのか？それは間違いだぜ。たとえド・ミュサックが俺より金を持っていたとしても――いや、そんなことはねえと思うが――どれだけ金を稼ごうが、あいつは市の予算を売春宿に回す余裕なんてねえんだよ。";
			link.l1 = "いい指摘だな。あいつは自分の野望について全然考えが足りてねえな。";
			link.l1.go = "PZ_8";
		break;
		
		case "PZ_8":
			dialog.text = "なあ、俺はいつも他の売春宿がどうやってやっていけてるのか不思議だったんだ。女に考える力なんてねえし、 ましてや支配するなんて絶対無理だぜ――よく覚えとけよ。";
			link.l1 = "そいつは違うぜ。時間を取ってくれてありがとな、マーカス！もし先にあの女に会ったら、 お前が会いたがってたって伝えてやるよ。";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "32");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}