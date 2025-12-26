// Джаспер Пратт - каторжник
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
				dialog.text = "俺にかまうな、旦那。俺は罪もない奴を傷つけるような連中とは話さねえ！お前の方がよっぽど悪党じゃねえか！";
				link.l1 = "俺は……？";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "よう、旦那。何か用かい？";
				link.l1 = TimeGreeting()+"。私の名は "+GetFullName(pchar)+"……俺はここに来たばかりなんだ。名前を聞いてもいいか？";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"！何か用か？";
				link.l1 = LinkRandPhrase("やあ、ジャスパー。最近何か噂を聞いたかい？", "島で何か新しいことが起きたか？", "最近の噂話を教えてくれないか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "元気かどうか見に来ただけさ。また今度な、ジャスパー！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "俺か？俺はジャスパー・プラットだ。州の囚人って呼ばれてるのを聞いたことがあるかもな――だからみんな、俺を胡散臭そうに見るんだよ。ああ、奴らなんざどうでもいいさ。俺は俺だ……";
			link.l1 = "お前が昔どんな奴だったかなんてどうでもいい。今のお前がどんな奴か、それだけだ。";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "「みんながあんたみたいに考えてくれりゃよかったんだがな、旦那。」";
			link.l1 = "まあ、俺は寛大な態度で知られてるからな……";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "よくやったな。心配すんな。昔は色々あったが、今は正義の島の住人たちの財布や宝箱を狙ったりしねえよ。 やっと平穏に暮らせて嬉しいぜ。";
			link.l1 = "会えてよかったぜ、Jasper。またな！"
			link.l1.go = "終了";
			link.l2 = LinkRandPhrase("やあ、ジャスパー。最近何か噂を聞いたかい？", "この島で何か新しいことが起きたかい？", "最近の噂話を教えてくれるか？");
			link.l2.go = "rumours_LSC";
			link.l3 = "この島についていくつか質問したいんだ。";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "答えられることなら答えてやるぜ。聞いてみな。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "どうやってこの正義の島に来たんだ？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "ここが気に入ったか？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "「人々があなたを怪訝な目で見ると言っていましたね。それはあなたの過去のせいですか？」";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "この島はなかなか面白いと思わないか？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "キューバのプランテーションから逃げ出したんだ。俺たちは五人いてな、毎日ムチで打たれたり、 骨が折れるほど働かされるくらいなら死んだ方がマシだって決めたんだ。うまく見張りをだまして、 ジャングルに消えたんだよ。海岸にたどり着いたとき、いかだを作った。\nトルトゥーガを目指したが、誰も航海のやり方なんて知らなくてな、迷子になっちまった。それから水も尽きて……あのことは思い出したくねえ。とにかく、この島にたどり着いて生き残ったのは俺だけだ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "ここが気に入ってるんだよ。あのプランテーションで味わったことを思えば、ここはまるで地上の楽園さ。 多くは望まねえ……ちょっとした食い物と水、夕方のラム酒一杯――それに、ここじゃ誰も俺の皮を鞭で打とうなんてしねえ。これだけで、ここに残る理由は十分だ。時が来たら、 ここで死ねるなら本望さ。";
			link.l1 = "そうかもな……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "実はな、この島は泥棒の遊び場になっちまってるんだ。夜になると奴がやって来て、どんな錠前も役に立たねえ。 たいていは提督の部屋、つまり海賊どもの住処を荒らしていく。誰もが一度は自分の箱をひっくり返されたもんさ。\n誰が泥棒なのか誰にも分からねえから、みんな…ええと、前科持ちを疑ってるってわけだ。\nけどな、その泥棒もちょっと変わっててよ、酒瓶とか特定の小物しか盗らねえんだ。 ほんとに価値のあるもんには手を出さねえ。不思議だろ？";
			link.l1 = "ああ、おかしいな……";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "そうだ。この島の内側の船をぐるぐる泳いだことがあるぜ。水から上がれる場所は多くねえ。サン・アウグスティンなら、 ロープ橋の両脇に傾いた甲板がある。グロリアなら、倒れたマストを登ればいい……\nフェニックスの近くを泳いで、セレスの周りを回れば、船首からメアリー・キャスパーの船室にたどり着けるぜ。\nタルタロスの腹の穴は牢屋に通じてる。サン・アウグスティンの船首にも穴があって、提督の倉庫に繋がってるが、 あそこには入るなよ――見張りに斬り捨てられるぞ。それに、タルタロスの一番下の扉が閉まってるのには理由があるんだ。\nそれと、もちろんフェルナンダ号――あの一隻だけのフリュートにも乗り込める。誰も住んでないって言うが、 俺は何度も船室の中に明かりが灯ってるのを見たことがあるし、時々飲み歌が聞こえる……それに、男の叫び声もな。痛みか悲しみかは分からねえが。";
			link.l1 = "面白いな……探検することが山ほどあるぜ。";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("あっ！泥棒だ！あそこにいるぞ！", "「俺が犯罪者だって言うのか！？手を離せ、旦那！」", "盗人を見つけたぞ！ここにいる！ここにいるんだ！");
			link.l1 = "待て、違う！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "俺の胸から指を抜け！助けてくれぇ！";
			link.l1 = "くそっ！";
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
			dialog.text = LinkRandPhrase("旦那、頼むから剣をしまってくれ！みんな怯えてるんだ。", "それを振り回してるところを誰にも見られない方がいいぜ…地獄行きになっちまうからな。", "ここで刃物を振り回す必要はねえぜ。ここは仲間ばかりだ。");
			link.l1 = LinkRandPhrase("「いいだろう。」", "すまねえ。", "……わかった……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "聞けよ、旦那、それをしまえ。ここじゃ剣なんていらねえんだ。", "ここが俺の家だ。ここは安全なんだぜ、みんな剣を振り回したりしねえからな。しまってくれよ。");
				link.l1 = LinkRandPhrase("「いいだろう。」", "「わかった、じゃあ。」", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "旦那、頼むから剣をしまってくれ！みんな怯えてるんだ。", "ここが俺の家だぜ。ここは安全なんだ、みんな剣を振り回したりしねえからな。しまっとけ。");
				link.l1 = RandPhraseSimple("了解だ。", "俺が持っていくぜ。");
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
