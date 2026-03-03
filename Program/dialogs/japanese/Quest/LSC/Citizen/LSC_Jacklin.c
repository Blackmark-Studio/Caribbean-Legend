// Жаклин Тьюрам - торговый капитан
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
				dialog.text = "俺はお前と話したくねえ。お前は理由もなく平和な民間人を襲って、けんかをふっかけるじゃねえか。じゃあな！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "ごきげんよう、旦那。あなたはここでは新顔ですね？";
				link.l1 = TimeGreeting()+"「……ああ、そうだと思う。私の名は "+GetFullName(pchar)+"。で、あんたは？";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "ああ、ボンジュール "+GetFullName(pchar)+"! "+TimeGreeting()+"！今日はどうなさいましたか？";
				link.l1 = LinkRandPhrase("「ボンジュール、Turam様！最近のニュースを教えてくれ。」", "島で何か新しいことが起きたか？", "最近の噂話を教えてくれるか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "元気にしてるか様子を見に来ただけさ。じゃあな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "ジャック・トゥラム。二年前までは立派で裕福な商人で、自分のフリュート船の船長兼船主だったんだ。だが、 今じゃ教会のネズミ並みに貧乏で、この状況が変わる望みもないさ。\nここで運のいい奴もいる。金や宝石、財宝を積んだ船を見つける者もいるが、俺は違う。 見つけたのはドゥブロン金貨が入った小さな箱と、ちょっとしたガラクタだけだ。\nまあ、食い物を買うには十分だから、飢え死にせずに済むがな……初めまして、旦那。話し相手は大歓迎だぜ。";
			link.l1 = "俺も会えて嬉しいぜ、Jacques。じゃあな！";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("「ボンジュール、Turam様！最近のニュースを教えてくれ。」", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
			link.l2.go = "rumours_LSC";
			link.l3 = "この島についていくつか質問したいんだ。";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "聞きたくてたまらないぜ。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "どうやってここに来たんだ？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "ここで何をしているんだ？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "教えてくれ…この島には女性たちもいるようだな…";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "広い世界へ戻りたいのか？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "何でもない。";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "俺の話が聞きたいのか？いいだろう。もう知ってると思うが、俺はもともと商人だった。ある日、 トルトゥーガからベリーズへ、俺の古いフリュート船で航海していたんだ。船倉には黒檀とカカオがぎっしり――貨物に全財産をつぎ込んだのさ。\nある男と、俺の貨物を法外な値段で買い取るという非常にうまい取引をまとめていた。大儲けできるはずだった。 すべて順調、空には雲ひとつなく、俺の船は鳥のように速かった。だが、災難は突然やってきた。\nキューバ近海を航行し、スペインの哨戒船を避けていたとき、突如として海賊のガレオン船に襲われた。 あんなスペイン領のど真ん中で、何をしていたんだろうな？逃げようとしたが、ガレオンは意外なほど速かった。\n海賊どもは俺たちに追いつき、攻撃してきた。クルヴリン砲にはブドウ弾が詰められていて、 最初の一斉射撃で乗組員の半分がやられ、残りも士気を失った。俺は戦おうとしたが、部下や士官たちに止められた。 結局、降伏したんだ。\n海賊どもは貨物を奪い、大砲を海に投げ捨てた。これで終わりじゃないと願っていたよ。貨物を失ったのは痛かったが、 貨物運送の契約でまた稼げるし、立ち直るつもりだった。\nだが、運命は別の筋書きを用意していた。海賊野郎どもは、無防備な俺のフリュート船に砲撃を浴びせてきた――大砲がなけりゃ、ただの的だ。今でもあいつらの笑い声が耳に残ってる……\nガレオンは去り、俺たちは沈みかけた船にしがみついていた。そこへ強い嵐が来て、大波にさらわれて海に投げ出された。 折れた帆桁に縛りつけて、なんとか浮かんでいられた。\nサメに襲われかけた話は省くよ。永遠にも思えるほど漂った末、潮流が俺をこの正義の島へ運んできた。 こうして俺は生き延びたんだ。";
			link.l1 = "ああ、それは本当に悲しい話だな。";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "俺も他の島民と同じように暮らしてるぜ。外輪でお宝を探しては、食い物と交換するんだ。 インディアンの酋長の財宝とか、スペインの金貨で満載のガレオン船を見つける夢を見てる…\n塩漬け牛肉と魚以外のものを食べるのが夢さ――ここには昔、あの巨大なカニを狩る男がいたんだ。俺は一つのハサミに五ドゥブロン払って、 何日もそれで飯を食ったもんさ。\n惜しいことに、そいつは死んじまった…まあ、誰も驚かなかったけどな――あのカニ狩りは危険な仕事だからよ。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "なるほど、言いたいことは分かるぜ。ああ、ここにも恋や駆け引きはあるさ――あって当然だろ？男は女のために、女は男のために生まれてきたんだ。それが自然の摂理ってもんさ。 ギリアンやタネケを試してみるといい、あの二人は若くて可愛くて、恋の相手を探してるぜ。\n俺自身はもう女を見つけたんだ。ナタリアっていうんだが、サンチョの酒場で給仕をしてる。最高の女さ、本当に。 ここで暮らし始めた最初の数ヶ月、俺が正気を保てたのは彼女のおかげだと思ってる。色々助けてくれて、 今は一緒にいるんだ。";
			link.l1 = "ああ、ロマンチックだな！";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "いい質問だな。もちろん、俺もそうしたいさ。だが、よく考えてみると……俺は無一文だ。持っていた金は全部貨物に突っ込んじまって、今じゃその貨物も船も海の底さ。何も残っちゃいねえ。 今思いつく金の稼ぎ方は、オランダ西インド会社で働くことくらいだ――もし雇ってくれるなら、の話だが。\nせめてスクーナーと少しの物資を買えるだけの金があればな……でも、そんなものはない。だから、島にとどまるしかねえ。少なくともここなら、 パン一切れのために夜明けから日暮れまで働かなくて済むからな。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("誰だ――あっ、泥棒！", "俺の物に手を出すな、この悪党め！", "それは俺の宝箱だ！離れろ！");
			link.l1 = "くそっ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "「俺の引き出しを勝手にあさるとは、よくもそんなことを！」";
			link.l1 = "静かに！";
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
			dialog.text = LinkRandPhrase("旦那、お願いです、武器をしまってください。怖いんです。", "おい、武器を抜いたまま走り回ってると、怪我するぜ。", "女の子たちに騎士気取りでいい格好しようとするな。しまっとけ……");
			link.l1 = LinkRandPhrase("いいだろう。", "「いいだろう。」", "え、そうか……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "旦那、この島の市民として、どうか剣を収めていただきたい。", "武器を抜いたまま歩き回るのは危険です、旦那。どうかしまってください。");
				link.l1 = LinkRandPhrase("いいだろう。", "「それでいいだろう。」", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "旦那、お願いです、武器をしまってください。怖いんです。", "男たちが海賊みたいに振る舞って、武器を構えて歩き回るのは好きじゃないんだ。");
				link.l1 = RandPhraseSimple("申し訳ない、しまっておくよ。", "俺はそれを片付けている。");
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
