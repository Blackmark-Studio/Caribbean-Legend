void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, sld, rShip, rItm, rItem;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr, sGun, sBullet, attrL;
	aref rType;
    
	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индекс в конце
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
	
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	if (findsubstr(sAttr, "tonzag_jail_" , 0) != -1) {
	 	pchar.questTemp.Tonzag.JailDialog.ID = strcut(sAttr, strlen("tonzag_jail_"), strlen(sAttr) - 1);
		DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog." + pchar.questTemp.Tonzag.JailDialog.ID);
		AddDialogExitQuestFunction("Tonzag_InJailDialog");
 	    Dialog.CurrentNode = "exit";
 	}
 	// генератор ИДХ по кейсу <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "もしこの行を読んでいるなら、それはコードのバグだ";
			Link.l1 = "Exit";
			Link.l1.go = "exit";
			
			//--> Вступительный туториал на палубе корабля за Шарля
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1"))
			{
				dialog.text = "最高だ、くそっ！本物の海戦だぜ！\nここからじゃ戦いが見られないのが残念だが…まあいい。航海のことは十分学んだから、どうなるか想像はつくさ。\nたぶん海賊は五人くらい…でかい船が一隻、中型が二、三隻、あとは小物ってとこだろう。うちのピナスにはちょうどいい相手だ。いい話になるぜ――ルルもきっと気に入るさ！";
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1");
				pchar.wind.speed = 18.0;
				fWeatherSpeed = stf(18.0);
				//AddDialogExitQuestFunction("SharlieTutorial_StartShip");
				AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_3");
			}
			//<-- Вступительный туториал на палубе корабля за Шарля

			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC_FindIsland"))
    		{
    		    dialog.text = "さて、この場所を地図で見つけたな。印をつけて、さあ探索に出発だぜ。";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("SearchingForIslandOnMap");
    		}
			if (CheckAttribute(pchar, "questTemp.HWICMC") && pchar.questTemp.HWICMC == "Fleetwood")
    		{
    		    dialog.text = "よし、着いたな。俺の船を南の湾に隠してから、ジャングルを歩いて戻り、 フリートウッドにとびきりのサプライズを用意してやるか。";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1.location = pchar.location;
				pchar.quest.Fleetwood_repeatShore.function = "Fleetwood_repeatShore";
    		}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabinWoman" && PChar.location == Get_My_Cabin()) 
	        {
				dialog.text = "ふむ…この悪党を信用するのは危険だが、話は本物らしい。今回は嘘をついていないかもしれん。だが、とにかく、 奴の妻と話すべきだな…ボースン！あの捕らえた女を連れてこい！";
    			link.l1 = "あいよ、船長！";
	    		Link.l1.go = "exit";
				chr = characterFromId("FalseTraceWife");
				chr.dialog.currentnode = "FalseTrace_wife_6";
				pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
				AddDialogExitQuest("SetFalseTraceCharToCabin");
	    	}
			//<-- Ложный след
			
			//--> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "DigGems")
    		{
    		    dialog.text = "ここがその場所のようだな。周囲で唯一、樹液のない木だ。ここを掘るべきだな。";
    			link.l1 = "（宝を掘り出す）";
    			link.l1.go = "exit";
				AddDialogExitQuest("FindPortugalGems");
    		}
			//<-- Португалец
			// Сага
			if (CheckAttribute(pchar, "questTemp.Saga.JessSoul"))
    		{
    		    dialog.text = "何が起きてるんだ？ここはどこだ！？一体どんな場所なんだ？";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("Saga_JessikaSoul_2");
    		}
            //--> приколы со стуком в дверь Диффиндура, LSC
			if (CheckAttribute(pchar, "questTemp.LSC.DiffIndoor"))
    		{
    		    dialog.text = "これは船の内部区画へ通じる扉だ。鍵がかかっている……ホークがここにいるはずだ。オーレが何て言ってたっけ？秘密のノックを使うべきだな。";
    			link.l1 = "二回ノックしろ。";
    			link.l1.go = "knock_2";
				link.l2 = "三回ノックしろ。";
    			link.l2.go = "knock_3";
				link.l3 = "「一度ノックして、間を置いて、三回ノックしろ。」";
    			link.l3.go = "knock_1_3";
				link.l4 = "「二回ノックして、間を置いて、また二回ノックしろ。」";
    			link.l4.go = "knock_2_2";
				link.l5 = "「三回ノックして、間をおいて、一回ノックしろ。」";
    			link.l5.go = "knock_3_1";
    		}
			//<-- приколы со стуком в дверь Диффиндура, LSC
			
			//--> напялили водолазный скафандр, для перехода в режим шага
			if (pchar.model == "protocusto")
    		{
    		    dialog.text = "うわぁ、びっくりだぜ！あれは本当に重いな！";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			//<-- водолазный скафандр
			// отказ от телепортации
			if (IsCharacterInLocator(pchar, "item", "dolly1") || IsCharacterInLocator(pchar, "item", "dolly2") || IsCharacterInLocator(pchar, "item", "dolly3"))
    		{
    		    dialog.text = "いや、いや、いや！絶対に無理だ！三回でもう十分すぎるぜ！";
    			link.l1 = "...";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "roof")
    		{
    		    dialog.text = "終わった。ルヴァスールは死んだ。思ったよりもずっと簡単だった……だが、何かがおかしい。ティボーはマルテンに一言も話さなかった！つまり、ロベールが俺を裏切ったか、 あるいは事故が起きたかだ\nだが、あの野郎ティボーはどこへ逃げた？きっとカトリーヌを追っているに違いねえ。 奴の鼻先からあの娘を生きたまま奪いたいなら、俺が早く動かねえとな……";
    			link.l1 = "";
    			link.l1.go = "terrapin";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
    		{
    		    dialog.text = "財宝、財宝……インディアンの都市……こんな偶然は信じられない……きっと俺の兄貴がディチョーソのフリゲート艦消失に関わっていたに違いねえ。 おそらく兄貴はディチョーソが二度と口を開けないようにしたんだろう\nあるいは一緒に動いていたのかもな。スペイン人がディチョーソがこの辺りにいると考えた理由もあるはずだ。 全く筋が通らねえ。でも、ミシェルがド・ポワンシーに届けようとしていたインディアンの金も、 ミゲル・ディチョーソの金も、同じ金だと俺は確信してる。囚人の話は、将校が俺に話した兄貴の冒険譚と一致してる\nおかしいな、ミシェルもミゲルも金を届けられなかった！じゃあ今、その財宝はどこにあるんだ？多分、 それが兄貴があんなに急いでる理由なんだろう\nつまり、金を見つければ一石二鳥ってわけだ。もう一度兄貴の生意気な目を見てやれるし……そう、金はいつだっていいもんだ。でも、どうやって見つけりゃいいんだ？ そろそろスペイン人に本気で近づく時が来たようだ\nドン・ラモナ・メンドーサは論外だ。あいつとやり合うのは無理だろうが、聖父ヴィンチェント――男爵の天敵……こいつなら使える。ああいう連中は抜け目がないが、金と汚い手段が大好きだ\nディチョーソ、ディチョーソ……この姓、前にも聞いたことがあるような……いや、ないか？まあ、どうでもいい。くそったれだ。将校のところへ行ってスペイン人の囚人を引き取ろう。 それからいつでもサンティアゴへ向かえるな。";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore")
    		{
    		    dialog.text = "バニラはブリガンティンに積み込まれ、あの船の帆はとっくに地平線の彼方へ消えちまった――それなのに、この忌々しいガレオンは外洋に出ずに港へ戻ってきやがった。俺の船で港に姿を見せるわけにはいかねえ――やつらには俺がグアドループを離れたと思わせておくのが一番だ……。\nジャングルを抜けて町まで歩き、愛しのマルシェについて何か情報を探すとするか……";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "galeon")
    		{
    		    dialog.text = "上甲板には見張りが数人いるだけで、みんなかなり眠そうだ。俺が静かに背後から近づいて、 メリケンサックで後頭部を殴れば、一人ずつ片付けられそうだな…… ";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth_room"))
    		{
    		    dialog.text = "鍵のかかっていない空き家、二階には居心地の良い部屋があり、カールフーンの部屋の近く……これはまさに乙女の願いが叶ったようなものね……もし窓から出て屋根のひさしを伝って歩けば、アーチーの部屋に簡単に忍び込めるわ。でも、 見つからないように夜にやらなきゃ……";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("GuardOT_FindWayToRoom");
    		}
			// Поиски Ксочитэма
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_pearl")
    		{
    		    dialog.text = "ついに！「啓示」に示された場所を見つけたぞ。それはインディアンの偶像だ。近づくと「道しるべの矢印」 が揺れなくなり、一方向を指し示す。まあ、インディアンの魔術とインディアンの偶像なら当然だな。さて、 「道しるべの矢印」が示した場所を地図に記してから、ドミニカへ向かうとしよう。";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFirstWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_dominica")
    		{
    		    dialog.text = "ついに！「啓示」で示された場所を見つけたぞ。それはインディアンの偶像だ。近づくと「道しるべの矢印」 が揺れなくなり、一方向を指し示す。なるほどな、インディアンの魔法とインディアンの偶像か。さて、 「道しるべの矢印」が示した場所を地図に記してから、メインへ向かうとしよう。";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindSecondWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "full")
    		{
    		    dialog.text = "両方の現象が見つかった！\nこれで二つ目の方角を地図に記さねばならない。\nこの二つの方角の交点がクソチェアテム島の位置を示してくれるはずだ。";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFullWay");
    		}
			// рассуждения по Тайясалю
			if (CheckAttribute(pchar, "questTemp.Tieyasal_CabinTalk"))
    		{
				if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
				{
					dialog.text = "アロンソ・デ・マルドナードは、ユカタンの北から始まるタイアサルへの道があると言っていた。つまり、 この地域のセルバの奥深くへ行かなければならないということだ。しかし、ジーノはテレポート像はもともと人々 をタイアサルへ移動させるためのものだったと言っていた\nそれに、ミスキートのシャーマン、スネークアイは、偶像は「食われた者」 をその場所へ送るために作られたと教えてくれた。だが、なぜそのポータルは壊れているんだ？ふむ。それに、 「二つの顕現」の地図には、ミスキート像の近くに奇妙な円が描かれている\n一体どういう意味だ？また別の魔法の場所か？それとも、あの像には何か追加の機能があるということなのか？ シャーマンに会いに行くべきだろうか。それとも、本島の北西に行って、現地の入り江の一つで道を探してみるか。";
					link.l1 = "";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "アロンソ・デ・マルドナードは、ユカタン半島北部からタイアサルへ行く別の道があると言っていた。\nつまり、俺はジャングルの奥へ続く道を探さなきゃならないってことだ。\n必要な道は、おそらく北西部の本土にある入り江の一つから始まっているだろう。";
					link.l1 = "";
					link.l1.go = "exit";
				}
				AddDialogExitQuest("Tieyasal_AfterCabinTalk");
    		}
			// решаем - титры или фриплей 010912
			if (CheckAttribute(pchar, "questTemp.Tieyasal_final"))
    		{
				dialog.text = "終わった。長い旅路の終わりだ。兄を牢獄から救い出すことが、 まさか彼との最後の戦いに自分を備えさせることになるとは思いもしなかった！俺は危うくこの世界を滅ぼしかけたんだ。 神よ、すべてが終わった、感謝する\nもうカリブに俺を引き留めるものは何もない。故郷フランスへ帰る時だ。だが…本当にそれを望んでいるのか？";
				link.l1 = "ああ、ヨーロッパに戻るところだ。";
				link.l1.go = "final_1";
				link.l2 = "いや、俺はここカリブ海に残るつもりだ。";
				link.l2.go = "final_2";
    		}
			// фэйловый финал 040912
			if (CheckAttribute(pchar, "questTemp.Europe"))
    		{
				PlaySound("Voice\English\military02.wav");
				dialog.text = "大佐の話を聞いたか？反乱者どもがそこに隠れているぞ！全部調べて、 家の中をひっくり返して見つけた奴は全員捕まえろ！さあ、やれ！";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuest("Europe_SharlieFinal_2");
    		}
			// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
			/*if (CheckAttribute(pchar, "questTemp.FMQG.Info") && pchar.location == "Bridgetown_Plantation")
    		{
    		    dialog.text = "ここは待ち伏せには最適な場所だ。ここでピネットが来るのを待つべきだ。";
    			link.l1 = "...";
    			link.l1.go = "exit";
				AddDialogExitQuest("FMQG_KidnappingInfo");
    		}*/
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN.Choose") && pchar.location == "shore40")
    		{
				dialog.text = "ふむ。この話、どうも腑に落ちねえな。セント・ジョーンズのラガー船なんて、最初から存在しなかったんじゃねえか。 あの副官は俺を軍の作戦に巻き込もうとしてやがる。そんなもん、俺には必要ねえ……俺はオランダと戦争してるわけじゃねえし……どうする？全部が地獄に落ちる前にここから足を洗って、あいつらを悪魔にくれてやるか――それとも残るか？";
				link.l1 = "出て行け。";
				link.l1.go = "FMQN_1";
				link.l2 = "「待て。」";
				link.l2.go = "FMQN_2";
    		}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Chest") && pchar.location == "shore37")
    		{
    		    dialog.text = "さて、宝箱の準備はできた。必要な材料を全部自分で探すこともできるが、やっぱりファディを訪ねてみたい。 あいつなら何でも手に入れられる男って感じがするからな。";
    			link.l1 = "＊弾薬の調達を終えるには「独り言」オプションを使え＊";
    			link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_PlantChestReadyExit");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Boats") && pchar.location == "Maracaibo_river")
    		{
    		    dialog.text = "つまり、ロングボートを六隻作る必要がある。そのためには大工と板材二十枚、それに革十束が必要だ。";
    			link.l1 = "＊「独り言」オプションを使ってロングボートの建造を始めよう＊";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Boats");
				AddQuestRecord("Roger_5", "11");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder") && pchar.location == "shore10")
    		{
    		    dialog.text = "だから、この古い木の山をまとめて吹き飛ばすつもりだ。念のために必要なのは火薬300樽だけだぜ。";
    			link.l1 = "＊「独り言」オプションを使って火薬の設置を指示する＊";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder");
				pchar.questTemp.Mtraxx.Retribution = "powder";
				chrDisableReloadToLocation = false;
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed") && pchar.location == "Judgement_dungeon_01")
    		{
    		    dialog.text = RandSwear()+" 出口が塞がれている！どうやら重いもので扉をふさいだようだ！ "+RandSwear()+"\n静かに……なんだこれは？";
    			link.l1 = "";
    			link.l1.go = "mtraxx_dungeon";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead") && pchar.location == "Judgement_church")
    		{
    		    dialog.text = "ここまでか……終わりだ\nドン・エンリコは本気だったらしい。この地下牢からは逃げ道がない。 水面のところにもう一つ扉を見つけたときは一瞬希望が湧いたが、今は……もう時間の感覚も失った――どれほどこの暗い通路を彷徨っていたのか？半日か、一日中か？この場所は棺桶のように静かで、不気味だ\nかつてここには教会があったはずだ。ここで祈るにはうってつけの場所だな。俺は多くの罪を犯した、あまりにも多く……ここで祈り、眠ることにしよう。傷と疲労で死にそうだ。運が良ければ、もう二度と目覚めることはないだろう……";
    			link.l1 = "";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead");
				AddDialogExitQuestFunction("Mtraxx_RetributionBead");
    		}
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice") && pchar.questTemp.Mtraxx.Retribution.Choice == "to_choice")
			{
				dialog.text = "";
    			link.l1 = "私は、シャルル・ド・モール、フランスの船長にして貴族として、自分自身と良心に誓う――もう二度と海賊の過去には戻らないと！";
    			link.l1.go = "Good_Choice";
				link.l2 = "ああ！ああ！アハハハ！！やったぞ、生き延びた！ざまあみろ、ゾロ！地獄へ落ちろ、マーカス！これからは俺一人だ！ チャーリー・プリンスは死んだかもしれねえが、シャルル・ド・モールを殺せる奴なんて誰もいねえ！";
    			link.l2.go = "Bad_Choice";
			}
			// <-- legendary edition
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog")) {
				dialog.text = "どうすればいいんだ？";
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime")) {
					DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime");
					dialog.text = "…もちろん、ルヴァスールは馬鹿じゃねえさ。じゃなきゃ、今この瞬間に俺たちを逮捕する必要なんてあるか？\nしかも、奴らは一言もしゃべりやがらねえ！\n"+dialog.text;
				}
				
				DeleteAttribute(link, "l1");
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Helena")) {
					link.l1 = "「ヘレン、どうしてそんなに静かなんだ？」";
					link.l1.go = "tonzag_jail_helena";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Mary")) {
					link.l2 = "メアリー、どうしてそんなに嬉しそうなんだ！？";
					link.l2.go = "tonzag_jail_mary";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tichingitu")) {
					link.l3 = "ティチンギトゥ？状況にふさわしいことを言ってみろ。";
					link.l3.go = "tonzag_jail_tichingitu";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tonzag")) {
					link.l4 = "エルキュール、聞こえるか？どうするつもりだ？";
					link.l4.go = "tonzag_jail_tonzag";
				}
				
				link.l5 = "仕方ねえな。しばらくミシェルの靴を履くしかねえか。";
				link.l5.go = "tonzag_exit";
			}
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailPanic")) {
				dialog.text = "";
				link.l1 = "なんてこった、エルキュールが殺された！";
				link.l1.go = "exit";
				link.l2 = "てめえら野郎どもめ！";
				link.l2.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.TonzagQuest.JailPanic");
				AddDialogExitQuestFunction("Tonzag_GFAfterShot");
			}
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.RefusedGame")) {
				dialog.text = "なんて夜だ！なんであいつの言うことなんか聞いたんだ？兄貴の言う通りだった――ここの女たちはまるで別人だぜ。もしかしてラム酒に何か入れてるのか？";
				link.l1 = "寝る時間だ、それから――カルタヘナへ行くぞ！";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.RefusedGame");

				AddDialogExitQuestFunction("HelenDrinking_LightsOut1");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk")) {
				dialog.text = "何一つ盗まれていないが、すべてが散らかっている。\n貴重品でさえ手つかずのままだ。 ";
				link.l1 = "奴らは俺を襲おうとしたんじゃねえ――何か特定のものを探してたんだ。\nだが、それは何だ？そしてもっと重要なのは、誰が……？";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk");

				AddDialogExitQuestFunction("PZ_OsmatrivaemSunduk_4");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_GotovimShlupki")) {
				dialog.text = "夜になるまで待ってから攻撃しようぜ！";
				link.l1 = "その間に俺たちはロングボートの準備を始めるぜ。";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_GotovimShlupki");

				AddDialogExitQuest("PZ_ShturmZvezdy");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_TiboUkralDevu")) {
				dialog.text = "ああ、神よ……いやだ、いやだ、いやだ…… ";
				link.l1 = "";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_TiboUkralDevu");
				
				LAi_SetActorType(pchar);
				LAi_ActorAnimation(pchar, "kneeling", "1", 7.5);
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_DevaMertva")) {
				dialog.text = "ああ神よ、ああ神よ、ああ神よ……なぜだ？ああ神よ、なぜ……でも俺はできることは全部やったのに……";
				link.l1 = "全部俺のせいだ、俺一人の責任だ。間に合わなかったんだ。本当にすまない……どうか、どうか許してくれ。";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_DevaMertva");

				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva8");
			}
		break;
		
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("とんでもねえ戦いだったな……これで逃げやがった腰抜けどもを呼び戻せるぜ……","ははっ！楽勝だったな。あの陸の野郎どもは散り散りになっちまったぜ！");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("ふむ……さて、これからどうすればいいんだ？","これからどうする？");
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "仲間を呼べ。";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
			else 
			{   //исп.линейка, квест №6, возможность переночевать в оплаченной комнате
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "朝まで休む。";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "夜まで休む。";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "次の朝まで休む。";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        if (!bDisableMapEnter)//боя в море нет
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "奴隷たちを船員に加えろ。";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // захват города
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && !CheckAttribute(Pchar, "questTemp.Sharlie.DefendSP"))
	        {
	            Link.l6 = "一番近い町の攻略を始めろ。";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
	        
			bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
	        if(!bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait") && !CheckAttribute(loadedLocation, "CannotWait")) 
	        {
	        	Link.l7 = "休むべきだな……";
	    		Link.l7.go = "TalkSelf_StartWait";
	    	}
			
			if(CheckAttribute(pchar, "equip.gun"))
			{
				if(CheckAttribute(pchar, "chr_ai.gun.bulletNum") && sti(pchar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l8 = "火器の弾薬を交換したい。";
					Link.l8.go = "SetGunBullets";
				}	
			}
			
			if(CheckAttribute(pchar, "equip.musket"))
			{
				if(CheckAttribute(pchar, "chr_ai.musket.bulletNum") && sti(pchar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l9 = "火縄銃の弾薬を交換したい。";
					Link.l9.go = "SetMusketBullets";
				}
					Link.l10 = "戦闘用の主武器を選びたい。";
					Link.l10.go = "SetPriorityMode";
			}
			
			Link.l19 = "普段使いのためのポーションを選びたいんだ。";
			Link.l19.go = "ChoosePotion";
			
			//--> Голландский гамбит
			if(CheckAttribute(pchar, "questTemp.HWIC_Coordinates") && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l11 = "地図の座標を使って島を探してみろ。";
	    		Link.l11.go = "Seek_AbyIsland";
	    	}
			//<-- Голландский гамбит
			
			//--> Ложный след
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabin" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "アダム・レイナーを呼べ。";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "CatchAdam" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "アダム・レイナーを逮捕しろ。";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			//<-- Ложный след
			// Addon 2016-1 Jason Пиратская линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Ammo") && PChar.location == "Shore37") // прогон 3
	        {
	        	Link.l17 = "箱の中身を数えて、ピカールのために弾薬集めを終えるかどうか決めろ。";
	    		Link.l17.go = "mtraxx_ammo";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Mutiny") && pchar.location == "Maracaibo_Plantation" && stf(environment.time) >= 3.00 && stf(environment.time) < 4.00) 
	        {
	        	Link.l17 = "マラカイボのプランテーションを攻撃するよう命令を出せ。";
	    		Link.l17.go = "mtraxx_mutiny";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_boats" && pchar.location == "Maracaibo_river") 
	        {
	        	Link.l17 = "ロングボートを建造するよう命令を出せ。";
	    		Link.l17.go = "mtraxx_boats";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "powder" && pchar.location == "shore10") 
	        {
	        	Link.l17 = "倒れた胸壁に火薬を届けるよう命じろ。";
	    		Link.l17.go = "mtraxx_powder";
	    	}
			// Jason Долго и счастливо
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "letter") 
	        {
	        	Link.l18 = "結婚式のことを考えてみろ。";
	    		Link.l18.go = "LH_marry";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "marry_offer" && LongHappy_CheckShore()) // 28-03-20
	        {
	        	Link.l18 = "結婚を申し込む。";
	    		Link.l18.go = "LH_marry_3";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "toIslaTesoro" && pchar.location == "Pirates_town") 
	        {
	        	Link.l18 = "祝宴の準備をしろ。";
	    		Link.l18.go = "LH_marry_4";
	    	}
			//--> завершение игры
			if(CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) // patch-9
	        {
	        	Link.l15 = "カリブでの用事を済ませてヨーロッパへ航海しろ。";
	    		Link.l15.go = "final_1";
	    	}
			//<-- завершение игры
			Link.l20 = RandPhraseSimple("今は無理だ。時間がない。","そんな暇はねえ、やることが山ほどあるんだ。");
			Link.l20.go = "exit";
		break;
		
		case "tonzag_exit":
			DialogExit_Self();
			AddDialogExitQuestFunction("Tonzag_CreateKiller");
		break;
		

		
		case "SetGunBullets":
			Dialog.Text = "弾薬の種類を選択してください：";
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;
		
		case "SetGunBullets2":
			i = sti(PChar.GenQuest.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(pchar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetGunBullets");
			DialogExit_Self();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "弾薬の種類を選択してください：";
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;
		
		case "SetMusketBullets2":
			i = sti(PChar.GenQuest.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, "musket", sBullet);
			LAi_GunSetUnload(pchar, "musket");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetMusketBullets");
			DialogExit_Self();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "戦いの始まりには、私はこれを使う：";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			pchar.PriorityMode = 1;
			DialogExit_Self();
		break;
		
		case "MusketPriorityMode":
			pchar.PriorityMode = 2;
			DialogExit_Self();
		break;
		
		case "ChoosePotion":
			Dialog.Text = "「ポーションを選んでください：」";
	    	Link.l1 = "治癒の薬。";
	    	Link.l1.go = "ChoosePotion1";
			Link.l2 = "「エリクサー。」";
	    	Link.l2.go = "ChoosePotion2";
			Link.l3 = "「混合物。」";
	    	Link.l3.go = "ChoosePotion3";
			Link.l4 = "ジンジャーの根。";
	    	Link.l4.go = "ChoosePotion4";
			Link.l5 = "ラム酒。";
	    	Link.l5.go = "ChoosePotion5";
			Link.l6 = "ワイン。";
	    	Link.l6.go = "ChoosePotion6";
			if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
			{
				Link.l7 = "自動的にポーションを選択したい。";
				Link.l7.go = "ChoosePotion7";
			}
			Link.l8 = "待て、やっぱり気が変わった。";
	    	Link.l8.go = "ChoosePotion8";
		break;
		
		case "ChoosePotion1":
			log_info("A healing essence will be used by default.");
			pchar.GenQuest.Potion_choice = "potion1";
			DialogExit_Self();
		break;
		
		case "ChoosePotion2":
			log_info("An elixir will be used by default.");
			pchar.GenQuest.Potion_choice = "potion2";
			DialogExit_Self();
		break;
		
		case "ChoosePotion3":
			log_info("A mixture will be used by default.");
			pchar.GenQuest.Potion_choice = "potion4";
			DialogExit_Self();
		break;
		
		case "ChoosePotion4":
			log_info("A ginger root will be used by default.");
			pchar.GenQuest.Potion_choice = "potion5";
			DialogExit_Self();
		break;
		
		case "ChoosePotion5":
			log_info("Rum will be used by default.");
			pchar.GenQuest.Potion_choice = "potionrum";
			DialogExit_Self();
		break;
		
		case "ChoosePotion6":
			log_info("Wine will be used by default.");
			pchar.GenQuest.Potion_choice = "potionwine";
			DialogExit_Self();
		break;
		
		case "ChoosePotion7":
			log_info("Potions will be selected automatically.");
			DeleteAttribute(pchar, "GenQuest.Potion_choice");
			DialogExit_Self();
		break;
		
		case "ChoosePotion8":
			DialogExit_Self();
		break;
		
		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  захват города
		case "TalkSelf_TownAttack":
            int needCrew = 500;
			if(CheckOfficersPerk(pchar, "Troopers")) needCrew = 300;
            bOk = (GetPartyCrewQuantity(Pchar, true) >= needCrew) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "町の攻略を始めることはできるが、砦の大砲からの斉射には船が長く耐えられねえし、上陸部隊を送ることもできねえ。";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
					if (pchar.location == "Panama_ExitTown" || pchar.location == "Tortuga_ExitTown" || pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_ExitTown") // patch-5
					{
						Dialog.Text = "いや、まだそこまでイカれちゃいねえよ……";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						if (pchar.location == "LosTeques_ExitTown")
						{
							Dialog.Text = "この鉱山について金や銀の採掘状況を事前に調べずに攻撃しても意味がない。\nそうでなければ、俺は部下たちを無駄死にさせることになるだけだ。";
							Link.l1 = "...";
							Link.l1.go = "exit";
						}
						else
						{
							Dialog.Text = "Attack "+GetCityName(chr.City)+".";
							if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && pchar.location == "PortSpein_ExitTown") // Jason НСО
							{
								Link.l1 = "ふざけるな！止まれ！";
								Link.l1.go = "exit";
								break;
							}
							if (CheckAttribute(pchar, "questTemp.Patria")) // Jason НСО
							{
								if (pchar.questTemp.Patria != "fail" || pchar.questTemp.Patria != "complete")
								{
									if (pchar.location == "Marigo_ExitTown" || pchar.location == "Villemstad_ExitTown")
									{
										Link.l1 = "ふざけるのはやめろ！止まれ！";
										Link.l1.go = "exit";
										break;
									}
								}
							}
							Link.l1 = "武器を取れ！";
							Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "止まれ！";
							Link.l2.go = "exit";
						}
	    		}
	        }
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "へっ！乗組員が足りねえな；最低でも必要だぜ "+needCrew+" 男たち。";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "散らばるな！攻撃を続けろ！";
					Link.l2 = "...";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // для сухопутных
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "奴隷たちは誰一人として乗組員になる気はない。";
	            Link.l1 = "奴らなんかくたばっちまえ！";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "新しい船員のための空きスペースは船にない。";
	                Link.l1 = "へっ！乗組員の一部を別の船に移す必要があるな。";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "あなたの乗組員は補充できる "+pchar.GenQuest.SlavesToCrew+" お前のもとで仕えたいという奴隷たちだ。受け入れるか？";
	                Link.l1 = "Yes";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "No";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
			bOk = ShipBonus2Artefact(pchar, SHIP_MEMENTO) && CheckAttribute(&RealShips[sti(pchar.Ship.Type)], "DeadSailors.RecruitSlaveBonus");
			if(!bOk)
			{
				// belamour legendary edition перк получил время работы, старый метод не подходит
				if (GetOfficersPerkUsing(pchar, "IronWill"))
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
				}
				else
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
				}
			}
			ChangeCharacterComplexReputation(pchar,"authority", -0.5);
	        // падение опыта -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "この素晴らしい船は今や俺のものだ、そしてここでは俺が船長だぜ！だが、 全員の船員を殺さなきゃならなかったのは残念だな。";
			Link.l1 = "上陸する時が来たな……";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "「どの仲間を呼び出せばいい？」";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "また今度な。";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		//--> Голландский гамбит
		case "Seek_AbyIsland":
			bOk = CheckCharacterItem(pchar, "bussol") && CheckCharacterItem(pchar, "clock2");
			bool bOk1 = CheckCharacterItem(pchar, "sextant2");
			if (bOk || bOk1)
			{
				DialogExit();
				DeleteAttribute(pchar, "questTemp.HWIC_Coordinates");
				pchar.questTemp.HWIC_FindIsland = "true";
				AddDialogExitQuestFunction("PrepareSearchingFor");
			}
			else
			{
				dialog.text = "必要な航海用の計器がないのが残念だな、緯度と経度を測れねえ。島はまた別の機会に探すしかねえな。 ";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		//<-- Голландский гамбит
		
		//--> Ложный след
		case "FalseTrace_Cabin":
			dialog.text = "ボースン！すぐにアダム・レイナーを俺のところに連れて来い！";
			link.l1 = "あいよ、船長！";
			link.l1.go = "exit";
			chr = characterFromId("Mugger");
			if (pchar.questTemp.FalseTrace == "CatchAdam") chr.dialog.currentnode = "FalseTrace_17";
			else chr.dialog.currentnode = "FalseTrace_7";
			pchar.questTemp.FalseTrace.CharID = "Mugger";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		
		case "FalseTrace_Woman":
			DialogExit();
			chr = characterFromId("FalseTraceWife");
			chr.dialog.currentnode = "FalseTrace_wife_6";
			pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		//<-- Ложный след
		
		//--> LSC, приколы со стуком в дверь
		case "knock_2":
			PlaySound("interface\knock_2.wav");
			dialog.text = "さて、ノックしたから、あとは返事を待つだけだな……";
			link.l1 = "（待て）";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3":
			PlaySound("interface\knock.wav");
			dialog.text = "さて、ノックしたから、あとは返事を待つだけだな……";
			link.l1 = "（待て）";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3_1":
			PlaySound("interface\knock_3_1.wav");
			dialog.text = "さて、ノックしたから、あとは返事を待とう……";
			link.l1 = "（待て）";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_1_3":
			PlaySound("interface\knock_1_3.wav");
			dialog.text = "さて、ノックしたから、あとは返事を待とう…";
			link.l1 = "（待て）";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_2_2":
			PlaySound("interface\knock_2_2.wav");
			dialog.text = "さて、ノックしたから、あとは返事を待とう…";
			link.l1 = "（待て）";
			link.l1.go = "knock_right";
		break;
		
		case "knock_wrong":
			dialog.text = "奴はドアを開けてくれねえな……秘密のノックを間違えたか。\nまあいい、明日また来て試してみるさ。\n今日は絶対に開けてくれねえだろう。";
			link.l1 = "（立ち去る）";
			link.l1.go = "exit";
		break;
		
		case "knock_right":
			PlaySound("interface\key.wav");
			PlaySound("Voice\English\YouFace.wav");
			dialog.text = "なんてこった！あいつが返事してドアを開けやがった！これで中に入れるぜ…";
			link.l1 = "（エンター）";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.DiffIndoor");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
		break;
		//<-- LSC, приколы со стуком в дверь
		
		// суп из черепахи
		case "terrapin":
			PlaySound("Interface\Door_Kick.wav");
			PlaySound("Voice\English\EvilPirates02.wav");
			dialog.text = "カランバ！なるほど、これがルヴァスールの遅れて来た援軍か……ドアからはとても出られねえな……よし、チボーの真似をしてやるぜ――窓からだ！なんせ、あの悪党もどうにかして逃げおおせたんだからな！\n";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Terrapin_GoWindow");
		break;
		
		// защита Сен-Пьера
		case "SP_defend":
			PlaySound("Voice\English\military02.wav");
			dialog.text = "つまり、我々の任務は忌々しいスペイン軍の攻撃を撃退し、サン・ピエールを救うことだ。砦は占拠され、 街中で戦闘が続いている。サン・ピエールの湾には強力な戦隊がいて、旗艦は戦列艦だ。今攻撃しても無駄だぜ。 砦も街も敵の手にあるから、港に上陸させてはくれねえ\nだから俺は、ジャングルを抜けて市門から背後を突くことに決めた。砦と街からスペイン兵を一掃したら、 戦隊に取りかかる。砦の砲撃支援がなくなれば、あいつらもずっと脆くなるはずだ\n楽な戦いじゃねえが、特別に十万ペソを通常の給金に加えて船員たちに分配するよう命じておいた。さあ、行くぞ！";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("DefendSP_GoJungle");
		break;
		
		// финал игры
		case "final_1": // Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) // генерал-губернатор никуда не уедет
			{
				dialog.text = "待ってくれ、俺はどこへ行くんだ？パリの許可なしに総督の地位を離れるわけにはいかん！そうでなければ、 フランスに戻った時に、任された植民地を無断で放棄した罪で間違いなく逮捕されてしまう。パリよ、お前が恋しい…";
				link.l1 = "";
				link.l1.go = "exit";
				EndQuestMovie();
			}
			else
			{
				dialog.text = "それでは、もう時間を無駄にするのはやめましょう！愛しきガスコーニュの野原が恋しくてたまりません！出航だ！";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("Final_ReturnToEurope");
			}
		break;
		
		case "final_2":
			dialog.text = "俺はこれが正しい決断だと思うぜ！こっちに来ちまった今、古き良きヨーロッパに俺に残されたもんなんてねえだろ？ それに、いつでも好きな時にフランスへ帰れるんだしな！";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Final_StayInCarribean"); // 010912
			DeleteAttribute(pchar, "questTemp.Tieyasal_final");
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN_1":
			dialog.text = "それが一番いい方法だ。俺は乗船して、ここから出航するべきだな。";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseExit");
		break;
		
		case "FMQN_2":
			dialog.text = "いや、絶対に行かないぜ。俺はここに残る。でもな、ただ何が起こるかわからねえまま待ってるつもりはねえ。 フィリップスブルフの港に向かって状況を調べてみるべきだ。あいつらの言いなりになって、 盲目的な道具になる気はねえよ。";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseContinue");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_ammo":
			Mtraxx_PlantCheckShoreBox(); // анализируем содержимое сундука
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && !CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade")) // собрали 30 сабель
			{
				dialog.text = "冷たい鋼三十本が箱に入ってるぜ！ここでやめるか、それとももっと火器や火薬、薬を集めるべきか？";
				link.l1 = "もう十分だ！";
				link.l1.go = "mtraxx_ammo_1";
				link.l2 = "いや、俺はこの箱をもっと詰めておくべきだ。";
				link.l2.go = "exit";
				// belamour legendary edition
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Full")
				{
					link.l3 = "ファディの箱の中身を詰めて、余った分を持っていけ。"; 
					link.l3.go = "mtraxx_ammo_1";
				}
			}
			else
			{
				dialog.text = "冷たい鋼鉄三十本はまだ集まっていない！もっと持ってこなきゃな。";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_ammo_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "チェストに鍵をかけて、それをプランテーションに密かに運び込む計画を立てる。";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantShoreBoxComplete");
		break;
		
		case "mtraxx_mutiny":
            dialog.text = "行け、突撃だ！おおっ！";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantMutiny");
		break;
		
		case "mtraxx_boats":
            if (GetSquadronGoods(pchar, GOOD_PLANKS) >= 20 && GetSquadronGoods(pchar, GOOD_LEATHER) >= 10) // наличие материалов
			{
				if (Mtraxx_MeridaCheckCarpenter()) // наличие плотника
				{
					dialog.text = "必要な材料はすべて揃った、すぐにロングボートの建造を始めよう。";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_MeridaBuildBoats");
				}
				else
				{
					dialog.text = "この仕事をこなせる経験豊富な船大工がいない。\nこの役職には士官を任命すべきだな。";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "材料が足りねえ、少なくとも板材20束と革10梱が必要だ。";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_powder":
            if (GetSquadronGoods(pchar, GOOD_POWDER) >= 300) // наличие пороха
			{
				if (GetCrewQuantity(pchar) >= 20) // наличие команды
				{
					dialog.text = "全部準備できたぜ、ぶちかますぞ！";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_RetributionBarrels");
				}
				else
				{
					dialog.text = "火薬を運ぶには最低でも20人は必要だ。";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "火薬が足りねえ、少なくとも300は必要だ。";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_dungeon":
			PlaySound("ambient\jail\jail_door2.wav");
            dialog.text = "それは扉だったのか？";
			link.l1 = "";
			link.l1.go = "mtraxx_dungeon_1";
		break;
		
		case "mtraxx_dungeon_1":
			PlaySound("ambient\jail\jail_door1.wav");
            dialog.text = "よし！客人が来たぞ……ヤン？… ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionRunToEnrico");
		break;
		// belamour legendary edition -->
		case "Good_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "good";
			DoQuestCheckDelay("Mtraxx_RetributionFreedom", 0.5); 
			DialogExit_Self();
		break;
		
		case "Bad_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "bad";
			Achievment_Set("ach_CL_97");
			bNoEatNoRats = false;
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Roger_10", "18");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
			DialogExit_Self();
		break;
		// <-- legendary edition
		
		// Jason Долго и счастливо
		case "LH_marry":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			string sTemp = sld.name;
			dialog.text = "お前と "+sTemp+" 俺たちは長い間一緒にいて、絆はどんな教会の誓いよりも強いが、この瞬間を二人とも覚えていたいんだ。だから、 彼女にプロポーズする場所を決める必要がある：";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "イスラ・テソロ――この島は俺たちの物語にとって大きな意味があるんだ。\nもっと良い場所なんてないだろうな。サブ・マティラ湾は夕暮れ時がとびきり美しいぜ！";
				link.l1.go = "LH_marry_1_1";
			}
			link.l2 = "トルトゥーガ――我らの時代の自由の象徴だ。そして灯台からトルトゥ海峡を望む景色は、どんな画家の筆にも値するぞ！";
			link.l2.go = "LH_marry_1_2";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l3 = "ジャマイカ――本当に奥が深いぜ！\nそれに、ポートランド湾で夜明けを眺めるのは、まるで地上の楽園みたいだ。";
				link.l3.go = "LH_marry_1_3";
			}
		break;
		
		case "LH_marry_1_1":
			pchar.questTemp.LongHappy.Shore = "Shore_ship1";
			AddQuestRecord("LongHappy", "2_1");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "しかし、教会の厳粛な儀式なしではこれを行うことはできません――すべては規範に従って行われなければならず、そうすれば父も私の選択を受け入れざるを得なくなるでしょう。だから、 神父が必要なのです。そして、この役目にふさわしいのはベノワ院長しかいないと私は思います。 彼は父の古い友人であり、私の新世界での冒険も彼を通じて始まりました。 この名誉を私のために引き受けてくれると信じています。";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_2":
			pchar.questTemp.LongHappy.Shore = "Mayak6";
			AddQuestRecord("LongHappy", "2_2");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "しかし、教会の厳粛な儀式なしではこれを行うことはできません――すべては規範に従って進めなければならず、そうすれば父も私の選択を受け入れざるを得なくなるでしょう。ですから、 神父が必要ですし、この役目に最もふさわしいのはベノワ院長以外にいないと思います。彼は父の古い友人であり、 私の新世界での冒険も彼から始まりました。きっと、この名誉を引き受けてくれると思います。";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_3":
			pchar.questTemp.LongHappy.Shore = "Shore36";
			AddQuestRecord("LongHappy", "2_3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "しかし、教会の厳粛な儀式なしではこれを行うことはできません――すべては規範に従って行われなければならず、そうすれば父も私の選択を受け入れざるを得なくなるでしょう。だから、 私は神父が必要ですし、この役目に最もふさわしいのはベノワ院長しかいないと考えています。彼は父の古い友人であり、 私が新世界で冒険を始めたのも彼のおかげです。きっと私の願いを聞き入れてくれると信じています。";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_2":
			AddQuestRecord("LongHappy", "3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "まあ、人間の厳粛さがなくてもこういうことは起こり得るさ。だが、できればこれについては "+sTemp+" 少し後で。";
			link.l1 = "";
			link.l1.go = "exit";
			pchar.questTemp.LongHappy = "choose";
		break;
		
		case "LH_marry_3":
			dialog.text = "よし、俺は準備できてるぜ！";
			link.l1 = "";
			link.l1.go = "exit";
			LongHappy_MarryOffer();
		break;
		
		case "LH_marry_4":
			if (LongHappy_CheckGoods())
			{
				dialog.text = "すべて準備できたぞ！";
				link.l1 = "";
				link.l1.go = "exit";
				LongHappy_OnIslaTesoro();
			}
			else
			{
				dialog.text = "必要な品物と金貨はまだ集まっていないぞ！";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
	}
}

void DialogExit_Self()
{
    SendMessage(PChar, "ls", MSG_CHARACTER_EX_MSG, "forceBlend");
    DialogExit();
	locCameraSleep(false); //boal
}
