//Jason общий диалог дворянок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "ふむ。お前は～の旗の下で航海しているのか "+NationNameGenitive(sti(pchar.nation))+"「船長。私は自国の敵と話す気などない。ふん！」";
					link.l1 = "ああ、そうだ。本物の愛国者だな……";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple("俺に何の用だ、 "+GetAddress_Form(NPChar)+"？平民の水夫が貴族のご令嬢と話すのは本来ならば無作法ですが、お話は伺います。","「おや、そんな勇敢な船長が俺に何の用だ？」");
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+"。あまりお時間は取らせません、ちょっとお尋ねしたいだけです…";
					link.l1.go = "question";
					link.l2 = RandPhraseSimple("お前たちの植民地で何が起きているのか知る必要があるんだ。","情報が必要だ。");
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("街中が緊張している――王室監察官のドン・フェルナンド・デ・アラミダが到着したんだ。\nここでいろんなことを見てきたが、これは……人を変えるのは悲しみそのものじゃなく、それにどう向き合うかなんだよ。\n彼は父親の死後、別人になったと言われている。今じゃ、群島中でこれほど清廉潔白で……そして容赦のない王冠の忠臣はいないさ。","『ホーリー・マーシー』を見てみろよ！王様自ら特別な設計で造らせたって話だぜ。しかも見てみろ、傷一つねえ。 まるで聖母マリア様が守ってるみてえだ。\nだが噂も聞いたことがある……もしかすると、聖母じゃねえのかもしれねえ。","ドン・フェルナンドが殺されかけた回数を知ってるか？公海で十二回も襲撃されたんだぞ――しかもそれは去年だけでだ！\nだが、あれほど忠実で鍛え抜かれた乗組員がいて、主のご加護もある。十三回目だってきっと生き延びるさ！"),LinkRandPhrase("聞いたかい？ドン・フェルナンド・デ・アラミダがうちの街に到着したんだってさ、今まさにどこかの通りにいるらしい。 自分の目で一度見てみたいもんだな…","複雑な男だよ、このドン・フェルナンドは。祖国の汚れを清める救世主だと言う者もいれば、父親の死で何かが壊れて、 やがて俺たち全員が泣くことになるとささやく者もいる。\nだが、俺が言っておく。彼を恐れるな。彼をこうした奴らを恐れろ。","なんてハンサムな男なの、あのドン・フェルナンド！でもね、不思議なのよ。まるで誰にも気づいていないみたい。 全てが義務と奉仕。女の子がいたって聞いたけど……ある神父と会ってから、世俗の楽しみをきっぱり断ったの。まるで誓いを立てたみたいよ。"),RandPhraseSimple(RandPhraseSimple("ちくしょう、あの検査官め！あいつがいる間は街が死んじまう。商売もできねえし、楽しみもねえ。 息をするのさえ静かにしなきゃならねえみたいだ。\nそしてな、何が一番怖いか知ってるか？どこの港でも同じなんだぜ。まるで機械仕掛けみてえによ。 国王陛下が俺たち全員を苦しめるためにわざと考え出した拷問じゃねえかって思うくらいさ！","ドン・フェルナンドがまた孤児院を訪れた。惜しみなく寄付し、何時間も祈っている。あんな立派な男こそ、あの忌々 しい横領者どもに見習わせるべきだ！"),RandPhraseSimple("はっ！「聖人」フェルナンドがまた娼館を全部閉めちまったぜ。まあいいさ、あいつもすぐに出航するだろうし、 そしたらまたすぐに開くだろうよ。","検査…検査官が来たんだよ、それが何だって！？ドン・フェルナンド・デ・アルメイダ、いや、なんだっけ、 アラミダとかいう奴さ！あまりにも偉いから、総督ですら奴の前じゃ猫なで声になるって話だ。目をじっと見られると、 一瞬で全部の罪を見抜かれるらしいぜ。怖いったらありゃしねえ！")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "もう一度言わなきゃならねえのか？あいつの仲間だと疑われたくねえんだが "+NationNameAblative(sti(pchar.nation))+"「出て行け！さもないと衛兵を呼ぶぞ！あいつらはお前と話したがっているからな。」";
					link.l1 = "わかった、わかった、落ち着け。俺はもう行くぜ。";
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat("何ですの？またあなた？他の方とお話しになったらいかが？そこら中に平民がうろついていますわ、 あなたにはそちらの方がお似合いですもの。\n私はもう行かなくてはなりませんの、今夜は総督邸で晩餐会がありますし、 私のポンパドゥールもまだ仕上がっていませんのよ！","いや、今のお前は本当にうっとうしいぜ！わからねえのか？それとも頭が鈍いのか？","旦那、あなたはただの馬鹿ではなく、ろくでなしで無礼者でもあるのではと疑い始めていますわ。 これ以上くだらない質問で私を困らせるなら、夫を呼びますからね！","もう一言でも言ったら、司令官にお前の始末を頼むぞ！","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("なるほど。さらばだ。","ああ、そうだ、覚えてるよ、ただ聞きそびれただけさ……","勘違いしてるぜ……","落ち着いてくれ、奥さん、もう出ていくよ……",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase("よし、聞いてみよう。","ああ、わかったよ。何の用だ？","質問か？よし、水夫、聞いてやるぜ。");
			link.l1 = LinkRandPhrase("この町の最近の噂話を教えてくれないか？","最近ここで何か面白いことがあったかい？","カリブ海から何か知らせはありますか、お嬢様？");
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"気は確かか！？怖いじゃねえか！武器を納めろ、さもないと司令官に言いつけて砦で吊るしてもらうぞ！","気は確かか！？お前、怖いじゃねえか！武器を収めろ、さもないと司令官に言って砦で吊るしてもらうぞ！");
			link.l1 = LinkRandPhrase("「よし。」","ご希望の通りに。","「よし。」");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
