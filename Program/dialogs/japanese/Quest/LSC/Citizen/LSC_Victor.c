// Виктор Кассель - бандит
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
				dialog.text = "消えろよ、相棒。無実の奴らをけしかけて喧嘩をふっかけるような野郎とは話したくねえんだ。とっとと失せな！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "ふん……何の用だ、相棒？話がしたいってんなら、悪いが期待外れだぜ……";
				link.l1 = "残念だな……話したかったんだけど。俺はここに来たばかりで、みんなのことを知ろうとしてるんだ……";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"！何の用だ？";
				link.l1 = LinkRandPhrase("ヴィクター！何か新しい知らせはあるか？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "元気にしてるか様子を見に来ただけだ。じゃあな。";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "新入りか？ふん……まあいい。俺はヴィクター・カッセルだ。俺が機嫌悪い時に怒らせるんじゃねえぞ。いや、機嫌がいい時でもだ。 俺は無駄話なんざしねえ。しつこくされりゃ、容赦なくやり返すからな。 ";
			link.l1 = "私は "+GetFullName(pchar)+"、俺だって本気を出せるが、できればそんな必要はないと願ってる。無理に付き合う気がないなら、 こっちも邪魔はしねえ。じゃあな。";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("「ヴィクター！何か新しい知らせはあるか？」", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
			link.l2.go = "rumours_LSC";
			link.l3 = "この島についていくつか質問したいんだ。";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "手短にしろ。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "どうやってここに来たんだ？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "ここでの暮らしは、どんな感じなんだ？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "ここで一番大事な人物は誰だ？";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "この島で金を稼げる場所はどこだ？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はありません。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "なぜ気にするんだ？俺は話したくねえ、特に知らねえ男とはな。";
			link.l1 = "「イエス……すまねえ。」";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "退屈そうだな。うんざりするほどつまらなくて、意味もない退屈さだ。俺はシャークの海賊どもに加わるつもりだ――あいつらなら時々ドンパチやってるしな。きっといつか島から抜け出す方法も見つけるだろう。その日が来たら、 俺も一緒にいたいんだよ。";
			link.l1 = "本当に……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "間違いなく提督だぜ！奴はナーワルとリバドスを手のひらで転がしてて、誰も逆らえねえんだ。でも、 その次に来るのは各クランの頭領たちさ。ナーワルのドナルド・グリーンスパイと、リバドスのブラック・エディだ。 その次はナーワルの商人アクセル・ヨーストだな。それから酒場の主人サンチョ・カルペンテロ――強い酒なしじゃやってられねえからな、へへっ！";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "宝箱ならもちろんあるが、まずは錠前を破らなきゃならねえぜ。ここじゃ誰も他人を信用しちゃいねえから、 全部の宝箱に鍵がかかってるんだ。それに教えてやるよ、相棒、一番いいガラクタは船の中、 持ち主の監視下に隠されてるもんさ。\n外側の輪っかも探検できるが、腐った甲板から落ちねえように気をつけな。あるいは巨大なカニを狩るのもいいぜ。 やつらのハサミの肉はいい値で売れるからな。";
			link.l1 = "了解だ…";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("おい、クソ野郎！俺に偉そうにするなって言っただろうが。俺の胸から手をどけろ！", "お前が図々しい奴だって分かってたぜ。俺から盗もうなんて、痛い目に遭わせてやる！", "おう、ちょうどいいぜ。お前に強気に出る口実を探してたんだ！");
			link.l1 = "「アルグ！」";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "何だと！？俺の宝箱を荒らすつもりか？ただじゃ済まねえぞ！";
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
			dialog.text = LinkRandPhrase("おい、相棒、その剣をしまえよ。みっともねえぞ。", "なあ、相棒、しまわねえとサメ野郎がてめえをタルタロスにぶち込むぜ……", "その剣を持ってうろつくな、バカみたいだぜ。");
			link.l1 = LinkRandPhrase("いいだろう。", "「いいだろう。」", "おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "相棒、その剣をしまえよ。みっともねえぞ。", "なあ、相棒、しまわねえとシャークが地獄にぶち込むぞ…");
				link.l1 = LinkRandPhrase("いいだろう。", "いいだろう。", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "おい、相棒、その剣をしまえよ。みっともねえぞ。", "その剣を持ってうろつくな、バカみたいだぜ。");
				link.l1 = RandPhraseSimple("了解だ。", "俺がそれを持っていくぜ。");
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
