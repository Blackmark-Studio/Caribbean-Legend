void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "「何でもない。」";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- работорговец -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//--> пинас
		case "TakeShoreCap":
    		dialog.text = "この野郎！驚いたか！";
    		link.l1 = "何だって？";
    		link.l1.go = "Node_1";
		break;
		
		case "Node_1":
			dialog.text = "ハハハ！ここには奴隷なんていねえぜ！お前は奴隷目当てで来たんだろう？";
			link.l1 = "くそっ。なんで交易用のピナスにあんなに兵隊がいるのかと思ったら……罠だったのか！";
			link.l1.go = "Node_2";
		break;
		
 		case "Node_2":
			dialog.text = "ああ、この野郎、罠だったんだよ。俺は商人じゃねえ、軍人だ！たとえお前が戦いに勝ったとしても、 裁きからは逃れられねえぞ！";
			link.l1 = "「それはなぜだ？今ここでお前を終わらせてやる。船も沈めてやるから、誰にも知られやしねえ。」";
			link.l1.go = "Node_3";
		break;
		
 		case "Node_3":
			dialog.text = "勘違いするな。お前があの銀行家とやっていたことはもうバレてるんだ。すぐに総督もお前の小細工を知ることになるし、 絞首台からは逃げられねえぞ。だが、ここで俺がとどめを刺してやるから、ありがたく思え！";
			link.l1 = "やってみろよ、この総督の犬め！";
			link.l1.go = "Node_4";
		break;
		
 		case "Node_4":
 		    pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //это состояние квеста для проверки у квестодателя
            AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
            pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
            Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Slave_arest":
			dialog.text = ""+GetFullName(pchar)+"「法の名のもとに、お前は逮捕する！武器を捨てて、俺たちと来い！」";
			link.l1 = "どうしたんだ、役人？降伏しろだと？何の理由でだ？";
			link.l1.go = "Slave_arest_1";
		break;
		
		case "Slave_arest_1":
			dialog.text = "とぼけるんじゃねえぞ、船長！てめえの汚い商売はもうバレてるんだ。お前がやった虐殺のことも、 そしてあの船のこともな\n "+NationNameGenitive(sti(npchar.nation))+" お前が沈めたからな、俺たちはお前を絞首刑にしてやるぞ！";
			link.l1 = "そう言うなら……くたばりやがれ！";
			link.l1.go = "Slave_arest_2";
		break;
		
		case "Slave_arest_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> крыса в доме
		case "Rat_bandos":
			dialog.text = "おい、ここで何してるんだ！？";
    		link.l1 = "どうしてそんなに無礼なんだ、旦那？あのネズミ野郎ゴンティエがどこかに隠れてやがるのか、ん？";
    		link.l1.go = "Node_rat_1";
		break;
			
		case "Node_rat_1":
			dialog.text = "いや、奴じゃねえ！出て行け！";
			link.l1 = "嘘をついているようだな。家の中を調べてみるぜ……";
			link.l1.go = "Node_rat_2";
		break;
		
 		case "Node_rat_2":
			dialog.text = "くたばれ！フランソワ！逃げろ！おい、野郎ども、助けてくれ！\n";
			link.l1 = "くそっ！";
			link.l1.go = "Node_rat_3";
		break;
		
		case "Node_rat_3":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Rat_lover":
			dialog.text = "ああ！お願いだ、俺を傷つけないでくれ！";
    		link.l1 = "なんだと…？フランソワ・ゴンティエはどこだ？答えろ、この汚えあばずれめ、 さもねえとお前も仲間たちと同じ目に遭わせてやるぞ！";
    		link.l1.go = "Rat_lover_1";
		break;
			
		case "Rat_lover_1":
			dialog.text = "いや、いや、全部話すよ！あいつは窓から飛び出して自分の船へ走っていったんだ。";
    		link.l1 = "何の船だ？あいつの船なんて港にはないのは知ってるんだ。俺に嘘をつくな、娘、さもないともっとひどい目に遭うぞ……";
    		link.l1.go = "Rat_lover_2";
		break;
			
		case "Rat_lover_2":
			dialog.text = "嘘じゃねえ、誓うぜ！あいつは小さな島に上陸して、ロングボートでここに来たって言ってたんだ…きっとまだそこにいるはずだ！頼む、俺を傷つけないでくれ！";
    		link.l1 = "よし、お前が本当のことを言ってるようだな。ここにいて大人しくしてろ。 今度はもう少し賢いやり方で友達を作るんだな。だがな、お前の目を見りゃ分かるぜ――頭がからっぽだってな。";
    		link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//отправляем в локацию
            pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//создание корвета
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;
			
		case "Rat_lover_3":
 		    LAi_SetPlayerType(pchar);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
            DialogExit();
		break;
		
		//--> беглые рабы
		case "Slave_woman":
			dialog.text = "助けてくれ！勘弁してくれ！降参だ！";
    		link.l1 = "おお、そうか？今すぐ貨物室へ行け！ふざけた真似をした奴は撃つからな！";
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
	//<--работорговец
			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- Генераторы -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--> Jason ------------------------ Сомнительное предложение -------------------------------------------	
		int iCGood;
		case "Contraoffer_patrol":
			chrDisableReloadToLocation = false;
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.PatrolSumm = sti(pchar.GenQuest.Contraoffer.Trader.Summ)/3;
			dialog.text = "ほうほう……これは何だ？うちの植民地では、許可のない者やその間での物品取引は禁止されてるって知らねえのか？";
			link.l1 = "そうなのか、役人？正直に言うと、それは初耳だぜ。この勅令は最近出されたものだろう、違うか？";
			link.l1.go = "Contraoffer_patrol_1";
			link.l2 = "なんだ、交易か "+GetGoodsNameAlt(iCGood)+"？俺には何も見えねえ "+GetGoodsNameAlt(iCGood)+" 辺りを見てみろ、役人。俺にはこのピカピカのコインしか見えねえ……あいつも同じだ。お前さんや兵隊たちも、俺たちのコインを見てみたらどうだ？";
			link.l2.go = "Contraoffer_patrol_pay1";
		break;
		
		case "Contraoffer_patrol_1":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > hrand(120))
			{
				dialog.text = "知らなかったのか？ふむ……嘘はついていないようだな。だが、それでもお前は法を破ったんだ。逮捕はしねえが、罰金は払ってもらうぜ。\nそれから積み荷については……取引のもう一人と話をさせてもらう。";
				link.l1 = "「で、その罰金はいくらなんだ？」";
				link.l1.go = "Contraoffer_patrol_pay2";
			}
			else
			{
				dialog.text = "とぼけるんじゃねえぞ、船長！それはとっくにみんな知ってたことだぜ、ついでに言っとくがな。 お前たち二人を密輸の罪で逮捕する。積み荷は没収だ。";
				link.l1 = "俺はカスエマートなんざ好きじゃねえ、役人さん。広い海の方が性に合ってる……今からそこへ出航するつもりだ。だが、どうやらお前の死体を乗り越えなきゃ無理みてえだな。";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "降参するしかない。しかし、本当に何も知らなかったんだ！";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_pay1":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > hrand(120))
			{
				dialog.text = "そうこなくちゃな……さあ、金貨を見せてもらおうか……確か、俺はかなり具体的な額を聞いた覚えがあるぜ―― "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+"。今や参加者が三人になったから、俺は手に入れたいんだ "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+"。これはお前からの分だ、そしてお前の友達も同じだ。";
				link.l1 = "かしこまりました、役人さん。これが俺のピカピカのコイン……いや、むしろあんたのコインだな――さっき浜辺でうっかり落としただけさ……そして、そこには何も\n "+GetGoodsNameAlt(iCGood)+" ほら、ははは、言っただろう。";
				link.l1.go = "Contraoffer_patrol_complete1";
				link.l2 = "おいおい！欲張りすぎだぜ、役人。母ちゃんに「欲張りはよくねえ」って教わらなかったのか？まあ、 剣で片付けた方が安上がりかもしれねえな。";
				link.l2.go = "Contraoffer_patrol_fight";
			}
			else
			{
				dialog.text = "冗談を言っているのか、船長？俺に賄賂を渡すつもりか？お前は逮捕されている！こいつを捕まえろ！";
				link.l1 = "「ふん、俺の金に興味がねえなら、俺の剣を見てみろよ！」";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "降参するしかない。しかし、本当に何も知らなかったんだ！";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_complete1":
			dialog.text = "ああ、どうやらお前の言う通りだな……ここには紳士数人と俺のピカピカのコイン以外、特に面白いものはねえ。行っていいぜ、船長。 お前の仲間とはこれから話をさせてもらう。";
			link.l1 = "じゃあな、士官。あいつを傷つけるなよ。";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_pay2":
			dialog.text = ""+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+"。俺の機嫌の良さに感謝しな。";
			link.l1 = "ありがとうございます、役人殿。まったく知りませんでした……さあ、罰金を支払う用意ができています。";
			link.l1.go = "Contraoffer_patrol_complete2";
			link.l2 = "あんたもそんなに正直じゃねえんだろうな、役人。罰金が高すぎるぜ。この植民地のために、 あんたを追い払ってやるとするか。";
			link.l2.go = "Contraoffer_patrol_fight";
		break;
		
		case "Contraoffer_patrol_complete2":
			dialog.text = "よろしい。もう行っていいぞ。今後このような事態を避けるためにも、現地の法律をよく学んでおくことを勧める。\nさあ、行け。我々はこの取引のもう一人の関係者と話をしなければならん。あいつはすべてを知っていたはずだ。";
			link.l1 = "そういうことなら、ごきげんよう、役人殿。";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_complete":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm));
			AddQuestRecord("Contraoffer", "6");
			CloseQuestHeader("Contraoffer");
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "Contraoffer_patrol_fight":
			AddQuestRecord("Contraoffer", "7");
			CloseQuestHeader("Contraoffer");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -5);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Contraoffer_patrol_jail":
			dialog.text = "司令官が貴様を相手にするぜ。ついて来い！";
			link.l1 = "...";
			link.l1.go = "Contraoffer_patrol_jail_exit";
		break;
		
		case "Contraoffer_patrol_jail_exit":
			GoToPrison(pchar.GenQuest.Contraoffer.Trader.City, sti(pchar.GenQuest.Contraoffer.Trader.Summ), 7);
			DialogExit();
			AddQuestRecord("Contraoffer", "8");
			CloseQuestHeader("Contraoffer");
			pchar.GenQuest.Contraoffer.Jail = "true";
		break;
	//<-- Сомнительное предложение	
		
	//Jason --> ----------------------------------- Неудачливый вор --------------------------------------------
		case "Device_poorman":
			dialog.text = "ごきげんよう。何かご用ですか？";
			link.l1 = "ああ、そうだぜ、相棒。お前が俺の仲間ってことでいいんだな。盗んだのはお前だろ "+pchar.GenQuest.Device.Shipyarder.Type+"  地元の造船所からか？すべてお前に繋がってるんだ、言い訳は通じねえぞ。";
			link.l1.go = "Device_poorman_1";
		break;
		
		case "Device_poorman_1":
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance3))
			{
				case 0://выбросил
				if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) != 1)
				{
					dialog.text = "お願いです、旦那様！はい、私はこの妙な物を造船所から盗みました。でも売ることができませんでした、 誰もこんな物はいらないと言うんです。だから処分しました。どうかお許しを、旦那、飢えのせいなんです、 私のせいじゃありません……そうでなければ決して盗みなんてしません！";
					link.l1 = "それは困ったな……それにお前もいらねえ。俺が探してるのはそいつだ "+pchar.GenQuest.Device.Shipyarder.Type+"。どこに捨てたのか教えてくれないか？";
					link.l1.go = "Device_poorman_0_1";
				}
				else //просто отдаст
				{
					dialog.text = "お願いです、旦那！はい、俺がこの妙な物を造船所から盗みました。でも売ろうとしたけど、 誰もこんな物欲しがらなかったんです。あなたに渡します。ほら、持っていってください、だから俺を傷つけないで、 兵士も呼ばないでください！";
					link.l1 = "よし、命は助けてやる、チンピラ。お前の皮なんぞいらねえ、欲しいのはその道具だ。さっさと渡して、とっとと消えな！ ";
					link.l1.go = "Device_poorman_0_2";
				}
				break;
				case 1://упирается, хитрый или храбрый
					dialog.text = "どういう意味だ？何が "+pchar.GenQuest.Device.Shipyarder.Type+"「？俺にはわからねえ！」";
					link.l1 = "「お前かお前の死体を調べたときに手に入れてやるぜ！今すぐ渡せ！」";
					link.l1.go = "Device_poorman_1_1";
				break;
				case 2://трусливый
					dialog.text = "ああ……これは何だ "+pchar.GenQuest.Device.Shipyarder.Type+"「？俺は……それで、何なんだ？」";
					link.l1 = "とぼけたり逃げたりしようなんて思うなよ、どうせ俺が捕まえるんだからな。さあ、ポケットの中を調べさせてもらうぜ…";
					link.l1.go = "Device_poorman_2_1";
				break;
			}
		break;
		
		case "Device_poorman_0_1"://идем на поиски
			dialog.text = "ちょうど城門のすぐ裏、ジャングルからも遠くない場所です。お願いします、旦那！どうしてもその品が必要なら、 ご自分で取りに行ってください。きっとまだそこにあるはずです。";
			link.l1 = "お前にそれを探させて持ってこさせるべきだが、そうするとお前を探す方が時間がかかりそうでな。 "+pchar.GenQuest.Device.Shipyarder.Type+"。俺が自分でやるぜ。しかし、もし嘘をついていたら必ずお前を見つけ出すからな！";
			link.l1.go = "exit";
			AddQuestRecord("Device", "3");
			string sCity = pchar.GenQuest.Device.Shipyarder.City + "_ExitTown";
			ref rItm = ItemsFromID("Tool");
			rItm.shown = true;
			rItm.startLocation = sCity;
			rItm.startLocator = "item" + (rand(14)+1);
			Log_TestInfo("Device is at the locator " + rItm.startLocator);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_0_2"://получили девайс
			dialog.text = "ほら、受け取れ。ありがとう、親切な旦那！";
			link.l1 = "ふん、これが俺の探してたものに違いねえな…はっ！もう行っていいぜ。さっさと動け。次はもっと気をつけるんだな。";
			link.l1.go = "exit";
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "4");
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_1":
			pchar.GenQuest.Device.Shipyarder.Poorsumm = 1000+hrand(1000);
			dialog.text = "聞けよ、お前、この楽器のことを言ってるのか？これは俺のもので、盗んだわけじゃねえ！それに、 タダで渡すつもりもねえんだ。欲しいなら、金を払え "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))+".";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))
			{
				link.l1 = "ふん……いいだろう。払ってやるよ。ほら、これが金だ、さあ楽器を渡せ！";
				link.l1.go = "Device_poorman_1_2";
			}
			link.l2 = "「ほう、本気か？この俺が貴様みたいな哀れな盗人を信用すると思ったのか？さあ、その」 "+pchar.GenQuest.Device.Shipyarder.Type+" 今すぐ俺に渡せ。さもないと衛兵を呼ぶぞ。そうすれば一緒に造船所へ行って、 この楽器が本当に誰のものか決めることになるからな。";
			link.l2.go = "Device_poorman_1_3";
			link.l3 = "お前、バカか？よく聞け、この野郎、選択肢は二つだ。どっちかだぜ、俺にその\n "+pchar.GenQuest.Device.Shipyarder.Type+" さもないと、お前を刺し殺してその道具を死体から奪うぞ！";
			link.l3.go = "Device_poorman_1_4";
		break;
		
		case "Device_poorman_1_2":
			dialog.text = "いい取引だな、船長！俺たち全員が分け前をもらえるってわけだな、へへ……受け取れよ。";
			link.l1 = "しゃべるな、盗人め！俺をだませたと思うなよ。俺はただ穏便に、面倒を少なく済ませたいだけだ。 どうせこのコインはお前の役には立たねえ。とっとと消えろ！";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Device.Shipyarder.Poorsumm));
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "5");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_3":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "やめてくれ！衛兵を呼ぶな！俺が……この忌々しい道具を渡すよ。ほら、持っていけ！";
				link.l1 = "今のほうがずっとマシだぜ！とっとと失せろ！さもねえと絞首台にぶら下がることになるぞ、時間の問題だ。";
				link.l1.go = "exit_device";
			}
			else//храбрый попался
			{
				dialog.text = "見張りなんていねえよ、船長。ここにいるのは俺とあんただけだ。あんたは口が過ぎるぜ……俺の刃で大人しくしてもらうぞ。";
				link.l1 = "俺様を脅すつもりか、このクズ野郎！？";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_1_4":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "ああ！助けてくれ！殺人者だ！";
				link.l1 = "そこまでだ、この野郎！";
			link.l1.go = "exit";
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				AddQuestRecord("Device", "7");
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else//храбрый попался
			{
				dialog.text = "さあ、どっちがどっちを刺すか見ものだな、船長！";
				link.l1 = "俺様を脅すつもりか、このクズ野郎！？";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_2_1":
			dialog.text = "捜しているのか？どうぞ、旦那！";
			link.l1 = "さあ聞け、今すぐ造船所から盗んだ物を大人しく渡すか、俺が司令官の部屋まで連れて行くかだ。 どうせお前はそれを俺に渡すことになるが、その前にかかとを焼きごてで焼かれることになるぜ。 もしかしたらその後で首を吊られるかもしれねえ。選ぶのはお前だ。";
			link.l1.go = "Device_poorman_2_2";
			link.l2 = "今すぐ盗んだ物を渡せ、この野郎、さもねえとここでぶっ殺してやるぞ！";
			link.l2.go = "Device_poorman_2_3";
		break;
		
		case "Device_poorman_2_2":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 2)//тут уж как повезёт
			{
				dialog.text = "まずは俺を捕まえないとな、司令官の執務室に連れて行きたいならな…";
				link.l1 = "そこまでだ、この野郎！";
				link.l1.go = "exit";
				AddQuestRecord("Device", "7");
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else
			{
				dialog.text = "いやだ、司令官の執務室には連れて行かないでくれ！自分で渡すよ！ほら、これだ、お前が探してたんだろう。 どうせ誰も買わねえしな…";
				link.l1 = "ええ、まあ砦まで連れて行ってやってもいいぜ……よし、道具を渡してさっさと行け！";
				link.l1.go = "exit_device";
			}
		break;
		
		case "Device_poorman_2_3"://напугали
			dialog.text = "痛い！やめてくれ、持ってる物は全部渡すから！ほら、持っていけ！";
			link.l1 = "そうこなくちゃな！さっさと失せろ、次にこの町で見かけたら司令官に突き出してやるぜ。じゃあな！";
			link.l1.go = "exit_device";
		break;
		
		case "exit_device":
			npchar.lifeday = 0;
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "6");
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_fight":
			chrDisableReloadToLocation = true;
			sld = characterFromId("Device_poorman");
			TakeNItems(sld, "Tool", 1);
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true; // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Device", "8");
			AddComplexSelfExpToScill(30, 30, 30, 50);
		break;
	//<-- Неудачливый вор
//-------------------------------------------почтовый генератор 2 уровня------------------------------------	
		case "PostGopHunters":
			dialog.text = "そこで止まれ、相棒！お前が持ってるものが必要なんだ。それを渡して、とっとと行きな。";
			link.l1 = "お前が話してるその物って何だ？";
			link.l1.go = "PostGopHunters_1";
			link.l2 = "最近のこの通りの連中は生意気すぎる……覚悟しろ、野郎ども！";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_1":
			dialog.text = "とぼけるんじゃねえ！荷物を渡せば命は助けてやる。さもねえと……死体から奪い取ることになるぜ！";
			link.l1 = "運はお前らの味方だ……持ってけ、この野郎ども、俺にはもう選択肢がねえ。";
			link.l1.go = "PostGopHunters_2";
			link.l2 = "やれるもんならやってみろ！";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_2":
			dialog.text = "舌の使い方に気をつけろよ、相棒……運を試さないのは賢い判断だぜ。どのみち結末は同じだったがな、ははっ！しばらくは生き延びられるだろう……じゃあな。";
			link.l1 = "...";
			link.l1.go = "exit_gophunter";
		break;
		
		case "PostProfHunters":
			dialog.text = "「待て、」 "+GetAddress_Form(NPChar)+"、そんなに急いで行くな。お前に頼みたい仕事があるんだ。";
			link.l1 = "何の用だ？俺はあんたのことを知らねえ。";
			link.l1.go = "PostProfHunters_1";
		break;
		
		case "PostProfHunters_1":
			dialog.text = "俺はお前のことを知ってるぜ、船長。さて、本題に入ろう。お前は今しがた受け取ったばかりだ "+pchar.questTemp.WPU.Current.Add+" で "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+"。言い逃れはするな、これが確かなことだと俺たちは知ってるんだ――何しろ、この書類を何日も探していたんだからな。";
			link.l1 = "なるほどな。で、どうするんだ？";
			link.l1.go = "PostProfHunters_2";
		break;
		
		case "PostProfHunters_2":
			dialog.text = "荷物を渡せば、俺たちの短い面会は終わる。英雄気取りはやめておけ、船長。俺たちはこの書類を手に入れるつもりだし、 必要なら街の衛兵とも戦う覚悟だ\nわかってるだろうが、もし小競り合いが始まれば最初に死ぬのはお前だ。だから書類を渡せ、 そうすりゃ友として別れてやる。";
			link.l1 = "運はお前らに味方してる……持ってけ、この野郎ども、他に選択肢はねえんだ。";
			link.l1.go = "PostProfHunters_3";
			link.l2 = "俺を脅かそうってのか？お前なんかより、小魚の方がよっぽど抵抗するぜ！消え失せろ。";
			link.l2.go = "PostProfHunters_4";
		break;
		
		case "PostProfHunters_3":
			dialog.text = "分別のある判断をしてくれて嬉しいよ、船長。お前はこの仕事を引き受けたことで大きな危険に身を晒したんだ。では、 失礼させてもらうぜ、構わないならな。";
			link.l1 = "...";
			link.l1.go = "exit_profhunter";
		break;
		
		case "PostProfHunters_4":
			dialog.text = "それはお前の決断だったんだ…";
			link.l1 = "...";
			link.l1.go = "PostHunters_fight";
			TraderHunterOnMap(false);//если деремся - запускаем ДУ вдогонку
		break;
		
		case "PostHunters_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_gophunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "11");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "exit_profhunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "12");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			pchar.questTemp.WPU.Postcureer.fail = "true";
			DialogExit();
		break;
		
		case "PostAgent":
			bDisableFastReload = true; 
			dialog.text = "「待て、」 "+GetAddress_Form(NPChar)+"、そんなに急ぐな。お前に頼みたい仕事があるんだ。";
			link.l1 = "何の用だ？早く言え、俺は急いでるんだ。";
			link.l1.go = "PostAgent_1";
		break;
		
		case "PostAgent_1":
			dialog.text = "お前が誰か知ってるぜ。それに、お前がたった今、あるものを受け取ったことも知ってるんだ。 "+pchar.questTemp.WPU.Current.Add+" "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+"。これらの書類こそ、私があなたと話したくてたまらなかった理由です。";
			link.l1 = "俺は知らねえ奴とこの件について話したくねえんだ。書類が欲しいのか？理由を言ってみろよ…";
			link.l1.go = "PostAgent_2";
		break;
		
		case "PostAgent_2":
			dialog.text = "もういいだろ、船長！俺が強盗に見えるか？俺は商人であり、～の利益を代表しているんだ "+NationNameGenitive(sti(pchar.questTemp.WPU.Postcureer.EnemyNation))+"。とても儲かる取引を持ちかけたいんだが、ここじゃ話せねえ。酒場の部屋に行って、この件について話そう。 そんなに時間は取らせねえよ。";
			link.l1 = "それはあまりにも怪しすぎる……俺はお前なんかと取引しないぞ、旦那！消え失せろ！";
			link.l1.go = "PostAgent_getout";
			link.l2 = "ふむ……お前が何を差し出せるか見せてもらおうじゃねえか。だが、俺に手を出すなんて考えるなよ――痛い目に遭うぜ。さあ、行くぞ、俺がお前についていく。";
			link.l2.go = "PostAgent_3";
		break;
		
		case "PostAgent_getout":
			dialog.text = "お前は頑固で愚かな男だな、船長！俺は楽に金を稼ぐチャンスをやったんだぜ。それなのに……後悔することになるぞ。";
			link.l1 = "失せろ！";
			link.l1.go = "PostAgent_getout_exit";
		break;
	
		case "PostAgent_3":
			dialog.text = "素晴らしい！ついて来い。";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			NextDiag.TempNode = "PostAgent_inTavern";
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", pchar.questTemp.WPU.Postcureer.StartCity +"_tavern_upstairs", "goto", "goto1", "PostAgent_inTavern_Room", -1);
		break;
		
		case "PostAgent_getout_exit":
			bDisableFastReload = false; 
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10);
			pchar.questTemp.WPU.Postcureer.AgentIslandID = GetCharacterCurrentIslandId(pchar);
			pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
			pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.AgentIslandID;
			pchar.quest.Postcureer_Hunter.function = "PostcureerAgent_ShipAttack";
			AddQuestRecord("Postcureer", "13");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "PostAgent_inTavern":
			dialog.text = "これで自由に話せるな。";
			link.l1 = "「それで、あんたの提案は何だ？」";
			link.l1.go = "PostAgent_inTavern_1";
		break;
		
		case "PostAgent_inTavern_1":
			dialog.text = "俺が言った通り、これは港の役所で受け取った書類のことだ。俺が必要なのはその写しだけ、それだけでいい\n原本はお前が持っていればいいから、仕事の報酬もちゃんともらえる。何があったか誰にもバレやしねえし、 しかも俺がたっぷり払ってやるぜ。";
			link.l1 = "失礼します…しかし、その包みは封印されています。封を破らない限り、複製はできませんよ！";
			link.l1.go = "PostAgent_inTavern_2";
		break;
		
		case "PostAgent_inTavern_2":
			dialog.text = "この質問が来ると思っていたよ。封印を破らなきゃならないが、心配はいらない、ちゃんと元に戻せるからな。もちろん、 複製の印章と封蝋も用意してある。誰にも包みが開けられたことは気づかれやしないさ。";
			link.l1 = "港の管理について、何かありがちな誤解を持っているのか "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"?";
			link.l1.go = "PostAgent_inTavern_3";
		break;
		
		case "PostAgent_inTavern_3":
			pchar.questTemp.WPU.Postcureer.AgentMoney = sti(pchar.rank)*3500;
			dialog.text = "なぜそんなことを聞くんだ、船長？ああ、持ってるぜ。本気で俺がふざけてると思ってるのか？ 俺はお前に提供してるんだぞ\n "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+" この書類を見る機会をくれてありがとう。さて、そろそろその包みを渡してくれるかい？頼むよ。";
			link.l1 = "持っていけ、だが必ず返してくれよ、しかも封をしたままでな！";
			link.l1.go = "PostAgent_inTavern_4";
			link.l2 = "そうだな、俺はやらねえよ。気に入らねえんだ。";
			link.l2.go = "PostAgent_inTavern_getout";
		break;
		
		case "PostAgent_inTavern_4":
			dialog.text = "心配するな。俺はプロだぜ。座ってゆっくり休んでくれ。だいたい一時間くらいかかるぞ。";
			link.l1 = "「いいだろう。」";
			link.l1.go = "PostAgent_inTavern_5";
		break;
		
		case "PostAgent_inTavern_5":
			NextDiag.currentnode = "PostAgent_inTavern_6";
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			pchar.questTemp.WPU.Postcureer.AgentChance = hrand(4);//шанс, что раскроют обман - 20%
			DialogExit();
			AddDialogExitQuest("PostAgent_inTavern_Room_end");
		break;
		
		case "PostAgent_inTavern_getout":
			dialog.text = "ふむ……こんな展開になるとは思わなかったぜ。お前は頑固すぎるな、船長。だからここでお前をぶっ殺して、 その荷物はタダでいただくぜ。祈るんだな、俺の剣の腕前は、ありきたりな決まり文句と同じくらい冴えてるからよ。";
			link.l1 = "祈るべきなのはお前だ、間者め！";
			link.l1.go = "PostAgent_inTavern_fight";
		break;
		
		case "PostAgent_inTavern_6":
			dialog.text = "終わった。言った通り、最も正確にやったぜ。約束通り荷物を受け取れ\n "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+"。さて、俺は行かなくちゃならねえ。幸運を祈るぜ、船長。取引できて嬉しかったぜ。";
			link.l1 = "さらば……";
			link.l1.go = "PostAgent_inTavern_7";
		break;
		
		case "PostAgent_inTavern_7":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.AgentMoney));
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			sld = characterFromID("PostAgent");        
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 2);
			AddQuestRecord("Postcureer", "15");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)));
		break;
		
		case "PostAgent_inTavern_fight":
			bDisableFastReload = false;
			sld = characterFromID("PostAgent"); 
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Postcureer", "16");
		break;
	//<-- почтовый генератор 2 уровня
		
	// --> --------------------------------- эскорт 2 уровень --------------------------------------------------
		case "DisasterCap":
			dialog.text = "ごきげんよう！ああ、お会いできて本当に嬉しいですわ！";
			link.l1 = "ごきげんよう。ふむ、教えてくれ、お前がその指揮を執っているのではないか "+pchar.questTemp.WPU.Escort.ShipName+"?";
			link.l1.go = "DisasterCap_1";
		break;
		
		case "DisasterCap_1":
			dialog.text = "「おお！それで、どうやってそのことを知ったんだ」 "+pchar.questTemp.WPU.Escort.ShipName+"「？ああ、俺が彼女の船長だ。いや、正確には……だったんだ……船はここからそう遠くない場所で沈んじまった。」";
			link.l1 = "ああ、それなら見つけたぞ……自己紹介させてもらおう―― "+GetFullName(pchar)+"。私は港長の依頼でここに来た "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"。彼はあなたの隊商のトラブルについて簡単に話してくれて、あなたの船を探しに行くよう私に言いました。";
			link.l1.go = "DisasterCap_2";
		break;
		
		case "DisasterCap_2":
			dialog.text = "そうか、お前が救助隊の船長か？";
			link.l1 = "そんなところだ。俺の任務はお前の船、もしくは沈没したか航行不能になった証拠を見つけることだったんだ。\n残念ながら船は見つからなかったが、船長は生きていた。それは間違いなく良いことだな……";
			link.l1.go = "DisasterCap_3";
		break;
		
		case "DisasterCap_3":
			dialog.text = "あっ、すまない、自己紹介を忘れていた。俺は "+GetFullName(npchar)+"。もうどうして俺たちがここにいるのか知ってるか？嵐で船が制御不能になったんだ\n数日後、この湾からそう遠くない岩礁にぶつかって、突風が数分で船をバラバラにしちまった。 生き残ったのは俺の部下のうち数十人だけだ。残りは海の底に沈んでる。俺たちは毎日、 やつらの魂のために祈ってるんだ……";
			link.l1 = "お悔やみ申し上げます、船長 "+GetFullName(npchar)+"。申し訳ねえ。";
			link.l1.go = "DisasterCap_4";
		break;
		
		case "DisasterCap_4":
			dialog.text = "ありがとう……生存者たちは岸辺にキャンプを張り、救援を待っているんだ。ちょうどいい時に来てくれたな、船長！ この地の好戦的なインディアンたちも俺たちの存在に気づいている。もし奴らが攻めてきたら、 何百人も相手にはとても太刀打ちできねえよ。\nそれに、この辺りをうろついている海賊船もいる。どうやら俺たちを探しているようだ。その海賊に会ったかい、船長？";
			link.l1 = "いいや、まだだ。";
			link.l1.go = "DisasterCap_5";
		break;
		
		case "DisasterCap_5":
			dialog.text = "それは主のお導きだ。あいつはあの忌々しい嵐の前に俺たちを襲った連中の一人だ。 ハイエナみてえに傷ついた獲物を仕留める気満々で、ここ、この島にやって来たんだ。";
			link.l1 = "なるほど。さて、これからどうするか決める時だな。";
			link.l1.go = "DisasterCap_6";
		break;
		
		case "DisasterCap_6":
			dialog.text = "何を決めるんだ、船長？俺たちを乗せてくれよ、そしてこんな呪われた場所から早く逃げようぜ。";
			link.l1 = "もちろんだ。船を救うことはできなかったが、せめて乗組員だけは助けるぜ。野営を片付けてくれ、 俺がここにロングボートを送るよう命じる。\nようこそ、俺の船へ！";
			link.l1.go = "DisasterCap_7";
		break;
		
		case "DisasterCap_7":
			PlaySound("people fight\rifle_fire1.wav");
			PlaySound("people fight\player_man_shoot_01.wav");
			dialog.text = "ありがとうございます、船長！すぐに終わります。待って……なんだと？くそっ！あの赤い肌の悪魔どもがまた来やがった！警報だ！武器を取れ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_IndianAttack");
		break;
		
		case "DisasterCap_8":
			dialog.text = "ふう、なんとか辿り着いたな……見ただろう、船長、この入り江はまさに地獄だって言ったじゃねえか。もう三度目のインディアンの襲撃だぜ！こんな所、 早く出なきゃならねえ。次の襲撃には耐えられねえぞ。";
			link.l1 = "ああ、その通りだ。生きている者を全員集めて、俺の船に乗せろ！すぐにロングボートを出すよう命じるぞ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_onBoard");
			AddQuestRecord("Escort", "38");
			AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore));
		break;
	// <-- эскорт 2 уровень
		
	//Jason --> -------------------------- Заносчивый аристократ ------------------------------------------------
		case "Badboy":
			dialog.text = "ひっく…何の用だ？消えろ、あんたと話す気はねえんだよ。";
			link.l1 = "お前は "+pchar.GenQuest.Badboy.Brothel.Name+"?";
			link.l1.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "ああ、そうだ。で、用件は何だ？";
			link.l1 = "簡単な話だ。この町にはお前の悪だくみにうんざりしてる奴がいるんだよ。その人はもう我慢の限界らしい。 今お前の顔を見て納得したぜ。二度とこの町の売春宿に顔を出すんじゃねえぞ、さもないと痛い目に遭うからな。 わかったか？";
			link.l1.go = "Badboy_2";
		break;
		
		case "Badboy_2":
			switch (sti(pchar.GenQuest.Badboy.Brothel.Type))
			{
				case 0://или напугается, или будет быковать - от авторитета
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 30)
					{
						dialog.text = "うおっ！てめえ…俺様を脅すつもりか、このクズ野郎！俺の刃に串刺しにして、丸焼きにしてやるぜ！";
						link.l1 = "覚悟しろ、この野郎！";
						link.l1.go = "Badboy_fight_1";
						NextDiag.currentnode = "Badboy_after_fight";
					}
					else
					{
						dialog.text = "何だと？どんなごまかしだ？ごまかしなんてしてねえよ。俺は酔っぱらって、何度か娼館で羽目を外しただけだ。 完璧な奴なんていねえだろ……わかった、わかった、わかったよ……もう二度とあそこは利用しねえ。これで満足か？俺の言葉だ。";
						link.l1 = "名誉の誓いがあなたにとって意味を持つこと、そしてそれを破った場合の結果を理解していることを願う。\nそのことを忘れないように。では、これで失礼する。";
						link.l1.go = "exit";
						pchar.GenQuest.Badboy.Complete = "true";
						LAi_CharacterDisableDialog(npchar);
						npchar.lifeday = 0;
					}
				break;
				case 1://дуэль за городом
					dialog.text = "なんて無礼な男なの、旦那！日が沈む前にその言葉を後悔させてやるわ。決闘を申し込む！\n人目のない静かな場所で戦った方がいいでしょうね。ジャングルで十分よ、二時間後にそこで会いなさい！";
					link.l1 = "いい考えだな！少なくとも、お前の死体を隠すのには困らねえだろう。";
					link.l1.go = "Badboy_duel";
					NextDiag.currentnode = "Badboy_duel_1";
					break;
				case 2://призовет на помощь дружков
					dialog.text = "何だと？どんなごまかしだ？ごまかしなんてしてねえよ。俺は酔っぱらって、娼館で何度か羽目を外しただけだ。 誰だって完璧じゃねえ…わかった、わかった、わかったよ…もう二度とあいつらの世話にはならねえ。これで満足か？約束するぜ。";
					link.l1 = "名誉の誓いがあんたにとって何か意味を持つことを願うぜ、もしそれを破ったらどうなるかも分かってるだろうな。 それを忘れんな。じゃあな。";
					link.l1.go = "exit_continue";
					pchar.GenQuest.Badboy.Continue = "true";
					NextDiag.currentnode = "Badboy_friends";
				break;
			}
		break;
		
		case "Badboy_fight_1":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("Badboy");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(npchar, 10.0, true, "Badboy_capture");
			DialogExit();
		break;
		
		case "Badboy_after_fight":
			dialog.text = "待ってくれ！やめてくれ！降参だ！命だけは助けてくれ！";
			link.l1 = "「それで今はそんな口をきいてるのか！」";
			link.l1.go = "Badboy_after_fight_1";
		break;
		
		case "Badboy_after_fight_1":
			dialog.text = "頼む、お願いだ、助けてくれ！言うことは何でもする！あの売春宿には二度と近づかない！";
			link.l1 = "こんなポーズはお前みたいなクズにしか似合わねえ。これが一生の教訓になればいいがな。\nこの町ではちゃんと大人しくしてろよ。";
			link.l1.go = "Badboy_exit";
			link.l2 = "もちろん、そうはいかねえ。お前のごまかしはここで終わりだ。";
			link.l2.go = "Badboy_killed";
			pchar.GenQuest.Badboy.Complete = "true";
		break;
		
		case "Badboy_exit":
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;
		
		case "Badboy_killed":
		DialogExit();
		LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
		LAi_ActorAnimation(pchar, "shot", "Badboy_killed_end", 2.2);
		break;
		
		case "Badboy_duel":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", true);//офицеров не пускать
			locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = true; //энкаутеры закроем
			pchar.quest.BadboyDuelTimer.win_condition.l1 = "Timer";
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.BadboyDuelTimer.function = "Badboy_duelstart";
			sld = characterFromId("Badboy");
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			TakeNItems(sld, "jewelry5", rand(10)); 
			TakeNItems(sld, "jewelry3", rand(10)); 
			TakeNItems(sld, "jewelry1", rand(10)); 
			sld.money = 24560;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			LAi_RemoveLoginTime(sld); //удалить время логина
			SetFunctionTimerCondition("Badboy_duelOver", 0, 0, 1, false);
			DialogExit();
		break;
		
		case "Badboy_duel_1":
			dialog.text = "地獄へ行く時間だぜ、この野郎！せいぜい自分のために祈るんだな、だが急げよ、俺は一日中付き合ってられねえんだ……";
			link.l1 = "しゃべってねえで、さっさと戦え、このクズ野郎！";
			link.l1.go = "Badboy_duel_2";
		break;
		
		case "Badboy_duel_2":
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Badboy_die");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_continue":
			sld = characterFromID("Badboy");        
			LAi_RemoveLoginTime(sld); // patch-6
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;		
		
		case "Badboy_friends":
			dialog.text = "あいつだ、あの生意気な野郎！\nこの町の主が誰か、思い知らせてやるぞ、野郎ども！";
			link.l1 = "ああ、お前は本当にろくでなしだな！だが警告はしたぜ。お前もその手下どもも、すぐに地獄行きだ！";
			link.l1.go = "Badboy_friends_fight";
		break;
		
		case "Badboy_friends_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(pchar, "GenQuest.Badboy");
		break;
	//Jason <-- Заносчивый аристократ
		
	//Jason --> ------------------------------- Место под солнцем ----------------------------------------------
		case "Sunplace_Store":
			pchar.quest.SunplaceContinue_Over.over = "yes";
			dialog.text = "挨拶だ。何の用だ？";
			link.l1 = "お前じゃねえか "+pchar.GenQuest.Sunplace.Trader.Enemyname+"？信じられねえだろ、はは。俺はお前の首が欲しいんだ。";
			link.l1.go = "Sunplace_Store_1";
			link.l2 = "ふむ……いや……なんでもない。どうやら俺の勘違いだったようだ。邪魔してすまなかったな。";
			link.l2.go = "Sunplace_Store_exit";
		break;
		
		case "Sunplace_Store_1":
			dialog.text = "なんて馬鹿げた冗談だ、旦那！説明しろ、さもないと俺は……";
			link.l1 = "「で、これからどうするつもりだ、みじめなニシン野郎？お前は善人にひどい仕打ちをして、あいつは本気で怒ってるぜ。 だから今すぐ祈れ、さっさとやれよ、俺は急いでるんだ。」";
			link.l1.go = "Sunplace_Store_3";
		break;
		
		case "Sunplace_Store_3":
			dialog.text = "な、なにをしているんだ、旦那！助けて！誰か助けてくれ！殺人者だ！";
			link.l1 = "俺はてっきり、最後の瞬間くらいは祈るのかと思ってたぜ。そうすりゃ、せめて天国に行ける望みもあったかもな……";
			link.l1.go = "Sunplace_Store_fight";
		break;
		
		case "Sunplace_Store_exit":
			sld = CharacterFromID("SunplaceTrader");
			sld.lifeday = 0;
			AddQuestRecord("Sunplace", "9");
			CloseQuestHeader("Sunplace");
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			NextDiag.currentnode = "Sunplace_Store_repeat";
		break;
		
		case "Sunplace_Store_repeat":
			dialog.text = "またお前か？何が欲しいのか、どうして言わねえんだ？";
			link.l1 = "「なんでもない。」";
			link.l1.go = "exit";
		break;
		
		case "Sunplace_Store_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("SunplaceTrader");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			sld = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
			LAi_group_Attack(sld, Pchar);
			pchar.quest.Kill_SunplaceTrader.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Kill_SunplaceTrader.win_condition.l1.location = pchar.location;
			pchar.quest.Kill_SunplaceTrader.function = "Kill_SunplaceTrader";
		break;
	// <-- место под солнцем
		
	//------------------------------------- киллеры Лиги-------------------------------------------------------
		case "LigaHunters":
			dialog.text = "";
			link.l1 = "あぁ！？なんだと？てめえ、ここで何してやがるんだ、この野郎！誰が中に入れたんだ！？";
			link.l1.go = "LigaHunters_1";
		break;
		
		case "LigaHunters_1":
			dialog.text = "「同盟はお前の命が必要なんだ、船長……」";
			link.l1 = "「なんだと？くそっ！」";
			link.l1.go = "LigaHunters_2";
		break;
		
		case "LigaHunters_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("LigaHunter_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "LigaHunters_Dead");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	// <-- киллеры Лиги
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
			dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ、俺はこの町の住人だ。剣を収めてくれ。","聞いてくれ、俺はこの町の住人だ。だから剣を納めてくれ。");
			link.l1 = LinkRandPhrase("「いいだろう。」","「いいだろう。」","ああ……");
			link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"「気をつけろ」 "+GetSexPhrase("相棒","娘")+"、武器を持って走っているときは緊張するんだ…","俺は、そういうのがあるのは気に入らねえ "+GetSexPhrase("「～という男たち」","「～という人々」")+" 俺の前を武器を構えて歩いている。怖いんだよ……");
				link.l1 = LinkRandPhrase("わかった。","大丈夫だ。","心配するな……");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
			if (npchar.id == "Device_poorman") NextDiag.TempNode = "Device_poorman";
		break;
	}
}
