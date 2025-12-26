// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("「すべての噂話は」 "+GetCityName(npchar.city)+" お役に立ちますぜ。何を知りたいんだ？","ちょうどその話をしてたんだぜ。お前、忘れちまったのか…","今日はこれで三度目だぜ、お前が俺に聞くのは……","お前、オウムみたいに同じことばっかり繰り返してるじゃねえか…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるか、」 "+NPChar.name+"、また今度だな。","そうだ、なぜか忘れちまってたんだ……","ああ、本当にこれで三度目だな……","ああ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "聞いてくれ、この町に錬金術師が来ていないか？医者だ。イタリア人で三十歳くらい、 名前はジーノ・グヴィネイリっていうんだが？";
				link.l1.go = "guardoftruth";
			}
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l1 = "聞けよ、フェルガス・フーパーって猟師を探してるんだ。ここに住んでるって聞いたぜ。どこにいるか教えてくれねえか？ ";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz"))
			{
				link.l1 = "約一か月半前にジェローム・ソーヴェルニエという男があんたの町にやって来たんだ。覚えてるか？";
				link.l1.go = "WildRose_Tavern_1";
			}
			//<-- Дикая Роза
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("いや、知らねえな。薬草師や医者はいるが、その名前のやつはいねえ。","こんな奇妙な名前は初めて聞いたぜ。いや、あんたの言うその男が来たことは一度もねえな。","錬金術師なんて一人もいねえよ。医者ならいるが、そんな名前のやつはいねえな。");
			link.l1 = "なるほど。残念だな。まだ探してみるぜ！";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
		
		// Калеуче
		case "caleuche":
			dialog.text = "ファーガスか？あいつはよく俺の店に来るぜ。だが、昨日からずっとセルバにいるんだ。心配すんな、1週間もすりゃ戻ってくるさ。ラムを飲みながら海の冒険を自慢するだろうよ。もっとも、 あいつは本当に腕のいい猟師だぜ。蛇をあいつほど捕まえられる奴は他に知らねえな。";
			link.l1 = "蛇か？ふむ。そいつに会うには、いつここへ戻ればいいんだ？";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "少なくとも三日はかかるぜ。あいつはいつもここに来るのは午後六時以降で、十時より遅くには絶対にいなくなるからな。 ";
			link.l1 = "どんな顔してるんだ？見たことねえな。";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "髭を生やした中年男で、茶色のコートと帽子、長靴を身につけている。";
			link.l1 = "ありがとう！お前さんには本当に助けられたぜ、相棒。また会おうな！";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "8");
			int iTerms = sti(pchar.questTemp.Caleuche.Belizterms);
			SetFunctionTimerCondition("Caleuche_FergusCome", 0, 0, iTerms, false);
			npchar.quest.Caleuche = "true";
		break;
		
		//--> Дикая Роза
		case "WildRose_Tavern_1":
			dialog.text = "うーん…そうだな。ああ、あの旦那のことは覚えてるぜ。洒落こんじゃいなかったが、金は持ってたな。";
			link.l1 = "あんたの酒場で乱闘に巻き込まれて怪我をしたんだ。";
			link.l1.go = "WildRose_Tavern_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tavern_2":
			dialog.text = "それがどうした？ここじゃ喧嘩なんて日常茶飯事だぜ。船乗りどもが酔っ払って、口論になって――そしたらもう止められねえよ。あんた、場数を踏んだ男に見えるが、こんなことにいちいち驚いたりしねえだろ？";
			link.l1 = "とんでもない。実は、この男は俺の古い知り合いなんだ。ここで会う約束をしてたんだが、ちょっと遅れてしまってな。 彼がどこにいるか教えてくれないか？";
			link.l1.go = "WildRose_Tavern_3";
		break;

		case "WildRose_Tavern_3":
			dialog.text = "なんで教えちゃいけねえんだ、旦那？さっきも言ったが、あいつは十分な金を持ってた――それで港役所の近くに家を借りたんだ。赤い屋根の目立つ家さ。今はそこに引きこもってて、足を治してる。 たまにここに飲みに来ることもあるが、いつも来るとは限らねえ――来る日もあれば、来ねえ日もあるぜ。";
			link.l1 = "それなら彼の家に訪ねてみるとしよう。情報をありがとう。じゃあな。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_tavern");
		break;
		//<-- Дикая Роза

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
