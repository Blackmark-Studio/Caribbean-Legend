// Антонио Бетанкур - потомок Франциско Бетанкура
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "俺の目の前から消えろ！無辜の人々を無差別に襲う野郎どもなんざ、相手にしねえ。さっさと失せろ！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "よう、いらっしゃい！何か用かい、友よ？";
				link.l1 = TimeGreeting()+"。私の名前は "+GetFullName(pchar)+"。自己紹介をしたかったんだ。実は、俺はここに来たばかりで、 この街とその住人たちのことを少しずつ知り始めたところなんだ。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"！何かご用かい？";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "アントニオ、この島の歴史に詳しいと聞いたぜ。ちょっと聞きたいことがあるんだが…";
					link.l4.go = "dolly";
				}
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"「おう、何か用か？」";
				link.l1 = LinkRandPhrase("「何か知らせか、アントニオ？」", "島で何か新しいことがあったかい？", "最近の噂話を教えてくれないか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "様子を見に来ただけだ。じゃあな、旦那！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "素晴らしい。正義の島へようこそ！大丈夫だよ、ここではみんな大家族みたいなもんだから――まあ、ナーワル族とあの汚いリバドスどもを除けば、だけどな。\n俺の名はアントニオ、アントニオ・デ・ベタンコートだ。フランシスコ・デ・ベタンコートの孫なんだが、 その名前に聞き覚えはあるか？";
			link.l1 = "フランシスコ・デ・ベタンコート？その名前は前にも聞いたことがあるな……ああ、そうだ！ホセ・ディオスが彼のことを話していたし、イグナシオ・アルバラードの記録にも書かれていたぞ！";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "俺はあんたの言う「ホセ・ディオス」なんて知らねえが、アルバラード船長なら昔ここに来たぜ――俺がガキの頃に自分の目で見たんだ。あの人は島を出て行って、自分の年代記にそのことを書いたんだよ。 それに俺のじいさん、フランシスコはスペインの提督で、自分の艦隊を率いてたんだ。\nこの場所の歴史の一部になってるのは、リヴァドスが旗艦タルタロスの黒人奴隷の子孫だからさ。 ナーワルは最初の白人入植者――タルタロス、サン・アウグスティン、サン・ヘロニモの乗組員の子孫ってわけだ。";
			link.l1 = "信じられない！じゃあ、お前はここで生まれたのか？";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "その通りだ。俺はこの島を開拓した男の孫なんだ。";
			link.l1 = "なるほど。会えて嬉しいよ、アントニオ。じゃあな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестовая часть
		case "dolly":
			dialog.text = "ああ、友よ、何でも聞いてくれ。答えられることなら答えるぜ。";
			link.l1 = "教えてくれ、「サン・ヘロニモ」というガレオン船を覚えているか？";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "ああ、覚えてるぜ。あれはとても特別な船だった。船には奇妙なインディアンの偶像があって、 汚らしい異教徒リヴァドスどもがその像に生贄を捧げていたんだ。";
			link.l1 = "どんな生け贄だ？マヤ人みたいに人の心臓をえぐり出したり、首をはねたりしてたのか？";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "いいや。犠牲者があの偶像のもとに連れてこられると、偶像はそいつを自分の中に引きずり込み、 永遠に消えてしまったんだ。悪魔の仕業さ！ありがたいことに、あの偶像は船と一緒に沈んで、 もう誰にも害を及ぼさないだろう。\n生け贄はいつも朝に捧げられていた。偶像は昇る太陽の光で黄金色に輝いたから、その時に野蛮人どもが捕らえた犠牲者――たいていはナーワル族だった――を連れてきたのさ。";
			link.l1 = "面白いな！誰かがその偶像にたどり着こうとしたことはあるのか？";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "もちろん違うぜ！まず第一に、リヴァドスは自分たち以外をサン・ヘロニモに近づけねえし、第二に、 正直なカトリック教徒は悪魔の仕掛けには近寄っちゃならねえんだ。";
			link.l1 = "そうか……リヴァドスのことはあまり好きじゃねえんだな。";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "なんてこった、あの汚い異教徒どもは大嫌いだ！さっきも言ったが、俺の祖父――神の御許に――は、あの黒人どもが反乱を起こした船の船長だった。リーダーのリヴァドスに率いられてな。 あの黒い野郎にゆっくりとした死を与えたのは、ああいう行為に対する唯一正しい、正義の報いだったんだ。\n俺は聖アンナの財宝庫の素晴らしい鍵を持っていた。今じゃ誰も財宝庫がどこにあるか知らない――たぶん海の底でカニに食われてるだろうが――でもその鍵は俺にとって甘い思い出だったんだ。それが盗まれちまった！\n黒人どもがやったに決まってる――財宝庫を探してるんだろう！どうせ無理だろうがな、もう随分昔の話だ、ハハッ！クズどもめ…";
			link.l1 = "ああ…ええと、とにかく、面白い話をありがとう！";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "どういたしまして！いつでも寄ってくれよ！";
			link.l1 = "さらば！";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "聞いてるぜ、相棒。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "じゃあ、お前は一度も島を出たことがないのか？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "お前はここで生まれたのに……それでもナーワル族じゃないのか？てっきり、この島の白人はみんなナーワル族だと思ってたぜ。";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "「それで、あんたはこの正義の島で何をしてるんだ？」";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "教えてくれ、お前はこの島を出て世界を見てみたいと思ったことがあるか？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "一度もないさ。しかし、俺を馬鹿とか狭量だなんて思うなよ。祖父からは立派な蔵書を受け継いだし、 親父からは素晴らしい教育を受けた。歴史も地理も天文学も知ってる。英語、フランス語、スペイン語、 ラテン語も話せる。朽ち果てた難破船しか見たことはないが、心の中ではヨーロッパや中国、 インドにも旅したことがあるんだ…\n実際、世界中を回った水夫どもより、俺の方がよっぽど多くを知ってると言ってもいいぜ。";
			link.l1 = "「もしかして……」";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "全部じゃないが、ほとんどそうだよ。でも俺はナーワルじゃねえし、奴らの仲間になる気もない。 なんでそんなことしなきゃいけねえんだ？炎天下で何時間も見張りをしたり、 リバドスとの喧嘩で腹を裂かれたりするためか？勘弁してくれよ、神様！俺は知識人だぜ。自分の好きなように生きて、 本を読む方が性に合ってるんだ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "父が私に立派な遺産を残してくれたから、それを賢く使っているんだ。 だから食べ物と引き換えにガラクタを探して難破船を這い回る必要もないし、 あるかどうかも分からない宝を追いかけることもないさ。\n俺が確実に知っている唯一の宝は、聖アンナの財宝だけだ。でかい鉄の箱に入ってるらしいが、 まだ誰も見つけていないんだ。\nいつか、この島の口伝をもとに、詳細な年代記を書こうと思ってるんだが、どう思う？";
			link.l1 = "価値のある探求だな！カリブにはその本にたっぷり金を払う男を少なくとも一人は知ってるぜ…";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "時々そう思うんだ。もし潮流や嵐を乗り越えられる船が来たら、もしかしたら俺も危険を冒すかもしれない。 俺の本に細かく書かれているものを、この目で見てみたいんだよ！\nでも今のところ、それはただの夢さ……";
			link.l1 = "時には夢が叶うこともある…自分で叶えればな。";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("ああ、助けてくれ！泥棒だ！！", "俺が背を向けてる隙に盗もうとするとは、この悪党め！", "それに手を出すな！それは俺の宝箱だ！誰か、助けてくれぇ！");
			link.l1 = "「くそっ！」";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "俺の箱を勝手に開けて、何をしてるつもりだ？こんなこと、ただで済むと思うなよ！";
			link.l1 = "ちくしょう！";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("剣を納めてくれ、旦那！お前さん、俺をビクビクさせるじゃねえか。", "ここで刃物を振り回すのは賢明じゃねえぜ、旦那。しまいな。", "ああ、子供みたいに剣を振り回すんじゃねえ、しまっとけ。");
			link.l1 = LinkRandPhrase("「いいだろう。」", "ご希望のままに……", "申し訳ない……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "この町の市民として、旦那、剣をしまってもらおうか！", "剣をしまいな、旦那！騒ぎを起こしてるぜ。");
				link.l1 = LinkRandPhrase("「いいだろう。」", "ご自由に……", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "旦那、頼むから剣をしまってくれ。落ち着かなくなるんだ…", "俺の前で武器を振り回す男は好きじゃねえ……怖いんだよ……");
				link.l1 = RandPhraseSimple("すまねえ。", "俺はしまっておくぜ。");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
