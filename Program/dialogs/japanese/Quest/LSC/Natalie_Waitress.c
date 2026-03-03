// официантка Наталия Бушелл
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
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "おお！それにしても、あんたが溺れ死んだって聞かされてたんだぜ……嘘つきどもめ！";
				link.l1 = "ああ、もちろんさ！ははっ！俺は平気だぜ！";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "「ごきげんよう。」 "+GetAddress_Form(NPChar)+"！初めてここに来たのかい？見かけたことがないね……ぜひもっと頻繁に来てほしいな、サンチョは素晴らしい種類の酒を揃えてるから。そうそう、私はナタリー、 サンチョの酒場の仕事を手伝っているの。";
				link.l1 = TimeGreeting()+"。私の名前は "+GetFullName(pchar)+"。お会いできて嬉しいよ。俺のことを前に見たはずがないぜ。ここに来たのは最近なんだ。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"！何か用か？";
				link.l1 = LinkRandPhrase("何か面白い話でもあるのか？","島で何か新しいことが起きたか？","最近の噂話を教えてくれるか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "元気にしてるか気になってな。じゃあ、またな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "最近？また船が難破したの？私は何も聞いていないけど……それとも、トゥラム旦那みたいにマストの残骸に乗ってここへ来たの？あら、ごめんなさいね、 女ってこういう好奇心があるものだから。";
			link.l1 = "いいんだ、ナタリー。俺はここにバーク船で来たが、沈んじまったんだ。会えてよかったぜ。またどこかでな！";
			link.l1.go = "exit";
			link.l2 = "いや、大丈夫だ。ちょっとこの島についていくつか質問したかっただけだ。";
			link.l2.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "聞いているぞ。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "お前は酒場で働いてるんだな。店主について何か知ってるか？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "「それで、どうしてここに来ることになったんだ？」";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "ここには何人住んでいるんだ？";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "ここで新しい顔を見ることに、驚くことはないのか？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はありません。失礼します……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "「良いことだけだ」  "+GetAddress_Form(NPChar)+" サンチョはいつも、古いワインから素朴なエールやラムまで、実に多彩な酒を揃えているんだ。数年前、 彼は年代物のワインが大量に眠っているのを見つけてな。サンチョは二ヶ月かけて、 その瓶の箱を店まで運び込んだんだよ\nおかげで今じゃ、昔なら総督しか飲めなかったようなワインがたっぷりある。ラムも心配いらねえ。 サンチョは酒だけじゃなく、新しい噂話や役立つ助言、一晩泊まれる暖かいベッドまで用意してくれるぜ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "ああ、それは悲しい話だよ。七年前、私は求婚者と一緒に親元から逃げ出して、 サンティアゴからベリーズへ移り住むことに決めたんだ。ところが、航海士がマインの近くで道を誤って、 北へ向かってしまい、嵐に巻き込まれたんだ。私たちの船は外輪の近くで沈没したよ\nその日、私の求婚者も他のほとんどの人たちと同じように亡くなった。生き残った私たちは、 ここ正義の島で新しい人生を始めたんだ。";
			link.l1 = "悲しい話だな……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "かなり多いよ。リヴァドスとナーヴァルの両クランは人数も多くてな、何十年もここで暮らしてるんだ。 普通の住人はあまりいないけど、酒場は毎晩満員さ。俺はやっとの思いで酒を出してるよ。";
			link.l1 = "本当か？面白いな。";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "なぜ俺たちがそうしなきゃならねえんだ？ここにはよく新しい顔がたくさんやって来るんだよ。 俺たちが何人住んでるのかすら分からねえ。時々、初めて会う男が「もう一年ここに住んでる」 なんて言うこともあるんだぜ。";
			link.l1 = "「さて……」";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("そこで何してるんだ、ああ？泥棒め！","見てくれよ！俺がちょっと物思いにふけってたら、あんたは俺の箱を漁ろうとしたじゃねえか！","俺の宝箱を調べるつもりか？ただじゃ済まねえぞ！");
			link.l1 = "くそっ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "「なんだと！？俺の宝箱を調べるつもりか？そうはさせねえぞ！」";
			link.l1 = "「愚かな娘め！」";
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
			dialog.text = LinkRandPhrase("聞けよ、武器はしまってくれ。そういうのを見ると落ち着かねえんだ。","ここではな、刃物を振り回すのは許されねえんだ。しまいな。","聞けよ、中世の騎士みたいに武器振り回してんじゃねえ。しまっとけ、似合わねえんだから…");
			link.l1 = LinkRandPhrase("「いいだろう。」","ああ、いいぜ。","おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ、俺はこの町の住人だ。だから剣を納めてくれ。","聞いてくれ、俺はこの街の住人だ。剣を納めてくれないか。");
				link.l1 = LinkRandPhrase("「いいだろう。」","わかった。","おっしゃる通り……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"気をつけろよ、相棒、武器を持ってうろつくのは。俺を不安にさせるんだ…","俺の前を武器を抜いたまま歩かれるのは好きじゃねえんだ。怖いからさ……");
				link.l1 = RandPhraseSimple("了解だ。","俺がそれを持っていくぜ。");
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
