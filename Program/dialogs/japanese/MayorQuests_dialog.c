void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("樽の上に現金だ "+GetSexPhrase("相棒","娘")+"！俺の名前は "+GetFullName(npchar)+"……そして、俺は反論には慣れてねえんだ……","「さあ、財布を見せろ」 "+GetSexPhrase("相棒","娘")+"、さっさとしろよ！俺の名前は  "+GetFullName(npchar)+"……それに、俺のことを聞いたことがあるだろう……","持ってる貴重品を全部渡せ、それから財布の中身もいただくぜ。さっさとしろ、俺はあまり我慢強くねえんだ。 血に飢えてる方は自信があるがな！");
			Link.l1 = LinkRandPhrase("へっ、あんたがあの有名な盗賊か "+GetFullName(npchar)+"「地元の総督が」 "+sTemp+" 「しゃべるのをやめないのか？」","「おお、あんたが地元の総督に追われてるあの盗賊か」 "+sTemp+"?!","Glad"+GetSexPhrase("","")+" 「あなたに会えて」 "+GetFullName(npchar)+"。地元の総督、 "+sTemp+" あなただけのことを話している。");
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("ああ、俺はこの土地じゃ有名なんだぜ、へへ……待てよ、お前もしかしてまた別のやつじゃねえか "+GetSexPhrase("汚ねえ野郎","汚えあばずれ")+" 「俺を追跡するために彼を送り込んだ総督のことか？」","総督は俺の親友だ、それは本当さ。ところで、もしかしてお前は、 "+GetSexPhrase("また一人の英雄が送り込まれた","もう一人の女傑が送り込まれた")+" 俺の首に、あいつがかけたのか？","総督は俺の大親友さ、隠しちゃいねえよ、へへ。しかし、どうしてそれを知ってるんだ？もしかして、 あいつが俺を追わせたのか？");
			Link.l1 = LinkRandPhrase("その通りだ、この悪党め。死ぬ覚悟をしろ！","頭の回転が速いじゃねえか！よし、お前の始末に取りかかるぜ。もう話は終わりだ。","ああ、俺だよ。武器を抜け、相棒！お前の血の色を見せてもらおうじゃねえか。");
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase("「ああ、もういい！そんな面倒ごとは俺には全く必要ねえんだ…」","いやいや、俺は決して英雄なんかじゃねえよ……","いや、いや、絶対にそんなことしない！面倒ごとはごめんだ…");
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("「それでいい」 "+GetSexPhrase("相棒","娘")+"…さっさと失せろ！","それが正しい判断だぜ。俺がどれだけ多くの英雄をあの世に送ってきたか、知ってりゃよかったのにな……まあ、もういい。さっさと消えな。 "+GetSexPhrase("クソ野郎","あばずれ")+"!","Good "+GetSexPhrase("坊主","少女")+"！とても賢明な判断だ――他人のことに首を突っ込まないのはな……よし、さっさと行け。 "+GetSexPhrase("相棒","娘")+".");
			Link.l1 = "さらばだ、幸運を祈っているぞ…";
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашёл, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// ОЗГ - пассажир
		case "ContraPass_abordage":
			dialog.text = "うおお、てめえ、この野郎！俺の船を襲うとは何様のつもりだ！？そのツケはしっかり払ってもらうぜ！";
			link.l1 = "逆に、俺はこれで報酬をもらってるんだ。お前の船には「という名の男が乗っているだろ。 "+pchar.GenQuest.TakePassenger.Name+"「……俺が必要としているのはあいつだ。」";
			link.l1.go = "ContraPass_abordage_1";
		break;
		
		case "ContraPass_abordage_1":
			dialog.text = "この悪党が俺たちに災いをもたらすと分かっていたんだ……だが、そう簡単にはやられねえぞ！覚悟しろ、汚え海賊め！";
			link.l1 = "防御を考えるべきなのはお前だ、野郎。";
			link.l1.go = "ContraPass_abordage_2";
		break;
		
		case "ContraPass_abordage_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Tempsailor":
			dialog.text = "船長、ご命令通り船室と船倉を捜索しました。あの悪党は隠れようとしましたが、俺たちが見つけました。";
			link.l1 = "素晴らしい！今そいつはどこにいるんだ？";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "ご命令通り、彼は船倉にいます。";
			link.l1 = "素晴らしい！さあ、この古い船から降りよう。帰る時間だ。";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "「すぐに参ります、船長！」";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
			sld.name = pchar.GenQuest.TakePassenger.Name;
			sld.lastname = "";
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;
		
		case "Fugitive_city": // ходит по городу
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "何の用だ、旦那？";
			link.l1 = "ほう、ほう……つまりお前が "+pchar.GenQuest.FindFugitive.Name+"、だろう？会えて本当に嬉しいよ……";
			link.l1.go = "Fugitive_city_1";
		break;
		
		case "Fugitive_city_1":
			dialog.text = "まあ、それは確かに俺だが、どうして俺に会えて嬉しいんだ？今まで一度も会ったことがないのに、妙じゃねえか……説明してくれないか？";
			link.l1 = "もちろんだ。私は来た "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity+"Gen")+"「地元総督の命令だ。お前は逮捕される、そして俺はお前をそのまま同じ町に連れて行かねばならん……ああ、それと剣から手を離せ！変な真似はするなよ、旦那、さもないと酷い目に遭うぞ！」";
			link.l1.go = "Fugitive_city_2";
		break;
		
		case "Fugitive_city_2":
			dialog.text = "とうとう俺を見つけたか……旦那、聞いてくれ、もしかしたら考えが変わるかもしれねえ。そうだ、俺は守備隊を脱走した。だが、 あの軍隊の堕落を見ていられなかったんだ！\n俺は静かな暮らしを望んでいて、この村でやっとそれを手に入れた……頼む、俺を放っておいてくれ。俺を見つけられなかったとか、海賊と一緒に大海原へ逃げたとか、そう伝えてくれ。 代わりに、この琥珀の袋をやる。とても価値のある品だぜ……";
			link.l1 = "俺に賄賂を渡そうなんて考えるな、旦那！武器を渡して俺について来い！";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "ふむ……堕落か？静かで穏やかな生活か？よし、望みを叶えてやろう。琥珀はどこだ？";
			link.l2.go = "Fugitive_city_gift";
		break;
		
		case "Fugitive_city_fight":
			dialog.text = "ならば剣を抜け、傭兵！俺をそう簡単に倒せると思うなよ！";
			link.l1 = "よし、お前の腕前を見せてもらおうじゃねえか！";
			link.l1.go = "Fugitive_fight_1";
		break;
		
		case "Fugitive_city_gift":
			TakeNItems(pchar, "jewelry8", 50+hrand(25));
			TakeNItems(pchar, "jewelry7", 2+hrand(5));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received amber");
			dialog.text = "ここだ……そして、二度とあなたや他の「使者」たちに会うことがないよう願っているよ。";
			link.l1 = "安心しなさい、そんなことはありませんよ。では、旦那、さようなら！";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_gift_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.FindFugitive = "Found"; //флаг провалил
			AddQuestRecord("MayorsQuestsList", "12-4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity));
		break;
		
		case "Fugitive_fight_1":// в городе и бухте
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Fugitive_afterfight":
			dialog.text = "うおおっ！お前の勝ちだ、くそっ！降参する……";
			link.l1 = "言葉に気をつけろ、旦那！さあ、サーベルを渡せ……ついて来い、変な真似はするなよ！";
			link.l1.go = "Fugitive_afterfight_1";
		break;
		
		case "Fugitive_afterfight_1":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			//DeleteAttribute(npchar, "LifeDay");
			npchar.lifeday = 0;
			LAi_SetImmortal(npchar, true);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			pchar.GenQuest.FindFugitive = "Execute"; //флаг выполнил успешно
			pchar.quest.FindFugitive1.win_condition.l1 = "location";
			pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity+"_townhall";
			pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
			SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;
		
		case "Fugitive_shore": // в бухте
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "旦那、今はあなたと話す気分じゃないんで……";
			link.l1 = "それでも、俺と話さなきゃならねえ。お前は "+pchar.GenQuest.FindFugitive.Name+"だろう？否定しないほうがいいと思うぜ。";
			link.l1.go = "Fugitive_shore_1";
		break;
		
		case "Fugitive_shore_1":
			dialog.text = "俺は否定しねえよ、それが俺だ。で、何の用だ？";
			link.l1 = "お前を連れて行かなくちゃならねえ "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+"、地元の総督があなたに会いたがっている。変な真似はするなよ！武器を渡して俺について来い！";
			link.l1.go = "Fugitive_shore_2";
		break;
		
		case "Fugitive_shore_2":
			dialog.text = "なるほど…旦那、軽率な行動を取る前に、ひとつ話をさせてくれ。そうだ、俺は守備隊を脱走した。だが、理由があったんだ。 もうあの務めには耐えられねえ！わかってくれるか？無理なんだ！\n俺は静かな暮らしがしたいんだ。そしてここ、この村でそれを見つけた…頼む、俺のことは放っておいてくれ。見つけられなかったとか、海賊と一緒に外洋へ逃げたとか、そう伝えてくれ。 その代わり、俺の週ごとの真珠の漁獲を全部渡す。それが俺の全てだ。";
			link.l1 = "俺に賄賂を渡そうなんて考えるな、旦那！武器を渡して俺について来い！";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "ふむ……軍務に疲れたのか？平和な暮らしがしたいんだな？よし、お前の願いを叶えてやろう。で、真珠はどこだ？";
			link.l2.go = "Fugitive_shore_gift";
		break;
		
		case "Fugitive_shore_gift":
			TakeNItems(pchar, "jewelry52", 100+hrand(40));
			TakeNItems(pchar, "jewelry53", 400+hrand(100));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received pearls");
			dialog.text = "ここだ……そして、二度とお前や他の「使者」たちに会わないことを願っているぞ。";
			link.l1 = "安心しな、そんなことはないぜ。じゃあな、旦那！";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern": // в таверне
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "ええっ…ひっく！旦那、俺は連れなんか探してねえんだ――特にあんたみたいなのはな。消え失せろ！";
			link.l1 = "「だが、俺は本当にお前と一緒にいたいんだ」 "+pchar.GenQuest.FindFugitive.Name+"！そしてお前は俺の船の船倉で俺と一緒にいることを我慢してもらうぜ。俺たちはこれから  "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+"、町の総督のところへ。あなたに会いたくてたまらないようです。";
			link.l1.go = "Fugitive_tavern_1";
		break;
		
		case "Fugitive_tavern_1":
			dialog.text = "「ひっく！」"+RandSwear()+" やっぱり俺を見つけやがったか！聞けよ、相棒、お前は何があったか知らねえし、現場にもいなかっただろ！ 俺はもうあの仕事を続けられなかったんだ、本当に無理だった！今でも毎晩酒に溺れて、全部忘れようとしてるんだよ。\nなあ、取引しようぜ。あいつには俺を見つけられなかったとか、海賊と一緒に大海原へ逃げたって伝えてくれ。 その代わり、地元の洞窟で見つけた金塊を全部やるよ。俺の持ち物はそれだけだ、分かるだろ？全部やるから、 もう二度とあいつの顔を見なくて済むようにしてくれ "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+"...";
			link.l1 = "俺に賄賂を渡そうなんて考えるな、旦那！武器を渡して俺について来い！";
			link.l1.go = "Fugitive_tavern_fight";
			link.l2 = "ふむ……嫌な話か？悪夢にうなされてるのか、それとも良心の呵責か？まあいい、ここはお前に任せるとしよう。で、 お前の金塊はどこだ？";
			link.l2.go = "Fugitive_tavern_gift";
		break;
		
		case "Fugitive_tavern_gift":
			TakeNItems(pchar, "jewelry5", 50+hrand(30));
			TakeNItems(pchar, "jewelry6", 100+hrand(50));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received nuggets");
			dialog.text = "ここだ……そして、二度とあなたや他の「使者」たちに会わないことを願っているよ。";
			link.l1 = "安心しなさい、そんなことにはならない。さようなら、旦那！";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern_fight":
			dialog.text = "ならば剣を抜け、傭兵！俺をそう簡単に倒せると思うなよ！";
			link.l1 = "よし、お前の実力を見せてもらうぜ！";
			link.l1.go = "Fugitive_fight_2";
		break;
		
		case "Fugitive_fight_2":// в таверне
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetImmortal(npchar, false);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
