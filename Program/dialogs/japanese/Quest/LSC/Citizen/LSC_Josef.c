// Джозеф Лодердэйл - английский военный офицер
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
				dialog.text = "消えろ、旦那！無実の者を襲い、まるで下賤なごろつきのように乱闘するとは！私の前から失せなさい！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "ごきげんよう、旦那。ここで貴族にお会いできて嬉しいです。";
				link.l1 = TimeGreeting()+"。実は、カリブで庶民たちと長く過ごしすぎて、自分が貴族だということを忘れかけていたんだ。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetFullName(pchar)+"！会えて嬉しいぜ！どうだ、話でもするか？";
				link.l1 = LinkRandPhrase("やあ、ジョセフ！島では何か新しいことがあったかい？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "挨拶だけ伝えたかったんだ。じゃあな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "おや、しかも控えめな貴族とは！本物の紳士だな！あんたと俺はきっと友達になれるぜ――あの偉そうな修道院長とは違うからな……自己紹介させてもらう。コモンウェルス海軍のジョセフ・ローダーデール船長だ。";
			link.l1 = "ようこそお会いしました、船長。 "+GetFullName(pchar)+" お役に立ちますぜ！";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "ここはかなり退屈だから、夕方に酒場へ来てくれ。ワインでも飲みながら紳士らしく語り合おうじゃねえか。";
			link.l1 = "心得ておきます、旦那。では、また！";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("ごきげんよう、ジョセフ。調子はどうだ？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれるか？");
			link.l2.go = "rumours_LSC";
			link.l3 = "この島についていくつか質問したいんだ。";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "ご質問にお答えできるのは私の喜びでございます、旦那。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "どうやってここに来たんだ？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "この島ではどんなサービスが受けられるんだ？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "海軍の人間として、ここでの海賊の支配についてどう思うんだ？";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "島のあちこちで鍵のかかった箱をよく見かけるよ。みんな、お互いを信用してないんだろう？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "義務を果たしていただけさ。スペインのスループ・オブ・ウォーと戦っていたんだ。 そいつは何隻ものイギリス商船を襲ったと俺たちは睨んでいた。戦いは何時間も続いた。あと一歩で仕留められたが、 突然の嵐で全部台無しさ。両方の船が外輪の近くで難破したんだ。\n運命ってやつは皮肉が好きらしい。俺もスペインの相手も生き残ったんだ。もしかしたら、もう会ったかもしれないな。 名前はロレンツォ・ソルデッラ。珍しいカトリックのろくでなしだ。気をつけろよ。";
			link.l1 = "話を聞かせてくれてありがとう、忠告は心に留めておくよ……";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "休みたければ、サンチョの酒場に行くといい。あそこならいつでも飯と酒、そして寝床を用意してくれるさ。火薬や弾丸、 刃物なんかが必要なら、アクセル・ヨーストの店に行け。あいつがこの島の店主だ。 ジュリアン修道士は教会で薬をくれるし、聖なるお守りも売っているぞ。\nナーワル族にはユルゲン・シュミットという腕利きの鍛冶屋がいる。あいつの作る刃物は絶品だって評判さ。 ナーワル族にはもう一人名工がいるらしいが、そいつについては何も知らないんだ。\nもし海賊や他の一族と揉め事になったら、ジュゼッペ・ファツィオに会いに行け。あいつは一族同士の間を取り持つ、 いわばこの島の外交役みたいなもんだ。";
			link.l1 = "情報をありがとう！";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "好きだとは言えませんが、どうしようもありません――それに、あの連中が島に平和をもたらしたのは事実、しかも驚くほど早かったのは認めざるを得ません。 海賊たちが来る前は、部族同士がほとんど毎日のように争い、巻き込まれた無辜の人々のことなどお構いなしでした。\nさらに、海賊たちは食料を公正な値段で売ってくれるので、市民は安くて良い栄養を取れています。ただし、 最初に襲われた仕返しに、部族には法外な値段を吹っかけているようです。\n海賊の中に、とても頭の切れる男が一人います――レイトン・デクスター。彼が全ての交易を仕切っています。以前、一度だけ話したことがあります。 戦術も地図作成も経済も知り尽くした、あんな才能と教養のある男が、なぜ海賊団に加わったのか、不思議でなりません。 \n彼はこの島全体の地図を、たった数日で作り上げたんですよ？実物を見ましたが、ほとんど全てが載っていました。 きっと部族間の戦争を見越して作ったんだと思います……";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "用心深さだよ、友よ、用心深ささ。昔はこの島で盗みが横行していたって話だ——少なくとも、全ての箱に新しい錠前が取り付けられるまではな。\nそれでも……いまだに箱を開けられる奴がいるんだ。ただし、そいつが盗むのはラム酒や安物の装飾品だけで、 金や金貨には決して手を付けない。\nどの錠前も一つひとつ違っていて、合い鍵なんて存在しない——ユルゲン・シュミットがそれを徹底したんだ。あいつは刃物だけじゃなく、錠前や鍵も作る職人さ。 屋外の箱には貴重品は入っていないって聞いたぜ。本当に大事な物は、いつだって船の中にしまわれてるんだ。";
			link.l1 = "「面白いな……」";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("お前は貴族かと思ったが、ただの泥棒じゃねえか！", "俺から盗もうってのか？よし、コモンウェルス海軍で泥棒をどう扱うか、たっぷり教えてやるぜ！", "俺のシーチェストから手を離せ、この泥棒め！！");
			link.l1 = "「くそっ！」";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "泥棒だ！誰か、あの泥棒を止めてくれ！";
			link.l1 = "黙れ！";
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
			dialog.text = LinkRandPhrase("旦那、どうか剣を収めてください。騒ぎになっていますよ。", "剣を納めろ、誰かに無理やり納めさせられる前にな。", "男の勇気は評価するが、今は剣を振り回す時じゃないのでは……？");
			link.l1 = LinkRandPhrase("いいだろう。", "ご希望のままに……", "おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "ふざけるのはやめろ、旦那。剣をしまえ。", "旦那、どうか剣を収めてください。騒ぎになっていますよ。");
				link.l1 = LinkRandPhrase("結構だ。", "ご自由に……", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "旦那、どうか剣をお納めください。騒ぎになっていますよ。", "男の勇気は評価するが、今は剣を振り回す時じゃないだろう…");
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
