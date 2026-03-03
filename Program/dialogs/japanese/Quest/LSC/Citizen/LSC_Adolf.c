// Адольф Барбье - авантюрист
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
				dialog.text = "俺はお前なんかに用はねえ。お前は理由もなく平和な民間人を襲い、ケンカをふっかけてばかりじゃねえか。消え失せろ！ ";
				link.l1 = "「ええと…」";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "やあやあ……見かけない顔だな。新入りか？";
				link.l1 = "「島に来たばかりかって？そうだ、その通りだ。俺の名前は」 "+GetFullName(pchar)+"、水夫であり冒険者だ。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"！何か用か？";
				link.l1 = LinkRandPhrase("俺に何か面白い話でもあるか？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "ちょっと様子を見に来ただけだ。じゃあな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "はは、俺も同じさ。水夫じゃねえが、冒険への情熱がここまで俺を連れてきたんだ。今じゃ他の連中と同じく、 この船の墓場で朽ち果てる運命さ。ところで、俺の名はアドルフ・バルビエだ。";
			link.l1 = "会えてよかったぜ、アドルフ。じゃあな。";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("俺に何か面白い話でもあるかい？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
			link.l2.go = "rumours_LSC";
			link.l3 = "この島についていくつか質問したいんだ。";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		//----------------------------------Адольф Барбье----------------------------------------
		case "Adolf":
			dialog.text = "「なんで俺の家に無断で入り込んできやがったんだ！？」";
			link.l1 = "お前は客に冷たくしてるぞ、アドルフ。俺はお前に用があるんだ。";
			link.l1.go = "Adolf_1";
		break;
		
		case "Adolf_1":
			dialog.text = "知らねえ奴とは取引しねえ！出て行け！";
			link.l1 = "そんな簡単に？じゃあ、ナーワルたちとは取引するのに、俺とはしないってのか？情けねえな……";
			link.l1.go = "Adolf_2";
		break;
		
		case "Adolf_2":
			dialog.text = "何を言ってやがる、道化野郎？ナーワル族に何の用だ？ここから出て行く最後のチャンスだぜ、俺が叩き出す前にな！";
			link.l1 = "度胸がねえな……今すぐ聞け！提督を撃つために使うストゥッツェンはどこだ？自分から話すか、 それとも俺がもっと説得力を見せる必要があるか？";
			link.l1.go = "Adolf_3";
		break;
		
		case "Adolf_3":
			dialog.text = "何だと？頭おかしいのか、相棒？俺のシュテュッツェンはもう売っちまったんだよ――もう持ってねえ！それに誰に売ったかなんてお前の知ったこっちゃねえし、そいつがどう使おうが俺には関係ねえ。 俺は誰も撃たねえ――提督だろうが将軍だろうが、誰だってな！わかったか、このクソ野郎？";
			link.l1 = "お前が嘘つきで人殺しだってことは分かってるぞ、アドルフ。売ったんじゃなくて、質に入れたんだろう。 それに借金を返してこの小屋を買うために大金を受け取ったことも知ってる――";
			link.l1.go = "Adolf_4";
		break;
		
		case "Adolf_4":
			dialog.text = "これは俺の金だ！俺が稼いだんだぜ！それに、俺のシュトゥッツェンも売ったんだ！";
			link.l1 = "嘘をつくな、アドルフ。お前はナーワル族に雇われて提督を撃つためにここに来たんだろう。 奴らはお前のシュトゥッツェンを買い戻す金を渡したし、この場所の代金も払った。俺よりもよく知ってるはずだ、 この扉の奥のバウスプリットこそが、正義の島でシャークの屋敷の裏手バルコニーを狙撃できる唯一の場所だってことを。 ";
			link.l1.go = "Adolf_5";
		break;
		
		case "Adolf_5":
			dialog.text = "お前、正気じゃねえぞ、相棒！檻にぶち込まれるべきだ！俺は半年もセシルがこの小屋を出るのを待ってたんだ――";
			link.l1 = "もう十分だ！お前とお前の船室を調べさせてもらう。必ずシュトゥッツェンを見つけてやる――それ以外の証拠もな！俺は確信してるぜ。\nそれから一緒にシャークのところへ行くんだ。奴はお前の目を見て、真実を見抜くだろう。";
			link.l1.go = "Adolf_6";
		break;
		
		case "Adolf_6":
			dialog.text = "ああ、この病み野郎め！俺の持ち物にイカれたクズが触るくらいなら、死んだ方がマシだ！";
			link.l1 = "いいだろう。なら、お前が死んじまえば、許可なんていらねえさ。";
			link.l1.go = "Adolf_7";
		break;
		
		case "Adolf_7":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "barmen", "stay");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_AdolfDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
			dialog.text = "さて、話そうか。何を知りたいんだ？";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "どうやってここに来たんだ？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "この島の地元の氏族について何か教えてくれないか？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "外周の船の輪を探検したことがあるか？";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "この島はキューバや本土と何か繋がりがあるのか？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "スペイン人水夫イグナシオ・アルバラードの年代記を見つけたんだ。彼はこの島について非常に詳しく記述していて、 特にいくつかの船――サン・アウグスティン、サン・ヘロニモ、そしてタルタロス――に言及していた。どれもベタンクール隊の所属で、五十年以上前に消息を絶った船だ。\n私はその遠征について調べてみた。すると、実はもう一隻、聖アンナ号という船があって、隊の財宝――大量のドゥブロン金貨――を運んでいたことが分かった。しかも、船の積荷には金鉱石まであったんだ。私はこの島を探す決心をした。\n知り合いの船長と取引して、彼のスクーナーで出航した。結末は想像できるだろう？　俺たちは島を見つけ、 ベタンクールの船も見つけ、さらには彼の孫アントニオ・デ・ベタンクールまで見つけた。それ以来、 俺はずっとここにいる。\nスクーナーは礁で壊れ、仲間は死に、俺と他の生存者はなんとかここまで泳ぎ着いた。最悪なのは、探していたもの――聖アンナ号の財宝も金鉱石も――結局見つからなかったことだ。";
			link.l1 = "興味深い話だな。俺もアルバラードの年代記を読んだことがあるぜ。";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "リバドスどもは呪われた異教徒のクズだ。あいつらはアフリカからド・ベタンクールに連れてこられた黒人奴隷の子孫さ。 白人の俺たちから剣やマスケットの使い方を学んだとはいえ、結局は野蛮人のままだ。\nナーワルたちはいい連中だぜ。頭も切れるし、戦いもうまい。職人も一流が揃ってる。俺も知り合いが多いんだ。 いつかあの一族に加わるのも悪くねえな。\n海賊どもは本当に厄介だ、くたばりやがれ！あいつらが来てから、俺たちの物資を奪いやがって、 今じゃ自分たちの食い物を売りつけてくるんだぜ！クソ野郎どもめ。数も腕も足りねえから追い出せもしねえ、 結局この血塗られた連中と一緒にやってくしかねえんだ。";
			link.l1 = "「面白いな……」";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "ああ、もちろんだ。男は稼がなきゃならねえからな。くそったれな海賊どもは、食い物を手に入れるのに金貨やペソ、 他の貴重品を要求しやがる。俺みたいな地元の人間には、クラン連中よりは安く売ってくれるが、慈善じゃねえよ。 ありがたいことに、外輪にはまだ手つかずの沈没船がたくさん残ってるから、そこを漁ればいいんだ。\n面白い仕事だが、危険も多い。水没した船倉に落ちて骨を折ったり、ロープに絡まったり、木の梁に潰されたり、 巨大なカニに食われたりすることもある――あいつら、あの辺りの難破船によくうろついてるからな。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "残念ながら、そうじゃないんだ。かつてはキューバからバッカニアや密輸業者がよくここを訪れて、 食料を金や沈没船の残骸と交換していたし、ナールヴァルたちも時々植民地に出かけていたそうだ。\nだが、それも今は昔の話さ。今じゃ誰も外輪の向こうへ小さくて脆い舟で出るなんて危険を冒したがらねえ――嵐に叩きのめされちまうし、ここにはもっといい船なんてありゃしないんだ。";
			link.l1 = "残念だな……";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("そこで何してるんだ、ああ？泥棒め！", "見てみろよ！俺がちょっと背を向けた途端に、お前は俺の箱を荒らす気か！", "俺の箱を荒らすつもりか、え？そうはさせねえぞ！");
			link.l1 = "くそっ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "何だと！？俺の宝箱を荒らすつもりか？そうはさせねえぞ！";
			link.l1 = "忌々しい女め！";
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
			dialog.text = LinkRandPhrase("聞けよ、武器はしまった方がいいぜ。見てると落ち着かねえんだ。", "ここではな、刃物を振り回すのは許されねえんだ。しまいな。", "聞けよ、剣を振り回して騎士気取りなんてやめとけ、お前には似合わねえ。しまっとけ……");
			link.l1 = LinkRandPhrase("「いいだろう。」", "いいだろう。", "おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "聞いてくれ、俺はこの街の市民だ。だから剣を下ろしてくれ。", "聞いてくれ、俺はこの街の住人だ。剣を下ろしてくれ。");
				link.l1 = LinkRandPhrase("いいだろう。", "「いいだろう。」", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "気をつけろよ、相棒。そんな武器持ってうろつかれると、こっちが落ち着かねえんだよ……", "俺は自分の目の前で武器を振り回す男どもが嫌いだ……怖いんだよ……");
				link.l1 = RandPhraseSimple("了解だ。", "しまっておく。");
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
