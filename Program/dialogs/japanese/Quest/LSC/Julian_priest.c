// брат Юлиан - священник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

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
				dialog.text = "俺はお前と話す気はねえ。理由もなくおとなしい島民を襲って、けんかをふっかけやがって。消えろ、この無神論者め！";
				link.l1 = "ご希望のままに……";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "お前が生き延びたことに驚きはしない。主の御業は神秘的だ。生と死はすべて主の御手の中にある。";
				link.l1 = "「全く同感だよ、ジュリアン兄弟。」";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "正義の島の聖なる教会へようこそ、息子よ。いつでも扉は開かれているぞ。私はジュリアン修道士だ。 我らが偉大なる主に仕える者なら誰でも歓迎するぞ。";
				link.l1 = TimeGreeting()+"。私の名は "+GetFullName(pchar)+"。お会いできて嬉しいです、ジュリアン兄弟。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"！何か用か？";
				link.l1 = "この島についていくつか質問したいんだ。";
				link.l1.go = "int_quests"; //информационный блок
				link.l2 = "あんたからポーションを買えるかい？";
				link.l2.go = "potion";
				link.l3 = "聖なる品を売っているのか？";
				link.l3.go = "amulet";
				link.l5 = "ここでちょっと祈りたかっただけさ、それと君の様子も見に来たんだ。じゃあな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "もっと頻繁に私たちの教会にいらしてくださることを願っています。\n魂を大切にしなさい、子よ。\n私はここで牧師だけでなく医者としても働いていますので、あなたの体も癒やすことができますよ。";
			link.l1 = "この島についていくつか質問したいんだ。";
			link.l1.go = "int_quests"; //информационный блок
			link.l2 = "お前からポーションを買えるか？";
			link.l2.go = "potion";
			link.l3 = "聖なる品を売っているのか？";
			link.l3.go = "amulet";
			link.l4 = "行かなくちゃ、ジュリアン兄弟。またな！";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "potion":
			dialog.text = "もちろんだよ、息子よ。どの薬が欲しいんだい？";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "簡単な治癒の薬。";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "癒しの霊薬。";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "「解毒剤だ。」";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "薬草の混合物。";
				link.l4.go = "potion4";
			}
			link.l5 = "申し訳ない、ジュリアン兄弟、考えが変わったんだ。";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "薬かい？90ペソだよ、坊や。";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "受け取ってくれ、ジュリアン兄弟。";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "今はコインが足りねえ……また後で来るぜ。";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "霊薬かい？五百ペソだよ、坊や。";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "受け取ってくれ、ジュリアン兄弟。";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "今はコインが足りねえ……また後で来るぜ。";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "「解毒剤かい？200ペソだよ、坊や。」";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "受け取ってくれ、ジュリアン兄弟。";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "今はコインが足りねえ……また後で来るぜ。";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "混ぜ物か？900ペソだ、息子よ。";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "受け取ってくれ、ジュリアン兄弟。";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "今はコインが足りねえ……また後で来るぜ。";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "ほら、薬を飲みなさい。神の導きがありますように！";
			link.l1 = "ありがとうございます、ジュリアン兄弟。";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
		break;
		
		case "amulet":
			bool bOK = (!CheckAttribute(npchar, "amulet_date")) || (GetNpcQuestPastDayParam(npchar, "amulet_date") >= 3)
			if (bOk && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > (10+hrand(110)))
			{
				npchar.quest.amulet = SelectLSCChurchAmulet();
				dialog.text = "はい、傷や病から人々を守る聖なるお守りをいくつかお渡しできます。どのお守りも値段は同じで、 金のドゥブロン十枚です。ご用意できるのは\n "+XI_ConvertString(npchar.quest.amulet)+" 今日。";
				if (PCharDublonsTotal() >= 10)
				{
					link.l1 = "はい、このお守りを買いたい。ほら、金貨だ。";
					link.l1.go = "amulet_pay";
					link.l2 = "このお守りは要らないよ、ジュリアン兄弟。俺が必要なものを手に入れるまで待たせてもらうぜ。";
					link.l2.go = "exit";
					SaveCurrentNpcQuestDateParam(npchar, "amulet_date");
				}
				else
				{
					link.l1 = "今はコインが足りねえ……また後で来るぜ。";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "いいえ、息子よ、残念ながら他には何もないんだ。\nまた別の日に会いに来てくれ、もしかしたら何か見つかるかもしれん。";
				link.l1 = "「取引成立だ、ジュリアン兄弟。」";
				link.l1.go = "exit";
			}
		break;
		
		case "amulet_pay":
			RemoveDublonsFromPCharTotal(10);
			GiveItem2Character(pchar, npchar.quest.amulet);
			Log_Info("You have received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "ありがとう、息子よ。お前の金はきっと役立つだろう。お守りを受け取りなさい、そして神のご加護がありますように！";
			link.l1 = "ありがとうございます、ジュリアン兄弟。";
			link.l1.go = "exit";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "聞いているぞ。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "「どうやってここに来たんだ、ジュリアン兄弟？」";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "あなたの教区には何人の人がいますか？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "ここで商品を売っているのは誰だ？";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "この島が滅びる危険はあるのか？嵐とか、そういうのは？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はありません。申し訳ない……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "多くの島民と同じようにな、息子よ。俺の船はハバナから新スペインへの航海中に嵐で沈んじまったんだ。 だが神に感謝するぜ、俺は生き延びて、今はここで神に仕え、 貧しい魂たちが本当の道を見つけられるよう手助けしているんだ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "俺の望むほどじゃねえな。ナーワルの連中の大半は慈悲より暴力を好むし、リバドスは貧しくて迷える羊だ。 あいつらは盲目的に異教の儀式を繰り返し、不滅の魂を危険にさらしている。中には危険な魔術師もいて、 そいつは聖なる異端審問で浄化されなきゃならねえ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "サンチョ・カルペンテロはフレロン号で酒場を営んでいて、そこで食事や酒、暖かい寝床が手に入るぜ。\nアクセル・ヨーストは「エスメラルダ号」でいろんな品物を売ってる。\n外周で面白いものを見つける奴も多いから、息子よ、通りの連中に聞いてみな。";
			link.l1 = "ありがとう！";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "すべては主のお導きにある、息子よ。私たちは主を信じ、主にすべてを委ねている。 深刻な災いはいつも正義の島から遠ざかってきた――嵐はよく外で起こるが、ここはいつも静かだ。";
			link.l1 = "ありがとうございます。安心しました。";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("そこで何してやがる、ああ？泥棒め！","見てくれよ！俺が物思いにふけってた隙に、お前は俺の箱を漁ろうとしたんだな！","俺の宝箱を調べるつもりか？ただじゃ済まねえぞ！");
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
			dialog.text = LinkRandPhrase("聞いてくれ、武器はしまってくれよ。見てると落ち着かねえんだ。","ここではな、刃物を振り回すのは許されねえんだ。しまいな。","聞けよ、剣を振り回して中世の騎士みたいな真似はやめとけ。しまえよ、そんなの似合わねえんだから…");
			link.l1 = LinkRandPhrase("「いいだろう。」","ああ、いいぜ。","おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ、俺はこの町の住人だ。だから剣を納めてくれ。","聞いてくれ、俺はこの町の市民だ。剣を納めてくれないか。");
				link.l1 = LinkRandPhrase("「いいだろう。」","ああ、いいぜ。","おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"気をつけろよ、相棒、武器を持ってうろつくんじゃねえ。俺は落ち着かねえんだ…","人が武器を抜いたまま俺の前を歩くのは好きじゃねえ……怖いんだよ……");
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

string SelectLSCChurchAmulet();
{
	string sAmulet;
	switch (hrand(3))
	{
		case 0: sAmulet = "amulet_2"; break;
		case 1: sAmulet = "amulet_3"; break;
		case 2: sAmulet = "amulet_6"; break;
		case 3: sAmulet = "amulet_7"; break;
	}
	return sAmulet;
}
