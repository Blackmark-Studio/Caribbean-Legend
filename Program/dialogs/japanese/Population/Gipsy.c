//Jason общий диалог цыганок
// ugeen <-- добавил продажу мышьяка из под полы
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "あら、こんにちは、あなた。何の用かしら？";
			link.l1 = "「何も、だろうな。」";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("お前に聞きたいことがある。","情報が必要だ。");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("ねえ、あなた、少し金貨を分けてくれない？そうしたら、あなたの未来を占ってあげるわ。","おい、水夫、そんなに急いで行くなよ！未来を知りたくはないかい？","タバコと銀貨を少しちょうだい、勇敢な若者よ。そしたら、あんたの未来を見てあげるよ。（ウインク）\n秘密のジプシーの魔法、聞いてみたいかい？");
				link.l1 = "悪いが、俺は行かなきゃならねえ。";
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "聞いてくれ、鍛冶屋のお嬢さん。あんたたちの仲間は薬や毒に詳しいって聞いてる。 この植物に興味があるかもしれないって言われたんだ。\nちょっと見てくれ。どう思う？";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "おい、黒い目のあんた、ちょっといいものがあるぜ……これはマンガローザだ。買ってみないか？";
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = "俺の運勢を占ってくれるか？";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("お前に聞きたいことがある。","情報が必要だ。");
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "病人の世話をしているジプシーの女を探しているんだ。あんたのことか？";
				link.l6.go = "dwh_ne_ta";
			}
			// <-- Тёмные воды исцеления

			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "おい、黒い目のあんた、ネズミ用の毒は持ってるか？俺の船であいつらがクソうるさくて困ってるんだ。";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = "もちろんよ、いい男さん。コインを少し渡して、右手を見せてごらんなさい。あなたの未来を占って、 災いを避ける手助けをしてあげるわ。あたしは絶対にごまかさないよ！返金保証付きよ！";
			link.l1 = "どうも、ここであんたの仲間が俺の財布をすり取る番みたいな気がしてきたぜ……気が変わった。今はそんな気分じゃねえ。";
			link.l1.go = "exit";
			link.l2 = "「いくら欲しいんだ？」";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "あらまあ、あなたのお財布が許す限り、そしてあなたの心が望むだけよ。八枚金貨が多ければ多いほど、 私の未来予知も遠くまで見通せるわ！";
			link.l1 = "100ペソ";
			link.l1.go = "guess_rate_1";
			link.l2 = "５００ペソ";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000ペソ";
			link.l3.go = "guess_rate_3";
			link.l4 = "５０００ペソ";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "ああ、慈悲をありがとう、私の美しい若き鷹よ！さて、聞いておくれ：  "+sTemp+"";
				link.l1 = LinkRandPhrase("へっ！そいつは面白いな。考えておくぜ……","本当か？考えておくぜ……","へえ、本当か？マジで言ってるのか？覚えておくぜ……");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "お前を待ち受けているのは、最も醜く避けられぬ不運だ。\n嘲る者に呪いあれ！\n頭上に暗雲が立ち込め、罰が必ずお前を見つけ出すだろう！";
				link.l1 = "ははは！俺が金を渡すとでも思ったのか、このジプシーの魔女め？どきやがれ！異端審問官に捕まればいいんだ！";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "ああ、ありがとう、私の美しい若き鷹よ！さて、聞きなさい："+sTemp+"";
				link.l1 = LinkRandPhrase("へっ！そいつは面白いな。覚えておくぜ……","本当か？考えておくぜ……","「へえ、本当か？マジで言ってるのか？まあ、覚えておくぜ……」","おい、もう元気になったぜ！");
				link.l1.go = "exit";
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = "お前を待ち受けるのは、最も醜く避けられぬ不運だ。\n嘲る者に呪いあれ！\n頭上に暗雲が集まり、罰が下るがよい！";
				link.l1 = "ははは！俺が金を渡すとでも思ったのか、このジプシーの魔女め？どけ！異端審問官に捕まればいいんだ！";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "ああ、銀貨をありがとう、俺の美しい若鷹よ！さて、よく聞きな："+sTemp+"";
				link.l1 = LinkRandPhrase("へっ！そりゃ面白い話だな。考えておくぜ…","本当か？考えておくぜ……","おお、本当か？マジで言ってるのか？まあ、そのことは覚えておくぜ……");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = "お前を待ち受けているのは、最も醜く避けられぬ不運だ。嘲る者に呪いあれ！\n頭上に暗雲が立ち込め、罰がお前を見つけ出すがいい！";
				link.l1 = "ハハッ！俺が金を渡すと思ったのか、このジプシーの魔女め？どきやがれ！異端審問に捕まればいいんだ！";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "おお、まあ！ご親切に感謝しますわ、私の素敵な若き鷹さん！さて、よくお聞きなさい："+sTemp+"";
				link.l1 = LinkRandPhrase("へっ！そいつは面白いな。考えておくぜ…","本当か？考えておくぜ……","へえ、本当か？マジで言ってるのか？まあ、そのことは覚えておくぜ……");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//везение
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//скрытность
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "お前を待ち受けているのは、最も醜く避けられぬ不運だ。\n嘲る者を呪え！\n頭上に暗雲が集まり、罰がお前を見つけ出すがいい！";
				link.l1 = "ははは！俺が金を渡すと思ったのか、このジプシーの魔女め？どきやがれ！異端審問官に捕まればいいんだ！";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//<-- гадание

// --> продажа мышьяка
		case "get_poison_1" :
			npchar.quest.poison_price = (hrand(3) + 1) * 10;
			if(hrand(10) == 3 || IsCharacterPerkOn(pchar, "Trustworthy"))
			{				
				dialog.text = LinkRandPhrase("あら、どうかしら、イケメンさん！少し前にネズミ退治を頼んでくる奴がいたし、 その後で誰かが砦の兵士たちに毒を盛ったのよ。島の仲間たちは大変だったわ、衛兵たちが二週間も取り調べしてきて、 ようやく犯人を見つけたの。あいつは敵のスパイだったのよ。","「それで、どうやってお前の目的を信じろってんだ？もしかして、正々堂々と決闘する勇気もねえくせに、 貴族を毒殺しようって魂胆じゃねえのか？」","酒場で誰かが商人に毒を盛って、持ち物を全部奪ったって聞いたよ。その男は死ぬまで長いこと苦しんだらしい。 口から泡を吹いて、ナスみたいに紫色になったって……。ねえ、それ、あんたがやったの、愛しい人？");
				link.l1 = "お前らジプシー女は本当に好き勝手に意見を言うもんだな！\n心配するな、お嬢ちゃん、誰かを毒殺するつもりはねえよ。毒なんて女のやり口で、俺の流儀じゃねえ。 男には剣があるが、あの忌々しいネズミどもだけはどうにもならねえんだ。";
				link.l1.go = "get_poison_2";
				if (IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(true, "Trustworthy");
			}
			else
			{
				dialog.text = "俺を罠にはめようとしてるな！いや、旦那、毒なんて持ってないぜ。薬草や薬はあるが、毒はないんだ。";
				link.l1 = "どうでもいいさ。俺に邪気をかけるんじゃねえぞ。";
				link.l1.go = "exit";
				Notification_Perk(false, "Trustworthy");
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "ああ、なんてハンサムで勇敢な方！　（小声で）お代を払って\n "+sti(npchar.quest.poison_price)+" ドゥブロン金貨だ。";
			if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
			{				
				link.l1 = "高いな……これ、本当に効いてくれよ。";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "ありえねえ！俺は故郷で同じものを五ピストルで買ったんだぜ！その金があれば自分でネズミ全部捕まえられるっての！";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "だったら自分で捕まえろよ、俺に構うな。次は衛兵を呼ぶからな。";
			link.l1 = "見張りはいらねえよ、魔女、俺はもう行くぜ。";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// <-- продажа мышьяка

	// --> Мангароса
		case "mangarosa":
			dialog.text = LinkRandPhrase("その植物を見せておくれ、坊や……ふむ……まあ、買い取ってあげてもいいわね。三百エイトピースでどうかしら？","案内してくれよ、イケメン……ふふ……まあ、それには二百五十払えるぜ。","そうだな……おっ！面白い例だぜ！二百ペソ！どうだ？")"";
			link.l1 = LinkRandPhrase("ああ、主よ……黒い目のあんた、俺は田舎者じゃねえ。この植物は知ってるぜ。マンガローサだ……","おお、本当か！？これは完璧なマンガローザの標本だ。俺を騙そうなんて思うなよ、ジプシー。","あはは、お前はこのマンガローザをそんなはした金で俺が渡すと思ってるのか。");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "わかった、わかった、いい男だな。この植物について何か知ってるようだな。50ドゥブロンだ。渡せよ。";
			link.l1 = "ちょっと待てよ！それがどう使えるのか、何のためなのか知りたいんだ。教えてくれないか？ お前たちの仲間はこの小さな草に大金を払う気満々じゃねえか！";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+hrand(25)+hrand(30, "1"))
			{
				dialog.text = "ふむ……まあ、少しくらい話しても悪くはないだろう。この植物は特別な技術がなければ、どうにもできないからな。";
				link.l1 = "聞いているぞ。";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("俺たちの仲間は金ならいくらでも払うかもしれねえが、自分たちの秘密を明かすことは絶対にないぜ。","金は金、秘密は秘密だ、若造…… ","ああ、金は払うが、話す気はねえ。")+"それで俺にマンガローザを売る気か？相場は五十ドゥブロンだぜ、それ以上払うやつはいねえよ。";
				link.l1 = "ああ、いいさ……俺には関係ねえ。五十ドゥブロンだ。持ってけ";
				link.l1.go = "mangarosa_trade";
				link.l2 = "分かってくれ、俺はそれを売りたくないんだ。なぜお前がそれを必要としているのか知りたいだけだ。 お前の知っていることを俺に教えてくれれば、ただで渡してやるぜ。";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "コインを受け取りな、若い鷹よ。もう一つ頼みがあるんだ、またこの草を持ってきてくれ。ただし、 一度にたくさんは買えないんだ、俺たちは大金を持ち歩かないからな。\n衛兵どもは俺たちを信用しねえし、嫌がらせするのが好きだからよ……";
			link.l1 = "わかった。もっと見つけたら持ってくるぜ。";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("ありえねえ！売りたくねえなら、売らなくていいさ。俺は何も教えねえぞ。","よそ者のゴージャには俺たちの秘密なんざ教えねえよ！（ぺっ）売りたくねえって？くたばっちまえ。","友よ、それはお前の耳に入れる話じゃねえ。五十ドゥブロンで売りたくねえなら、商人の娘に二百ペソで売ってこいよ。");
			link.l1 = LinkRandPhrase("それは残念だったな！どうせお前の仲間の誰かが俺に話してくれるさ。 そいつがこの植物をプレゼントとして受け取ることになるぜ。じゃあな！","なぜそんなに頑固なんだ？お前が話さないなら、もう一人に聞くだけさ。そいつにはこのマンガローザを土産にやるぜ。 じゃあな。","お前の息はニンニク臭いな。俺はそのうち欲しいものを手に入れるさ。お前みたいな奴の中には、 もっと口の軽いのもいるだろうし、そいつならタダでその植物を手に入れてくれるだろう。じゃあな。");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "なぜそんなことを聞くんだ、鷹野郎！？もちろんだ！よこせ。";
			link.l1 = "ドゥブロン金貨を五十枚よこせ。";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "おっと！どうやら失くしたか、船に置いてきちまったみたいだ。残念だな。じゃあな…";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "心配するな、俺はお前をだましたりしねえ。さあ、金貨を受け取れ。";
			link.l1 = "マンガローザを持っていけ。もし見つけたら、また持ってきてやるぜ。";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "俺たちは蕾を特別な方法ですり潰してから乾燥させ、種や茎を取り除き、それをタバコと混ぜてパイプに詰めて吸うんだ。 その混合物を吸うと……忘れられない効果があるぜ。酒の酔いみたいだが、あとで頭が痛くなることはねえ。一株で二十本分のパイプに十分だ。";
			link.l1 = "なるほど！その秘伝の技を教えてくれないか？ちゃんと礼はするぜ…";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "若き鷹よ、俺を信じろ、お前にはこんなもの必要ねえ。関わるな、あの草は身を滅ぼすぞ。頭が鈍くなって、 体も太っちまう。俺に聞くなって。\nだが……今、俺の前にいるのは剣を持った勇敢な男、海の男……もしかして船長か？";
			link.l1 = "おっしゃる通りです。";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "よく聞け。マンガローザはもっと高貴な目的にも使えるし、お前にも役立つかもしれん。 我らの癒し手の一人がその秘密をすべて知っている。お前が探しているのはその女だ。\nその植物を渡せば、彼女の名と居場所を教えてやる。ただし、彼女に秘密を明かさせるのはお前自身の問題だぞ。";
			link.l1 = "よし。植物を持っていけ、それでお前のジプシーの魔術師の居場所を教えてくれ。";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "彼女の名はアメリアだ。賢い者たちが言うには、彼女はスペイン領本土の南西海岸のどこか、 海からそう遠くない砂丘の中の小さな家で一人暮らしをしている。";
			link.l1 = "ああ、頼むからもっと具体的に言ってくれないか？";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "お前は船乗りだ、大胆な鷹だが、俺は違う。言った場所で彼女を探せ。彼女の家は海岸のすぐ近くだ。 スペイン領本土の南西、入り江のそばにある――船乗りなら知っているはずだ。";
			link.l1 = "よし、探してみるぜ……";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "彼女のところにマンガローサを持っていけ、そうじゃないと話もしてくれねえぞ。\nそれにドゥブロンも忘れるなよ、タダで教えてくれるなんて思うなよ！";
			link.l1 = "なんて強欲なんだ。考えておくぜ。話を聞かせてくれてありがとう！";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
			AddQuestRecord("Mangarosa", "4");
			// создаем и ставим Амелию
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Amelia";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_ne_ta":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "「いや、」 "+GetSexPhrase("親愛なる","美しさ")+"、俺じゃねえ、必要なのはあいつだ "+sld.name+"。彼女は今この街にいるんだ。最近見かけたよ。";
			link.l1 = "ありがとうございます。";
			link.l1.go = "exit";
		break;
		// <-- Тёмные воды исцеления
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"聞いておくれ、勇敢な鷹さん、あたしはジプシーだけど、私たちだって無闇な暴力は嫌うんだよ。 どうか剣を収めておくれ。","聞いてくれ、勇敢な鷹よ。この町の市民として、剣を納めてくれ。");
			link.l1 = LinkRandPhrase("「よし。」","ご希望の通りに。","おっしゃる通りで……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (hrand(19))
	{
		case 0: sText = "you will have luck, brave young falcon, tomorrow you'll be lucky with cards!" break;
		case 1: sText = "the fortune will be kind with you in your mercantile business, captain!" break;
		case 2: sText = "there is a misfortune awaiting you in the open sea, it's waiting just for you, wait for three days!" break;
		case 3: sText = "I see that you need to seek help from your closest ones, you won't make it alone in your next fight!" break;
		case 4: sText = "go and light a candle in a church, you have been cursed by your enemy. You won't make it without God's help!" break;
		case 5: sText = "you are going to lose a lot soon, my falcon, but don't despair and hope for yourself, seek help from you friends..." break;
		case 6: sText = "a heavy loss is waiting for you in the sea, but I see, that you, captain, will be able to ride it out even if you don't get what you want." break;
		case 7: sText = "you have entered the aim of misfortune, captain! Visit a brothel and have some rest." break;
		case 8: sText = "you will get what you want, captain, but don't expect anything good from it. All what you've wanted so passionately, captain, will bring only bad things so you'd better change your plans away." break;
		case 9: sText = "I see that there is a sign on that face of yours, the sign of ultimate luck. You will get more than you're expecting to get, young man!" break;
		case 10: sText = "you need to evaluate your wish once again and decide. Do you really need it? Your fate is giving you a chance to rethink." break;
		case 11: sText = "it's rare luck, not everyday we've getting a chance to rethink. Take a rest for a few days, bright-eyed, think about things. Don't hurry to your death!" break;
		case 12: sText = "though all of your efforts won't give you the expected result, don't despair, young falcon, great luck is waiting for you in the most unexpected day, don't lose it!" break;
		case 13: sText = "your problem won't be solved in a positive way but you are a stubborn one and you'll get what you want but, perhaps, not from the place you've expected." break;
		case 14: sText = "you'd better forget about the business you are up to. You will never be lucky in this and if you'll be continuing in it than, perhaps, your closest people will be hurt or killed." break;
		case 15: sText = "there is an event which is waiting for you, captain, and it will completely change your life. Your recent concerns will lose all of their meaning to you after that." break;
		case 16: sText = "there is danger on your way to your dream, captain, and you must be really lucky if you will be able to get what you want without heavy losses. It's better to turn away and forget your unachievable dream. Or perhaps, this fate could be tricked if you lose in cards or dice right now..." break;
		case 17: sText = "I see a strong power in you like a rock and a light as bright as the north star which leads people. Good news is waiting for you!" break;
		case 18: sText = "a bad sign is rising on your way, fear the evil eye and keep loyal men close to you." break;
		case 19: sText = "a lucky event is rising on your way right behind your own back. Look for the good which is coming right to your hands and don't chase the unachievable." break;
	}
	return sText;
}
