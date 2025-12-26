// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("どんな質問だ？","何の用だ？");
			link.l1 = RandPhraseSimple("気が変わったんだ。","今は何も言うことはねえ。");
		    link.l1.go = "exit";
			// Rebbebion, квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter"))
			{
				if (rand(1) == 0)
				{
					link.l1 = "もしかして、エドガルド・ソッタ船長と出会ったことがあるか？彼について何か知っていたら教えてくれないか？ 知り合う価値のある男らしいぜ。";
					link.l1.go = "Sotta1";
					link.l2 = "お前さん、「おしゃべり野郎」の処刑を見に行かねえのか？";
					link.l2.go = "Lutter1";
				}
				else
				{
					link.l1 = "教えてくれ、今日の英雄、エドガルド・ソッタ船長を見かけたか？俺は残念ながら会えなかったんだ。どんな奴なんだ？ あの悪名高いおしゃべりマットを商人が捕まえたなんて信じられねえよ！";
					link.l1.go = "Sotta1_1";
					link.l2 = "町中がルッターの捕縛を祝っているんだな、海に出たことのない連中までな。"link.l2.go ="Lutter1_1";
				}
			}
			// <== квест "Путеводная звезда"
			//--> Дикая Роза
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "およそ一月半前、ジェローム・ソーヴェルニエという男がベリーズにやって来たんだ。奴は『グラス・アイ』 での喧嘩で怪我をしたが、生き延びた。どこで彼に会えるか教えてくれないか？";
				link.l1.go = "WildRose_Beliz_Citizen_1";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "一月半ほど前に、ベリーズに紳士が現れたんだ。名前はジェローム・ソーヴェルニエ。誰かを探していたらしくて、 町の人たちに話を聞いて回ってた。その後、酒場の喧嘩で怪我をしたが、幸い命は助かった。\n彼がどこにいるか教えてくれないか？";
				link.l1.go = "WildRose_Beliz_Citizen_2";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "2か月ほど前にベリーズに到着した男を探しているんだ。名前はジェローム・ソヴェルニエ。 ある紳士を探していたらしくて、そのことで町の連中に話を聞いて回っていたと思うんだが……";
				link.l1.go = "WildRose_Beliz_Citizen_3";
			}
			//<-- Дикая Роза
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "俺がその秘密組織のために働いてると思うのか "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "そうか……いや、違うな。じゃあ、達者でな。";
			link.l1.go = "exit";
			link.l2 = "他に質問はあるか？";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "俺が調査局に見えるか？知らねえよ、何も知らねえんだ。";

            link.l1 = "お前は本当にドジだな！消え失せろ。";
			link.l1.go = "exit";
			link.l2 = "他に質問はあるか？";
			link.l2.go = "new question";
		break;
		
		// Квест "Путеводная звезда" ==>
		case "Sotta1":
			dialog.text = "俺はあいつと話せなかったが、あいつの船は見たぜ――重いガレオン船だった。この海域を一人で航海するのは危険だが、ソッタは護衛なしでやってのけるんだ。";
			link.l1 = "たぶん、金貨一枚でも追いかけて、どこでも節約してるんだろうな。まあ、これ以上引き止めないぜ。じゃあな。";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sotta1_1":
			dialog.text = "ああ、信じがたい話だな！だが、旦那、聞いたことを全部鵜呑みにしちゃいけねえぜ。俺はあいつを見たんだ、 今お前を見てるくらいはっきりとな。ルッターを捕まえたのは良かったが、なんであんな商人のふりをしてるんだ？ あいつはどう見ても兵士みてえな立ち居振る舞いだ。俺にはすぐわかる――親戚が何年も兵役についてたからな。";
			link.l1 = "面白いな。まあ、誰にでも秘密はあるもんだ。そろそろ行くぜ。話を聞かせてくれてありがとな。";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "俺はもうあの男を見たぜ。同じ海賊が何年も俺たちの商人を脅かしてきたなんて、とても信じられねえ。そもそも、 どうやって自分の艦を持つことができたんだ？兵士たちがあいつを護送してるのを見た――叫んだり、泣いたり、笑ったりしてた。まるで狂人だ。";
			link.l1 = "もしかしたら、敗北と死が目前に迫った現実に耐えきれなかったのかもしれねえ。\nだが、そんなことはどうでもいい。じゃあな！";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1_1":
			dialog.text = "ああ、俺も祝ってるぜ――あいつの手で多くの同胞が死んだからな。運の悪い奴らは父親や兄弟、息子を失った……わかるだろう。あの野蛮な行為はあまりにも長く続きすぎた！俺の考えじゃ、 マットは近年で最も運のいい海賊の一人だったに違いねえよ。";
			link.l1 = "運はいつか尽きるもんだぜ。またな。";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
		
		//--> Дикая Роза
		case "WildRose_Beliz_Citizen_1":
    		dialog.text = "そんな男は知らねえよ、旦那。酒場での喧嘩なんざほとんど毎日のことだし、 怪我した奴ら全員を覚えてるなんて割に合わねえ仕事だぜ。";
    		link.l1 = "なるほど、ありがとう。ごきげんよう。";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen");
			pchar.questTemp.WildRose_Beliz_Citizen_2 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_2":
    		dialog.text = "ソヴェルニエ？フランス人か……ああ、そんな男がいたな。俺のところに助けを求めてきたが、何もしてやれなかった。それ以来会っていない、 すまないな。";
    		link.l1 = "ありがとうございます。では、引き続き聞き込みを続けます。";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2");
			pchar.questTemp.WildRose_Beliz_Citizen_3 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_3":
			dialog.text = "ジェローム旦那か！もちろん、もちろん、覚えてるぜ。酒場の喧嘩で怪我をしたんだ。それ以来、 足の傷を手当てしながら、ほとんど家から出てこねえんだよ。";
			link.l1 = "「で、その家はどこだ？」";
    		link.l1.go = "WildRose_Beliz_Citizen_3_1";
 		break;
		
		case "WildRose_Beliz_Citizen_3_1":
    		dialog.text = "ここだ、すぐ近くだぜ、港役所の隣にな。赤い屋根の家だ。そこにあいつがいるぞ。";
    		link.l1 = "助かったぜ、ありがとう！あんたに幸運を祈るぜ！";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3");
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_citizen");
 		break;
		//<-- Дикая Роза
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
