#include "DIALOGS\%language%\Common_Duel.c"

#define MAX_PGG_STORIES 		9
#define MAX_PGG_QUEST_STORIES 	3
#define MAX_PGG_MEET_REP 		5

string PGG_Stories[MAX_PGG_STORIES] = {
"... only devil and I know the location and the last man standing will take it all!\n",
"... and Maynard said: 'I don't expect mercy so shouldn't you'.\n",
"... he was that drunk that proposed to arrange the very special hell right there, just to see who of us will endure it longer.\n",
"... funny story of my old pal from Porto Belo...\n",
"... No, gentlemen, those are crappy anecdotes. I've got some good stories to fill your ears\n",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!\n",
"... I tend to believe that this 'Flying Dutchman' crap is a fake\n",
"... Ever heard about me being shell shocked at Key West? Although there was no visible damage, I lain for two months. And then my passion persuaded me to confess. They say, with God's help, the matter will go well ... Well, I went, and the priest asked: 'Did you kill many people, my son?' 'And how many ships sunk?' - 'Many' - I answer. And he does not let up: 'Have you seduced many wives?' Then I say: 'Padre, I did not come here to brag'. Ha-ha-ha-ha\n",
"... But in Santa Cruz there was a case during mooring. With a cry of 'Beware!' My sailor throws a whip and hits the local onlooker straight in the forehead! That screams and falls without feelings. The sailor was frightened, not waiting for the ramp he jumped on the pier and gave that poor guy some water. Finally, he woke up and told the sailor: 'You have to shout 'Watch out' when danger is coming, not 'Beware' you idiot! Ha-ha-ha! " 
};

string PGG_QuestStories[MAX_PGG_QUEST_STORIES] = {
"... Got stuck in Florida once...",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!...",
"... She killed the poor bastard right in the middle of the tavern after he suggested testing her 'officer skills' upstairs..."
}

string PGG_Meet_GoodRep[MAX_PGG_MEET_REP] = {
"Decent captains are rare breed in these waters.",
"Nobility is out of fashion these days.",
"Oh, now there's a decent captain, not like you at all, cutthroats! He-he!",
"Gentlemen, we have a decent captain at our table, who had been through fire and water countless times. So, what can you tell us, esteemed one?",
"Now there's another glorious corsair, who is not used to look for royal roads.", 
};

string PGG_Meet_BadRep[MAX_PGG_MEET_REP] = {
"Now there's another pirate!",
"Gentlemen, we have a gentleman of fortune at our table, I guess?",
"I smell gunpowder and blood! A filibuster aboard!",
"Ohh, gentlemen, now this is a seasoned corsair, who surely has something to tell in a nice company over a mug of rum... Would you like to join us?",
"Oh, I smell gunpowder... Gentlemen, we now have here another glorious corsair, who sure as hell will have a lot to tell on his confession... Ha-ha-ha!",
};

void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	int iAns;
	bool bOk;
   	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting")) Dialog.CurrentNode = "Second time";
	switch(Dialog.CurrentNode)
	{
//	Dialog.Text = "バグを見つけたら…海軍のためにQAに報告してくれ。";
//	link.l1 = "「もちろん！」";
//	link.l1.go = "exit.";
	case "First time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "おい、消え失せろよ！俺の取引を台無しにしたら、心臓を引き裂いてやるぞ！";
			link.l1 = RandPhraseSimple("俺に脅しをかけるつもりか、この野郎！？","てめえの言葉、喉につまらせてやるぜ、この野郎！");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "ああ、なるほど。商売は商売だな。幸運を祈るぜ。";
			link.l2.go = "Exit";
			break;
		}
//		Dialog.Text = "こんにちは、私の名前は "+GetFullName(NPChar)+"、君のは？";
		if(rand(10) == 3)
		{
			iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
			Dialog.Text = PGG_QuestStories[iRnd];
		}
		else
		{
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns],PGG_Meet_BadRep[iAns]);
		}		 
//		link.l1 = "私の名前は "+GetFullName(pchar)+".";
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("皆に酒だ！俺が船長だ "+GetFullName(pchar)+".","俺が『』の船長だ"+PChar.Ship.Name+" そして百人二百人の本物の悪魔どもだぜ！へっへっ！俺の名は "+GetFullName(pchar)+"."),RandPhraseSimple("自己紹介させていただきます、旦那方。私は船長 "+GetFullName(pchar)+".","まだご挨拶していませんね。俺は『の船長だ"+PChar.Ship.Name+" ～の旗の下で "+NationNameGenitive(sti(PChar.nation))+"。私の名前は "+GetFullName(pchar)+"."));
		link.l1.go = "Meeting";
		break;

	case "Meeting":
		Dialog.Text = "ここにいるみんなは俺のことを知ってるぜ！俺は "+GetFullName(NPChar)+"。はじめまして！ご用件は何でしょうか？";
		link.l1 = RandPhraseSimple("お前に用があるんだ！","お前と話がしたいんだ…");
		link.l1.go = "quest";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			sld = GetRealShip(sti(NPChar.Ship.Type));
			
			Dialog.Text = "ここにいる皆は俺のことを知ってるぜ！俺は "+GetFullName(NPChar)+"、船長 "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+".";
			link.l2 = "俺と組まないか？船が二隻あれば一隻より心強いぜ。二人でいい商売ができるだろう。";
			link.l2.go = "companion";
		}
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
		{
			link.l3 = RandPhraseSimple("俺の船で士官として仕えたいか？","お前なら俺の船の士官としてやっていけると思うぜ。どうだ、やってみるか？");
			link.l3.go = "officer";
		}
		if (bBettaTestMode)
		{
			link.l7 = "（ベータテスト）クエスト。";
			link.l7.go = "BT_Quest";
			link.l8 = "（ベータテスト）決闘。";
			link.l8.go = "outraged";
		}
		link.l9 = "「何もない。」";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "おい、消え失せろよ！俺の取引を台無しにしたら、心臓を引き裂いてやるぞ！";
			link.l1 = RandPhraseSimple("俺に脅しをかけるつもりか、この野郎！？","その言葉、飲み込ませてやるぜ、このろくでなし！");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "なるほどな。商売は商売だ。幸運を祈るぜ。";
			link.l2.go = "Exit";
			break;
		}

		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "今日はもう全部話したぞ！";
			link.l1 = "「ああ、そうだな……」";
			link.l1.go = "exit";
			break;
		}

		Dialog.text = RandPhraseSimple("何の用だ"+GetFullName(pchar)+"?","誰だ？ああ、お前か……消えろ、今はそんな気分じゃねえ……");
		link.l1 = RandPhraseSimple("商売の話はどうだ？","君と話がしたかったんだ……");
		link.l1.go = "quest";

		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
//			Dialog.Text = RandPhraseSimple("おや、誰が来たかと思えば！それは "+GetFullName(pchar)+"。何か新しい知らせはあるか？","ご機嫌いかがですか？何かご用でしょうか？");
			if(rand(10) == 3)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd]+PCharRepPhrase(" 「何か新しい知らせはあるか？」"," この諸島で何か新しい噂はあるか？");
			}
			else
			{
				iRnd = rand(MAX_PGG_STORIES - 1);
				iAns = rand(MAX_PGG_MEET_REP - 1);
				Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns]+" 「何か新しい知らせはあるか？」",PGG_Meet_BadRep[iAns]+" この諸島で何か噂はあるか？");
			}		
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = RandPhraseSimple("俺と組まないか？船が二隻あれば一隻よりずっといい。二人でうまくやれば、いい商売ができるぜ。","あんた、なかなか経験豊富な船長に見えるな。俺の旗の下で一緒に航海しないか？");
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				Dialog.Text = RandPhraseSimple("ああ、なんてこった……俺の船が沈んじまった！","おや、誰が来たかと思えば！？どうしてここに来たんだ？ところで、俺の船を失くしちまったんだよ……");
				link.l3 = RandPhraseSimple("残念だな。次はもっと運があるかもしれねえぜ。","そうかい……さて、そろそろおいとまするぜ。じゃあな。");
				link.l3.go = "exit";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l3 = RandPhraseSimple("俺の船で士官として働いてみないか？","お前なら俺の船の士官としてうまくやれると思うぜ。どうだ、乗らねえか？");
					link.l3.go = "officer";
				}
			}
//			link.l4 = "「何か新しい知らせはあるか？」";
//			link.l4.go = "rumours_capitan";
		}
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
		{
			link.l8 = PCharRepPhrase("なんて醜いツラだ。ぶん殴ってやりたくなるぜ。","「ああ、あの“友達”か。胸に新しい穴を二つほど開けてほしいのか？」");
			link.l8.go = "outraged";
		}
		link.l9 = "「何もない。」";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		break;

	case "no_ship":
		break;

//==================================================
// Officer 
//==================================================
	case "officer":
		//раз в день.
		if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("もう言っただろう、俺は興味ねえんだ。","もうすでに全て話し合ったと思っていた。");
			link.l1 = RandPhraseSimple("「どうして忘れられるんだ？」","なるほどな。じゃあな。");
			link.l1.go = "exit";
			break;
		}
		//если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("ふむ……やめておこう。二度目はない。","俺が二度もそんな餌に食いつくと思ったのか！？");
			link.l1 = RandPhraseSimple("まあ、好きにしな…","わかった。それじゃあ、またな。");
			link.l1.go = "exit";
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("ふむ……いや、そうじゃないと思う。","いや、俺は船長だ。士官として仕える気はねえ。");
			link.l1 = RandPhraseSimple("まあ、好きにしな…","わかった。それじゃあ、またな。");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		//Проверка на ПИРАТЕС, не было! :) //navy 04.04.07
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple("すでに一式揃っている。","俺に命令する準備ができてるとは思えねえな。");
			link.l1 = RandPhraseSimple("「残念だな……」","運命はそうはさせなかったのさ。");
			link.l1.go = "exit";
			break;
		}
		if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
		{
			NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)*1000);
		}
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("まさに俺が求めていたものだぜ！俺たちの剣が敵の血を味わう時が来た！だが、一つ問題がある――まだ俺には必要なものがあるんだ "+NPChar.Quest.Officer.Price+" 借金を返すためのペソだ。","お前さん、まるで本物の古参水夫みたいだな。もし金を払う気があるなら "+NPChar.Quest.Officer.Price+" ペソがあれば、俺たちはうまくやっていけそうだな。"),LinkRandPhrase("あなたのご提案は実に光栄です。かなり控えめな報酬でお引き受けしましょう。 "+NPChar.Quest.Officer.Price+" ペソ。","ふむ……お前は経験豊富な船乗りに見えるな。もし金を払う気があるなら、お前の申し出を受けてもいいかもしれねえ。 "+NPChar.Quest.Officer.Price+" ペソ。","俺たちはうまくやっていけると思うぜ、船長。だが\n "+NPChar.Quest.Officer.Price+" ペソで、取引成立だ。"));

		MakeRandomLinkOrderTwo(link, PCharRepPhrase(RandSwear() + RandPhraseSimple("That suits me fine. I just hope you're not going to charge me on daily basis.", "That's very expensive, but I hope you're worth it."), 
				LinkRandPhrase("I agree. Consider yourself a part of the crew.", "Hm... I think, I can afford it.", "Looks like you are worth it. Take the coins!")), "officer_hired",
									PCharRepPhrase(RandSwear() + RandPhraseSimple("You're not worth that much. See you...", "Too damn expensive for me."), 
				LinkRandPhrase("Yeah... Greed is not a sin...", "Are you laughing at me? I can buy a dozen like you for such money.", "That's a rip off. Where am I supposed to find such money?")), "exit");
		link.l3 = "ふむ……で、お前はどれほどの腕前なんだ？";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "お前さん、金に困ってるみたいだな、船長。";
			link.l1 = "「ああ…確かに。」";
			link.l1.go = "exit";
			break;
		}
		pchar.questTemp.HiringOfficerIDX = NPChar.index;
		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Officer.Price)));
		AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
		NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0)*0.3)

		DeleteAttribute(NPChar, "Quest.Officer");
		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");

		Dialog.Text = RandPhraseSimple("「素晴らしい！」","俺はお前を疑ったことなんてないぜ、船長。");
		link.l1 = "出航に遅れるなよ。";
		link.l1.go = "exit";
		break;

//==================================================
// Companion 
//==================================================
	case "companion":
		Dialog.Text = "バグだ、開発者に知らせてくれ";
		link.l1 = "やるぜ！";
		link.l1.go = "exit";
		//раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("もう言っただろう、俺は興味ねえんだ。","もうすでに全て話し合ったと思っていた。");
			link.l1 = RandPhraseSimple("「どうして忘れられるんだ？」","なるほどな。じゃあな。");
			link.l1.go = "exit";
			break;
		}
		//разница в один класс.. нефиг халявить
		if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar)-1)
		{
			Dialog.Text = RandPhraseSimple("俺と一緒に航海だと！？まずは少し大人になれよ！","俺はそんなもんに興味ねえぜ！");
			link.l1 = RandPhraseSimple("まあ、好きにしな…","わかった。それじゃあ、またな。");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("うーん……いや、そうじゃないと思う。","いや、結構だ。俺は誰かの下で働くのは好きじゃねえ。");
			link.l1 = RandPhraseSimple("まあ、好きにしな…","わかった。それじゃあ、またな。");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//есть ли место для компаньона.
		if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
		{
			Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("お前が気に入ったぜ！取引成立だ！もう俺たちの懐でペソがチャリンチャリン鳴ってる音が聞こえてくるぜ！","「お前は賢い」 "+GetSexPhrase("野郎","娘")+"…俺たち、きっとうまくやっていけるはずだぜ！"),LinkRandPhrase("あんたの提案、気に入ったぜ。賛成だ。","それは面白いな。知ってるか、一緒ならもっと大きなことができると思うぜ！","面白そうだな。取引成立だぜ！"));
			link.l1 = RandPhraseSimple("いいぞ！海で待ってるからな！","取引成立だ！俺たちは最高のクルーになるぜ。");
			link.l1.go = "exit";
			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			NPChar.Dialog.TempNode = "hired";
			NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
            NPChar.Payment = true;
            NPChar.Money   = 0;
            
            SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
    
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			SetCharacterRemovable(NPChar, true);
			SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
		}
		else
		{
			Dialog.Text = RandPhraseSimple("もう仲間は十分いると思うぜ。","お前はもう十分な船を持ってるだろう――なんでさらに必要なんだ？");
			link.l1 = "ああ……たしかにお前の言う通りかもな。";
			link.l1.go = "exit";
		}
		break;

	case "companion_leave":
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("お前にはもううんざりだ！！！俺はお前の艦隊を抜けるぜ！","俺の我慢はもう限界だ！俺は行くぜ。"),RandPhraseSimple("お前の冒険にはもううんざりだぜ、「提督」……俺はこれで失礼させてもらう。","お前の指揮にはもううんざりだ、俺はお前の艦隊から抜けるぜ。"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("わかった、さっさと失せな。","わかった、好きなところへ行け。"),RandPhraseSimple("よし。引き止めはしない。","それはお前の選択だ。順風を祈るぜ。"));
		link.l1.go = "Exit_Companion_Leave";
		link.l2 = PCharRepPhrase(RandPhraseSimple("ええっと……ちょっと上乗せしてくれないか？","カランバ！くそっ、もしかしてお前、ここに残ってくれねえか？船員たちにも少し余分に払ってやれるぜ！"),RandPhraseSimple("お前と別れるのは嫌だな……少しばかりの見返りでこの争いを収めるってのはどうだ？","「給料を上げるのはどうだ？」"));
		link.l2.go = "companion_stay";
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion"))
		{
			Dialog.Text = RandPhraseSimple("一度で十分だったぜ。もうお前の約束なんか信じねえ！","金で俺を釣ろうとしても無駄だ！俺の決意は揺るがねえぞ！");
			link.l1 = RandPhraseSimple("よし、健闘を祈るぜ。","だったらとっとと失せろ、二度と俺の前に現れるんじゃねえぞ！");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}
		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("報酬か？いいだろう！金額は "+NPChar.Quest.Companion.Price+" ペソで十分だぜ。","まあ、もしかしたら、もしあんたが俺の船員たちに支払いをする気があるならな "+NPChar.Quest.Companion.Price+" ペソを払えば、あいつらを引き留められるかもしれねえ。"),RandPhraseSimple("よし！少しばかりの報酬でここに残ってやるぜ "+NPChar.Quest.Companion.Price+" ペソだ！",NPChar.Quest.Companion.Price+" しばらくの間、俺と俺の船員たちを満足させてくれるだろう。"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("俺を笑ってんのか、どうなんだ！？さっさと消えろ！","はっ！俺はこの金をもっと役に立つことに使いたいぜ！"),RandPhraseSimple("おいおい、俺はそんなに金持ちじゃねえぞ！","さらばだ。これだけ払うつもりだ。"));
		link.l1.go = "Exit_Companion_Leave";
		if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("素晴らしい！これが君の報酬だ！","俺は最初から全部金のためだって疑わなかったぜ！"),RandPhraseSimple("素晴らしい！君が残ってくれて嬉しいよ。","約束したものだ。"));
			link.l2.go = "Exit_Companion_Stay";
		}
		break;

	case "Exit_Companion_Leave":
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(pchar, NPChar);

		NPChar.PGGAi.IsPGG = true;
		NPChar.RebirthPhantom = true;
		NPChar.PGGAi.location.town = GetCurrentTown();

		LAi_SetWarriorTypeNoGroup(NPChar);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		break;

	case "Exit_Companion_Stay":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Companion.Price)));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

//==================================================
// Quests
//==================================================
//==== BETTA_TEST ====
	case "BT_Quest":
		Dialog.Text = "テンプレートを選んでくれ！";
		link.l1 = "クエスト1テンプレート―海。";
		link.l1.go = "BT_Quest_1";
		link.l2 = "選択済み！クエスト1テンプレート―陸地。";
		link.l2.go = "BT_Quest_2";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = "クエスト1テンプレート―海。";
		link.l1 = "「ああ、そうだな……」";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "選択済み！クエスト1テンプレート－陸地。";
		link.l1 = "「ああ、そうだな……」";
		link.l1.go = "quest";
		break;
//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "もう全部話しただろう！";
			link.l1 = "「ああ、そうか……」";
			link.l1.go = "exit";
			break;
		}
		Dialog.Text = RandPhraseSimple("何の用だ？…ひっく！見りゃわかるだろ、俺と仲間たちで楽しくやってんだよ！…ひっく…","ええ…今日は商売にならねえな！");
		link.l1 = "なるほど……";
		link.l1.go = "exit";
		if (!PGG_IsQuestAvaible()) break; //квест нельзя брать.
		//if (!CheckAttribute(NPChar, "PGGAi.ActiveQuest") && !bBettaTestMode) break; //для релиза возможно надо будет закрыть. если закоментить, то ГГ сам может предложить дело
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber")) iRnd = sti(NPChar.PGGAi.ActiveQuest.QstNumber); //тип квеста, который хочет от нас ПГГ
		if (iRnd == -1 && !CheckAttribute(pchar, "GenQuest.PGG_Quest")) iRnd = rand(1); // может и не быть
		switch (iRnd)
		{
		case 0:
			if (sti(NPChar.Ship.Type) != SHIP_NOTUSED && sti(PChar.Ship.Type) != SHIP_NOTUSED && GetCharacterShipClass(PChar) <= 4 && GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				//квест от ПГГ
				/*if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
				{ */
				if (!CheckAttribute(pchar, "GenQuest.PGG_Quest"))
				{  // не занят другими квестами ПГГ
					Dialog.Text = "何の話だ？まあ、ちょうどいいところに来たな。商売のことなら、俺はいつでも準備万端だぜ！";
					link.l1 = "ふむ。何の話だ？";
					link.l1.go = "Quest_1_Work";
					NPChar.PGGAi.ActiveQuest = 1; // чтоб говорил от своего имени
					PChar.GenQuest.PGG_Quest = 1; // чтоб не достовали другие ПГГ
				}
				/* }
				//квест от ГГ
				else
				{
					if ()
					{
						Log_TestInfo("The test sentence of the protagonist");

						Dialog.Text = LinkRandPhrase("…その場所を知っているのは悪魔と俺だけだ、そして最後に生き残った奴がすべてを手に入れるんだ！…","…そしてマイナールトはこう答えた。「貴様に情けは期待しないし、俺も情けはかけねえぞ」","…そして外洋に出て、やつがすでに少し酔っ払っていたときにこう言いやがったんだ。「ここで暴れまくって、 最後まで立っていられる奴を見てやろうぜ」\n")+PCharRepPhrase(LinkRandPhrase("今度はまた別の海賊だな！","諸君、この卓には運に恵まれた紳士がいるのだろうか？","火薬と血の匂いがするぜ！右舷にフィリバスターだ！"),LinkRandPhrase("この海域では、まともな船長は珍しい存在だ。","最近は貴族なんて時代遅れだな。","おお、あれこそ本物の船長だぜ、お前らみたいな人斬りどもとは大違いだ！へへ！"));
						link.l1 = "俺は怒鳴ってるんじゃねえ、言ってるんだ――儲かる取引があるぜ！";
						link.l1.go = "Quest_1_Work";
					}
				}  /**/
			}
			break;
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	case "quest_onStay": // ПГГ сам подходит
		chrDisableReloadToLocation = false;
		Dialog.Text = "気をつけろ、気をつけろ！おっと！あんたのことは知ってるぜ。あんたは "+GetFullName(PChar)+"。あなたのことはよく耳にしています。";
		if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
		{
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("俺が船長だ "+GetFullName(pchar)+".","俺が『』の船長だ"+PChar.Ship.Name+" それに百人以上の本物の悪党どもだぜ！へっへっへ！俺の名前は "+GetFullName(pchar)+".")+" しかし、お前のことは覚えてねえな。",RandPhraseSimple("ご紹介させていただきます、旦那方。私は船長 "+GetFullName(pchar)+".","まだ自己紹介していなかったな。俺は『の船長だ"+PChar.Ship.Name+" ～の旗の下で "+NationNameGenitive(sti(PChar.nation))+"。私の名前は "+GetFullName(pchar)+".")+" 「だが、お前のことは覚えてねえな。」");
//			link.l1 = "ふむ……で、お前は誰だ？覚えがねえな。";
			link.l1.go = "Quest_1_Meeting";
		}
		else
		{
			link.l1 = "やあ、 "+GetFullName(NPChar)+"。元気にしてるか？";
			link.l1.go = "Quest_1_Work";
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		sld = GetRealShip(sti(NPChar.Ship.Type));
		Dialog.Text = "私は "+GetFullName(NPChar)+"、船長 "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+NPCharRepPhrase(NPChar,"。スペイン領西インド全域で最も悪名高いコルセアだ。","。ただの水夫だ。");
		link.l1 = "ああ、これでお前のことは忘れないぜ。";
		link.l1.go = "Quest_1_Work";
		NPChar.meeting = true;
		break;

	case "Quest_1_Work":
		PChar.GenQuest.PGG_Quest.Template = rand(1);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
		{
			PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
		}
		PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar)+1;
		PChar.GenQuest.PGG_Quest.Nation = rand(NON_PIRATES);
		PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		while(PChar.GenQuest.PGG_Quest.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		}
		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		while(PChar.GenQuest.PGG_Quest.Island.Shore == "")
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
			PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
			else
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
		}
		PChar.GenQuest.PGG_Quest.Island.Town = FindTownOnIsland(PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Days = 3 + GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(pchar)].id, PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Goods = GetRandomGood(FLAG_GOODS_TYPE_CROWN, FLAG_GOODS_NONE);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "「お前に用がある」 "+GetSexPhrase("相棒","娘")+"。お前のことは信頼しているが、酒場じゃ話せないんだ――余計な耳が多すぎる。俺の船で待ってるぜ。俺の古い船の名前は『"+NPChar.Ship.Name+"「。」";
//			link.l1 = "さっさと言え、俺は客にかまってる暇はねえんだ。";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("お前とその悪党どもに面白い仕事があるぜ。","もし力を合わせれば、本当にでっけえ獲物を手に入れられるかもしれねえぜ！\nもちろん、そのためには誰かを殺さなきゃならねえがな。へっへっ。"),RandPhraseSimple("船長、あなたに商談がある。","船長、あなたの評判は比類なきものです。だからこそ、ぜひとも魅力的な事業にご参加いただきたいのです。"))+RandPhraseSimple("二人だけの話だ。『』の士官室で話そう。"+NPChar.Ship.Name+" 最高のエールの樽を囲んで。今日だ。","ここで話すべきじゃねえ、詳しいことは『で交渉しよう"+NPChar.Ship.Name+" 静かに穏やかにお願いします。\nそして、あまり長くかからないでください。");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("こんな遅れはくたばっちまえ！いい知らせならすぐに知りたいし、悪い知らせならなおさらだぜ！","そんな短い話じゃ意味がねえ！酒場にちょうどいい部屋があるぜ――そこへ行こう！"),RandPhraseSimple("「それで、なぜ今すぐ酒場の部屋であんたの提案について話し合えねえんだ？」","あんたの船に行く気はほとんどねえんだ。用があるなら、ここでさっさと言いやがれ！"));
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
			Dialog.Text = "しっ…酒場で商売の話はやめとけ、余計な耳が多すぎる。俺の船『』で待ってるぜ\n"+NPChar.Ship.Name+"。そこで話そう。";
			link.l1 = "俺には時間がねえし、訪ねるのも好きじゃねえ。";
		}
		link.l1.go = "Quest_1_Work_1";
		link.l2 = PCharRepPhrase(RandPhraseSimple("行ってやるぜ。だが、もし俺の時間を無駄にするつもりなら、その舌を引き抜いてやるからな！",RandSwear()+"よし、待ってろ。お前の提案がそれだけの価値があるといいがな。俺に変な真似をするんじゃねえぞ！"),RandPhraseSimple("喜んでご招待をお受けします、船長。","面白い話だな。もちろん、行くぜ。"));
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("おい、船酔いか？母ちゃんのスカートの下にでも隠れてろよ！","怖じ気づいたのか！？消え失せろ！"),RandPhraseSimple("無理だな。金に興味がねえなら、それはお前の勝手だ。","こうするしかねえんだ。他がいいなら、勝手にしな。ほかにもたくさんいるからな。"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("ははっ！お前、なかなか度胸があるじゃねえか？よし、行ってやるぜ！","お前はなかなか筋が通ってるな、船長。よし、俺を待ってろ。"),RandPhraseSimple("よし、承知した。","お前はずいぶん口が達者だな。お前の船で商談をする準備はできているぞ。"));
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";
		link.l2 = PCharRepPhrase(RandPhraseSimple("はっ！俺をお前の船に誘い込んで殺そうとしたのか？そんな手には乗らねえぞ！","お前の言葉なんざ一文の価値もねえ！俺はお前と取引なんかしねえぞ！"),"怪しい申し出だな。断らせてもらう。");
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("俺にはラムをくれ！そしてお前は俺の前から消えろ！","もう全部話し合ったんじゃねえか？"),RandPhraseSimple("自分の用事を済ませろ。俺にはやることがあるんだ。","俺たちに話し合うことなんて何もねえと思うぜ。"));
		link.l1 = RandSwear();
		link.l1.go = "exit_2";
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "俺は自分の船でお前を待ってるって言っただろう！";
		link.l1 = "「ああ…もちろん…」";
		link.l1.go = "exit";
		NextDiag.TempNode = "Quest_1_Work_2";
		break;

	case "Exit_Quest_1_AfterTavernTalk":
		PChar.GenQuest.PGG_Quest = 1;
		PChar.GenQuest.PGG_Quest.Stage = 0;
		PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
		Group_SetTaskNone("PGGQuest");

		SetTimerConditionParam("PGGQuest1_RemoveShip_Timer", "PGGQuest1_RemoveShip_Timer", 0, 0, 0, MakeInt(GetHour() + 6), false);
		PChar.Quest.PGGQuest1_RemoveShip_Timer.function = "PGG_Q1RemoveShip";

		NPChar.Ship.Mode = "Pirate";
		NPChar.DeckDialogNode = "Quest_1_Ship";
		NPChar.Nation.Bak = NPChar.Nation;
		NPChar.Nation = GetCityNation(GetCurrentTown());
		NPChar.AlwaysFriend = true;
		NPChar.Abordage.Enable = false; //нельзя брать на абордаж
		SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

		ReOpenQuestHeader("Gen_PGGQuest1");
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern_1");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		}
		AddQuestUserData("Gen_PGGQuest1", "sShipName", NPChar.Ship.Name);

		NextDiag.CurrentNode = "Quest_1_Work_2";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Ship":
		PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";
		if (GetCompanionQuantity(PChar) == COMPANION_MAX)
		{
			Dialog.Text = RandPhraseSimple("「おいおい、それじゃダメだろ……お前には船が多すぎじゃねえか？」 "+GetSexPhrase("相棒","娘")+"?","はっ！こんな大勢の中じゃ、秘密なんて守れねえよ。さっさと失せな。");
			link.l1 = RandPhraseSimple("ご希望どおりに！","ああ、別に気にしちゃいねえよ。");
			link.l1.go = "Exit";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}
		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "よし。これで邪魔な耳は周りにいないと確信できたし、俺の水夫たちにもすでに伝えてある。だから俺の提案は、 持ち主のいない品を手に入れようってことだ。";
//			link.l1 = "「それの何がそんなに難しいんだ？そもそも、なんで俺が必要なんだよ？」";
			Dialog.Text = RandPhraseSimple("乗船を歓迎するぜ、船長！","よし。これで邪魔な耳は周りにいないと確信できるし、俺の船員たちにもすでに話は通してある。\nつまり、俺の提案は持ち主のいない品を手に入れようってことだ。")+" つまり、俺の提案は、誰のものでもない品を手に入れるってことだ。";
			link.l1 = RandPhraseSimple("「それの何がそんなに難しいんだ？そもそも、なんで俺が必要なんだよ？」","持ち主がいないだと？！冗談じゃねえか！");
		}
		else
		{
			Dialog.Text = "今はもう邪魔な耳は周りにいないと確信したぜ――さあ、思い切って話せよ！";
			link.l1 = "つまり、俺の提案は、誰のものでもない品を手に入れるってことだ。";
		}
		link.l1.go = "Quest_1_Ship_1";
		break;

	case "Quest_1_Ship_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = RandPhraseSimple("まあ、自分のものだと思っている連中もいるからな、そいつらを納得させなきゃならねえんだ。","もちろん、誰かを殺す必要があるだろうが――それが問題になるはずはないよな？");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("本題に入るぜ！","虐殺の臭いがするぜ！それで、奴らはどこにいるんだ？"),RandPhraseSimple("あなたの提案について、もっと詳しく知りたい。","「具体的に俺に何を提案してるんだ？」"));
			link.l1.go = "Quest_1_Ship_Detail";
			link.l2 = PCharRepPhrase(RandPhraseSimple("俺の目をごまかそうとしてるな。そんなことには乗らねえぞ！","それは簡単そうだが、俺はお前を信用しねえ！俺にお前のために火中の栗を拾わせたいのか？冗談じゃねえ、断るぜ！"),RandPhraseSimple("面白そうだが、俺は遠慮しておくぜ。","いや、俺は盗まねえよ。むしろ、向こうから贈り物をくれる方が好きなんだぜ。"));
			link.l2.go = "Quest_1_Ship_Refuse";
		}
		else
		{
			Dialog.Text = "「それの何がそんなに難しいんだ？そもそも、なんで俺が必要なんだよ？」";
			link.l1 = "まあ、自分のものだと思い込んでいる連中もいるが、そいつらには違うと納得させる必要があるんだ。";
			link.l1.go = "Quest_1_Ship_Detail";
		}
		break;

	case "Quest_1_Ship_Detail":
		sTmp = "A caravan belonging to " + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", transporting ";
		if (sti(PChar.GenQuest.PGG_Quest.Goods) == GOOD_SLAVES)
		{
			sTmp += "Slaves";
			PChar.GenQuest.PGG_Quest.Goods.Text = "Slaves";
		}
		else
		{
			sTmp += XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
			PChar.GenQuest.PGG_Quest.Goods.Text = XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
		}

		if (PChar.GenQuest.PGG_Quest.Island.Town == "" || PChar.GenQuest.PGG_Quest.Island.Town == "Caiman" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "Terks" || PChar.GenQuest.PGG_Quest.Island.Town == "Dominica")
		{
			sLoc = GetIslandNameByID(PChar.GenQuest.PGG_Quest.Island);
		}
		else
		{
			sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
		}
		
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			sTmp +=	", stopped not far from " + sLoc + " at the cove of " + GetLocationNameByID(PChar.GenQuest.PGG_Quest.Island.Shore) + " to resupply.";
		}
		else
		{
			sTmp += ", was caught in the storm not far from " + sLoc + " and went down. But they managed to secure part of the cargo and landed in the cove of " + GetLocationNameByID(PChar.GenQuest.PGG_Quest.Island.Shore) +
				" Now they are waiting their squadron to come.";
		}
		
		Dialog.Text = sTmp;
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("ぐずぐずするな、さっさと言え！","俺の見立ては正しかったな、他に何を知ってるんだ？"),RandPhraseSimple("それはとても興味深いですね、どうぞ続けてください！","私は "+GetSexPhrase("すべて","すべて")+" 耳だ！"));
		link.l1.go = "Quest_1_Ship_Detail_1";

		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("それは魅力的な話だが、俺はやっぱり断るぜ。揉め事なんて必要ないんだ "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+".","隊商だと？持ち主がいねえだと！？普通なら千人の兵士が護衛してるはずだろうが！いや、そんなのは駄目だ。 俺は引き上げるぜ。"),RandPhraseSimple("いや、俺は戦争中じゃねえよ "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+"、だから興味はねえ。","俺の答えはノーだ！俺は関係を壊すつもりはねえ "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+"!"));
			link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
		}
		else
		{
			Dialog.Text = "それは虐殺の臭いがするぜ！詳細はどうなってるんだ？";
			link.l1 = sTmp;
		}
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_A");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_B");
		}
		AddQuestUserData("Gen_PGGQuest1", "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData("Gen_PGGQuest1", "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text));
		AddQuestUserData("Gen_PGGQuest1", "sColony", sLoc);
		AddQuestUserData("Gen_PGGQuest1", "sShore", GetLocationNameByID(PChar.GenQuest.PGG_Quest.Island.Shore));
		break;

	case "Quest_1_Ship_Detail_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "俺たちにはこれしかない "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" 奴らを迎え撃つために。";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("In "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" 隊商があまりにも遠くへ行ってしまって、俺たちは追いつけなくなるぞ。","「ちょうど」 "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" 全員ぶっ殺して戦利品を手に入れるまで、あと何日だ！"),RandPhraseSimple("「俺たちには」 "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" 作戦全体に使える日数だ。","急いだほうがいいな "+PChar.Name+"。俺たちにはまだ "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+"."));
			link.l1 = RandPhraseSimple("間に合わせてやるぜ！今日は出航しよう。","それじゃあ、時間を無駄にするな。今日出航するように命令を出せ。");
			link.l1.go = "Exit_Quest_1_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
		}
		else
		{
			Dialog.Text = "それはとても興味深いですね、どうぞ続けてください。";
			link.l1 = "「俺たちには」 "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" 奴らを迎え撃つために。";
			link.l1.go = "Quest_1_Ship_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "時間を無駄にするな！さあ、行くぞ！";
		link.l1 = "さあ、行くぜ！";
		link.l1.go = "Exit_Quest_1_Accept";
		break;

	case "Exit_Quest_1_Accept":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
		{
			PChar.GenQuest.PGG_Quest.Stage = 2;
			PGG_Q1RemoveShip("");

			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				PGG_Q1PlaceShipsNearIsland();
			}
			else
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
				PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
			}
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
			PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

			SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
			PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			DeleteAttribute(NPChar, "AlwaysFriend");

			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);
			
			SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
		}
		NextDiag.CurrentNode = "Quest_1_Ship_Accept";
		DialogExit();
		break;

	case "Quest_1_Ship_Refuse":
		Dialog.Text = RandSwear()+"お前にはがっかりだぜ、船長。俺が何かに招待すると思ったのか "+RandPhraseSimple("「日曜ミサか？！！」","子供の遊びか！？"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("それはお前の勝手だ。決めるのは俺だぜ。","俺はたった数ペソのために縄で吊られるつもりはねえ。"),RandPhraseSimple("私の決定は最終だ、船長。","これ以上話すことはない。"));
		link.l1.go = "Exit_Quest_1_Refuse";
		break;

	case "Exit_Quest_1_Refuse":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

			AddQuestRecord("Gen_PGGQuest1", "q1_Close");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Gen_PGGQuest1");
			DeleteAttribute(NPChar, "AlwaysFriend");
		}
		NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
		NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
		DialogExit();
		break;

	case "Quest_1_Ship_BadWay":
		Dialog.Text = PCharRepPhrase("おい、いいじゃねえか！全部うまくいくさ、誰にもバレやしねえ。全員ぶっ殺してやるぜ。"),RandPhraseSimple("どこへ行くんだ、船長？もしかして役人のところか？","虎の穴に簡単に出られると思って入るのは、かなり愚かなことだ。"));
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("海の悪魔にキスでもしてこい！俺が船長だ "+GetFullName(PChar)+" お前なんかどうでもいい！俺は行くぜ！","悪魔に誓って、てめえは本当に俺をイライラさせるぜ！"),RandPhraseSimple("お前の提案には興味がねえし、もう話すことは何もねえ。じゃあな。","これ以上話し合うことはないと思う。すまないが、忙しいので行かなくてはならない。"));
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear()+PCharRepPhrase(RandPhraseSimple("Seize "+GetSexPhrase("彼","彼女")+"「引き分け」 "+GetSexPhrase("彼","彼女")+" 大砲につけ！どんな色か見てやろう "+GetSexPhrase("彼の","彼女")+" 根性だ！！！","おい！ジョニー！ヘンダーソン！それを掴め "+GetSexPhrase("悪党","娘")+"！逃がすな "+GetSexPhrase("彼","彼女")+" 救命ボートに乗り込め！！！"),RandPhraseSimple("残念だな、船長！だが、俺たちの船倉は気に入ってくれるといいぜ。さて、それからお前をどうするか決めるとしよう。","白人奴隷は長生きしねえもんだぜ、船長。だから選べよ。ヘンズがてめえの頭を撃ち抜くか、一生石切場で過ごすかだ。"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("てめえの汚ねえ内臓を食わせてやるぜ "+GetFullName(NPChar)+"!!!","どけ！この野郎ども！その場でぶっ殺してやるぞ！"),RandPhraseSimple("お前の申し出は受け入れられねえ……しかも、とんでもなく愚かだぜ！！！","見たところ、お前はあまり親切じゃねえな……どけっ！！"));
		link.l1.go = "Exit_Quest_1_DeckFight";
		break;

	case "Exit_Quest_1_DeckFight":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
		DeleteAttribute(NPChar, "AlwaysFriend");
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_SetImmortal(NPChar, true);
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		//группа может быть занята, а проверок по группам у нас нет... :(
		if (!CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			sTmp = "PGGTmp";
		}
		else
		{
			sTmp = "PGGQst";
		}
		PChar.GenQuest.PGG_Quest.GrpID = sTmp;

		for (i=1; i<5; i++)
		{
			sld = CharacterFromID("saylor_0" + i);
			LAi_group_MoveCharacter(sld, sTmp);
		}
		LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
		LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
		chrDisableReloadToLocation = true;

		PGG_ChangeRelation2MainCharacter(NPChar, -20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetFightMode(pchar, true);
		break;

	case "Quest_1_Time2Late":
		chrDisableReloadToLocation = false;

		//перенес сюда.. х.з. вроде будет лучше (Баг Изгоя.)
		PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
		PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
		PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

//		Dialog.Text = "「それで、」 "+GetFullName(PChar)+"、お前と関わったのは間違いだったようだな。これじゃ俺たちの分け前はなしだ。じゃあな！";
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("くそっ！遅れちまったじゃねえか――全部あの怠け者どものせいだ！これじゃお前と分ける戦利品もねえぞ。 "+GetFullName(PChar)+"「ステイスルを揚げろ！ここから脱出するぞ！」 ","それで、 "+GetFullName(PChar)+"、お前と関わったのは間違いだったと分かったぜ。これじゃあ俺たちの分け前はなしだ。じゃあな！"),RandPhraseSimple("奴らは消えちまった――全部お前の遅れのせいだ！これで俺たちは別々の道を行くぜ、 "+GetFullName(PChar)+".","今さら隊商には追いつけねえよ。お前と関わったのが間違いだったぜ。じゃあな！"))link.l1 = PCharRepPhrase(RandPhraseSimple("そんな隊商なんてくそくらえだ！真珠採りの方がずっといいし、危険もねえからな！","運が味方してるぜ、そして明日はまた新しい日だ！ この海には俺たちに金を奪われるのを待ってる哀れな商人どもが山ほどいるんだ！"),RandPhraseSimple("まったく残念だぜ、あんな見事な作戦が完全な失敗に終わるとはな！さらばだ！","人事を尽くして天命を待つ……さらばだ！"));
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			RemoveCharacterCompanion(pchar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;

			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_MoveCharacter(NPChar, "GroupDeck");

			PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
			if (PChar.location == "Ship_deck")
			{
/*				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromSea";
				PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";
				PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromSea";
*/				PChar.quest.Munity = "Deads";
			}
			PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
		}
		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		break;

	case "Quest_1_CheckResult":
		if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
		{
			Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
		}
		else
		{
			PChar.quest.Munity = "Deads";
		}
		chrDisableReloadToLocation = false;

		//не взяли груз...
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days)*10000;
//			Dialog.Text = "ああ、なんでお前なんかと関わっちまったんだ。全部台無しじゃねえか。だから、今から罰金を払ってもらうぜ "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+".";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Bloodthirsty "+GetSexPhrase("悪党","汚物")+"「くそっ！すべて海の悪魔の元へ沈んじまったぜ！」"+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" さっさとペソを置いて、とっとと俺の前から消えろ！","自分をネルソン提督だとでも思ってるのか？戦利品を全部沈めちまいやがって、 "+GetSexPhrase("馬鹿","愚かな女")+"！今すぐ俺によこせ "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" ペソを持ってさっさと失せろ！"),RandPhraseSimple("ここで戦争を始めるつもりか！それはまったく受け入れられん！だが、まあ、金を払えば水に流してやってもいいぞ "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" ペソ。","お前のやり方はまったくもって受け入れられねえ！全部台無しにしやがって！今すぐ俺たちの取り分を払え、その額は "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" ペソを持って好きなところへ行け！"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("俺がいなきゃ、今ごろカニの餌になってたんだぜ、この強欲野郎！","ああ、そうだな、あいつらの旗艦にお前を拿捕させてやりゃよかったぜ――そうすりゃ今ごろお前はヤードからぶら下がって、空気を汚すこともなかったのによ！"),RandPhraseSimple("お前の要求は筋違いだし、そのほのめかしは侮辱的だぞ！","罰金については合意していないから、俺は一銭も払わねえぞ！"));
			link.l1.go = "Quest_1_NotPay";
			if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
			{
				link.l2 = PCharRepPhrase(RandPhraseSimple("今はお前と戦うことはできねえ、わかってるだろうが！ペソでも喉につまらせやがれ！"," ペソだと？！今日は運の女神に見放されてるみたいだな。仕方ねえ、同意するぜ。"),RandPhraseSimple("お前の要求はとんでもないが、俺には他に選択肢がなさそうだ。","お前らの食欲はすごすぎるが、俺も同感だぜ！"));
				link.l2.go = "Exit_Quest_1_Failed";
			}
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			Dialog.Text = "ああ、なんでお前なんかと関わっちまったんだ。全部台無しじゃねえか。";
			link.l1 = "おい、勘弁してくれよ！他に方法がなかったのは自分で見ただろう。";
			link.l1.go = "Exit_Quest_1_Failed";
		}

		//минимум треть если взял, то гуд!
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3))
		{
			PChar.GenQuest.PGG_Quest.Ok = 1;
//			Dialog.Text = "さて、俺たちの戦利品は "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+"。分かれよう。";
			Dialog.Text = PCharRepPhrase("いい取引だったな！さて、俺たちの戦利品は "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","素晴らしい働きだ、船長！俺たちの戦利品は "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");
			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = Dialog.Text+PCharRepPhrase(" 俺の取り分は "," 俺の船の取り分だ―― ");
			}
			else
			{
				Dialog.Text = Dialog.Text+" お前の取り分だ ";
			}
			Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
			link.l1 = PCharRepPhrase(RandPhraseSimple("全て順調だ！ボートはもう積み込み中だぞ！","ああ、すべて間違いない。約束は約束だ。"),RandPhraseSimple("あなたの計算は正しい。私も同意する。","分け前の話になると、お前は文句なしだぜ。"));
			link.l1.go = "Exit_Quest_1_End";
			link.l2 = PCharRepPhrase(RandPhraseSimple("自分の取り分を要求するとは大胆だな！すぐにでもヤードアームに吊るされるべきだぜ！","お前の取り分だと？ここじゃ自分の分は自分で掴むもんだ。\n残ってなきゃ、それはお前の問題だぜ！"),RandPhraseSimple("分け前はもらえないと思うぜ。","俺の答えはノーだ！お前みたいな悪党どもと分け合うつもりはねえ！"));
			link.l2.go = "Quest_1_NotPay";
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
		}
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("まあ、わかったよ、俺はもう言い争わねえ！じゃあな！","血を流して事態をさらに悪化させるのはやめよう！\n次こそはうまくいくさ！"),RandPhraseSimple("さて、それではお別れだ、船長。俺には要求できる立場じゃねえからな……","俺の船の損失と損害では、公正な判断を主張することはできねえ。あんたの良心に任せるぜ、船長！"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("順風を祈るぜ！","竜骨の下に七フィートだ！"),RandPhraseSimple("さらばだ！新鮮な海の空気があんたの体に良い影響を与えるといいな！","俺たちの不運でお前がさらに手に負えなくならねえといいがな、船長！じゃあな！"));
		link.l1.go = "Exit_Quest_1_Failed";
		PChar.GenQuest.PGG_Quest.Stage = -1;

		bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("分からなかったのか！命を金で買うこともできたんだぜ！この野郎を捕まえろ！","俺たちが遊び半分でやってると思ってるのか？まあ、キールホールにかけてやれば、もっと大人しくなるだろうぜ！"),RandPhraseSimple("じゃあ、お前の寿命を縮めるしかねえな、船長！おとなしく行かねえなら、すぐに聖マルティンに会うことになるぜ！","「お前には他に選択肢を残してくれなかったな、」 "+GetFullName(PChar)+"！俺のものは俺がいただくぜ、てめえが気に入ろうが気に入るまいがな！"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("悪魔に誓って、てめえには必ず報いを受けさせてやるぜ！！！","ヨーホー！だったら俺を捕まえてみろ、船長 "+GetFullName(PChar)+"! "),RandPhraseSimple("切り傷は長くて深くなるぜ！","「さっさと死にたいか、それとも少し苦しんでからがいいか？」"));
			link.l1.go = "Exit_Quest_1_FailedFight";
		}
		break;

	case "Exit_Quest_1_Failed":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
			AddQuestRecord("Gen_PGGQuest1", "q1_FailPay");
		AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		AddQuestUserData("Gen_PGGQuest1", "sSex1", GetSexPhrase("",""));
		}
		CloseQuestHeader("Gen_PGGQuest1");
		RemoveCharacterCompanion(pchar, NPChar);

		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
		}
		else
		{
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
		}
		PGG_ChangeRelation2MainCharacter(NPChar, -5);

		LAi_SetImmortal(NPChar, true);
		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Failed":
		Dialog.Text = "もうお前とは関わりたくねえんだ！";
		link.l1 = "全然問題ないぜ。";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "取引できてよかったぜ。幸運を祈る。";
		link.l1 = "「あなたにも同じことを。」";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_End";
		break;

	case "Exit_Quest_1_FailedFight":
		RemoveCharacterCompanion(pchar, NPChar);

		LAi_LockFightMode(pchar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);	
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");
	
		PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
		chrDisableReloadToLocation = true;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
		Group_SetTaskNone("PGGQuest");

		PGG_ChangeRelation2MainCharacter(NPChar, -15);

		GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();

		Log_TestInfo("go to loc " + sTmp + " " + NPChar.location);
		NPChar.location = PChar.location;
		if (PChar.location != "Ship_Deck") sTmp = "reload1_back";

		PChar.questTemp.Chr2Remove = NPChar.id;
		LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", 5.0);

		LAi_SetImmortal(NPChar, true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_Quest_1_End":
		RemoveCharacterCompanion(PChar, NPChar);

		i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
/*		i *= (sti(PChar.GenQuest.PGG_Quest.Parts)-1);
		i += sti(PChar.GenQuest.PGG_Quest.StartGoods);
		n = GetCompanionQuantity(PChar);
		SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
		for (i = 1; i < n; i++)
		{
			iRnd = GetCompanionIndex(PChar, i);
			if (iRnd != -1)
			{
				sld = GetCharacter(iRnd);
				if (GetRemovable(sld))
				{
					Log_TestInfo("" + sld.id);
					SetCharacterGoods(sld, sti(PChar.GenQuest.PGG_Quest.Goods), 0);
				}
			}
		}
*/
		RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
/*		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_EndExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_EndExitSea.function = "PGG_Q1EndClear";
		}
		else
		{*/
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
		//}
		AddQuestRecord("Gen_PGGQuest1", "q1_OkShare");
		CloseQuestHeader("Gen_PGGQuest1");

		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		LAi_SetImmortal(NPChar, true);
		NextDiag.CurrentNode = "Quest_1_End";
		DialogExit();
  		LAi_SetWarriorType(NPChar); // сброс группы ГГ
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

	case "Quest_1_SharePrise":
		chrDisableReloadToLocation = false;
		Dialog.Text = PCharRepPhrase("本当に大虐殺だったな！女どもが一緒にいなかったのが残念だぜ！だが、戦利品で十分儲かったからいいか  "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","悪くないぜ、船長！戦利品で元は取れるな "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");

		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
        SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = Dialog.Text+" 俺の取り分は ";
		}
		else
		{
			Dialog.Text = Dialog.Text+" お前の取り分は ";
		}
		Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
		link.l1 = PCharRepPhrase(RandPhraseSimple("まったく公平だろ、くそったれ！","「全く問題ねえじゃねえか、くそったれ！」"),RandPhraseSimple("計算は正しい。その通りだ、俺も同意する。","分け前の配分となると、お前は非の打ち所がねえな。"));
		link.l1.go = "Exit_Quest_1_End";
		break;
//===================================
//              Exits 
//===================================
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;
		
	case "Exit_2":
		if (CheckAttribute(pchar, "GenQuest.PGG_Quest")) DeleteAttribute(pchar, "GenQuest.PGG_Quest"); //fix
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;		

	case "Exit_Smugglers_Fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();

		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_ShowParam":
		NextDiag.CurrentNode = "Second Time";
//		NPChar.quest.meeting = true;
		DialogExit();

		PChar.SystemInfo.OnlyShowCharacter = true;
		LaunchCharacter(NPChar);
		break;
	}
}
/* TEMPLATE
		Dialog.Text = "";
		link.l1 = "";
		link.l1.go = "";
		link.l2 = "";
		link.l2.go = "";
		link.l3 = "";
		link.l3.go = "";
*/
