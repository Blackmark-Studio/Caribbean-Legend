// Чарли Книппель - старый артиллерист
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		//ветка на взятие 2 варианта прохождения - за Англию
		if(CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "おい、相棒、チェーンショットなんざくそくらえだぜ！何の用でここに来たんだ？";
			link.l1 = "お前の…何にチェーンショットを？いや、もういい、ただ挨拶したかっただけだ。";
			link.l1.go = "exit";
			link.l2 = "ごきげんよう、クニッペルさん。はは、なぜあなたがクニッペルと呼ばれているのか分かりましたよ。さて、 あなたがかつてイギリス海軍に仕えていたという噂を耳にしました。私は立派な船と腕の立つ乗組員を持っています。 イギリス王室……いや、コモンウェルスに自分と船をお役立てしたいのです。何か助言をいただくか、 誰かに推薦していただくことはできますか？あるいは、その件でお力添えいただけませんか？\n";
			link.l2.go = "Knippel_check";
			break;
		}
		//за Голландию
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "おい、相棒、チェーンショットなんてくそくらえだぜ！何しに来やがった？";
				link.l1 = "ごきげんよう、クニッペルさん。はは、なぜあなたがクニッペルと呼ばれているのか分かった気がします。 かつてイギリス海軍にいたという噂を聞きましたので、あなたに助けをお願いしたいのです…";
				link.l1.go = "Dominica";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "チェーンショットだと？ふざけんな！何の用だ、相棒？";
			link.l1 = "いや、なんでもない。俺は行くぜ。";
			link.l1.go = "exit";
			break;
		}
		//за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "おい、船長、銀の護送船団が襲われたって噂を聞いたぜ……";
				link.l1 = "「よくご存知ですね、キニッペルさん。」";
				link.l1.go = "HollConvoy_Check";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Wait")
			{
				dialog.text = "質問はあるか、船長？";
				link.l1 = "いや、なんでもない。俺は行くぜ。";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main")
			{
				dialog.text = "会えて嬉しいぜ、船長！俺の上官リチャード・フリートウッドも本当は自分であんたに会いに来るつもりだったんだが、 昨夜事件が起きてな…誰かが通りの真ん中で奴を殺そうとしやがったんだ、チェーンショットで尻を撃たれるなんてよ！";
				link.l1 = "ありえない！衛兵たちは何をしていたんだ？";
				link.l1.go = "Fleetwood_house";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "質問はあるかい、船長？";
			link.l1 = "いや、なんでもない。俺は行くぜ。";
			link.l1.go = "exit";
		break;
		}
			dialog.text = "おい、鎖弾なんてくそくらえだぜ！何しにここへ来やがった？";
			link.l1 = "やあ、ちょっと立ち寄っただけだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------за Голландию--------------------------------------------------	
		case "Dominica":
			dialog.text = "ああ、そうかい？で、ずいぶん前に陸に上がった年寄り水夫がどうやってお前の役に立てるんだ、相棒？";
			link.l1 = "見てくれ…俺はただの普通の船長で、マルティニークとキュラソーの間を定期的に航海してるんだ。\nマルティニークの近くで幽霊船に二度も襲われたことがある…\nでもな、あれはファタ・モルガーナでもフライング・ダッチマンでもねえんだ。 普通の砲弾であいつの帆を引き裂くことができたんだぜ！";
			link.l1.go = "Dominica_1";			
		break;
		
		case "Dominica_1":
			dialog.text = "そうかい？それは確かに幽霊船らしくねえな、実体のある砲弾で帆を失うなんてよ、まったく驚いたぜ…";
			link.l1 = "俺の船が風上に向かって全速で走れたからこそ、なんとか生き延びたんだ。\n前回は、逃げるために船体を軽くしようと積み荷を全部海に投げ捨てる羽目になった……その損失、想像できるか？胸が張り裂けそうだったぜ！";
			link.l1.go = "Dominica_2";			
		break;
		
		case "Dominica_2":
			dialog.text = "やれやれ、船長……";
			link.l1 = "キュラソー総督マティアス・ベックは、私の訴えをまるで相手にしなかった。幽霊船の話など馬鹿げているし、 私の見張りたちはグロッグで酔っていたのだと言うのだ。マルティニーク総督は巡回隊を送ると約束してくれたが、 その目は何もする気がないことを物語っていた。\nあの忌々しい海賊“幽霊”がうろついている間は、マルティニークには戻れない。私の船も乗組員も小規模で、 三度目の遭遇にはとても生き残れそうにない……";
			link.l1.go = "Dominica_3";			
		break;
		
		case "Dominica_3":
			dialog.text = "「こりゃあ、まったくもって残念だぜ、相棒。で、俺に何を手伝ってほしいんだ？」";
			link.l1 = "このあたりの船乗りたちから聞いた話だが、セントジョンズにはリチャード・フリートウッドという船長がいて、 あの幽霊船を追いかけたことがあるそうだ。私自身は彼を知らないので、こうしてあなたにこの話をしている。 もしよければ、私の不運な話を彼に伝えてくれないか？きっとあの汚い海賊はドミニカの荒れた海岸の近くに隠れていて、 バルバドスとマルティニークの間で略奪を働いているに違いない。\n";
			link.l1.go = "Dominica_4";			
		break;
		
		case "Dominica_4":
			dialog.text = "バルバドスとマルティニークの間か？ははっ！あそこは儲かる太い交易路だぜ。いかにも、 あの下衆野郎がやりそうなことじゃねえか。";
			link.l1 = "私は金持ちでもなければ太ってもいませんし、軍艦の護衛を頼むために艦長に賄賂を渡す金もありません。ですが、 もしフリートウッド旦那がすでにこのドブネズミを追っているのなら、その「フライング・ダッチマン」がどこにいるか、 彼に教えていただけませんか？\n";
			link.l1.go = "Dominica_5";			
		break;
		
		case "Dominica_5":
			dialog.text = "ここに来てくれてよかったぜ。お前の話はしかるべき奴らに伝えてやる、 俺の肝臓にチェーンショットをぶち込んでもいいくらいにな！ もうすぐマルティニークとまた交易できるようになるだろう。";
			link.l1 = "神があなたの言葉を聞き届けてくださることを願っています！私の話を聞いてくれてありがとう、チャーリー。 うまくいくことを本当に願っています。さようなら、そしてチェーンショットには気をつけて！";
			link.l1.go = "Dominica_6";			
		break;
		
		case "Dominica_6":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toDominica";
			AddQuestRecord("Holl_Gambit", "1-17");
			pchar.quest.toDominica.win_condition.l1 = "location";
			pchar.quest.toDominica.win_condition.l1.location = "Dominica";
			pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
			DelMapQuestMarkShore("Shore1");
			DelMapQuestMarkShore("Shore2");
			AddMapQuestMarkIsland("Dominica", true);
		break;

//----------------------------------------------за Англию--------------------------------------------------	
		case "Knippel_check"://начинаем проверять нашего ГГ по всем статьям
			if(makeint(PChar.reputation.nobility) < 48)//низкая репа
			{
				Notification_Reputation(false, 48, "low");
				PlaySound("Voice\English\hambit\Charlie Knippel-04.wav");
				dialog.text = "陽気なイングランドが悪党どもの助けなんぞ要らねえよ、鎖弾なんざクソくらえだ！悪いが、さっさと失せやがれ。";
				link.l1 = "おいおい、相棒、口の利き方に気をつけろよ、じゃねえとその口を縫い合わせてやるぜ！";
				link.l1.go = "exit";
				break;
			}
			else
			{
				Notification_Reputation(true, 48, "low");
			}
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 30)//низкая навигация
			{
				dialog.text = "船長、はっきり言うぜ。お前じゃ濡れた袋からも出航できねえよ。航海術をもっと身につけてから出直してきな、 わかったか？";
				// belamour legendary edition покажем критерии  -->
				notification("Skill Check Failed (30)", SKILL_SAILING);
				//<--
				dialog.text = "カオン、我々の艦隊には経験豊富な船長が必要だ、素人はいらねえ。航海術を身につけてから戻ってこい。";							 
				link.l1 = "なるほど……それでは、また後で会いましょう。";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Skill Check Passed", SKILL_SAILING);
			}
			dialog.text = "おう、ちょうどいい時に来たな、船長、チェーンショットなんてくそくらえだ！ リチャードはこの危ない仕事を誰に任せるか迷っててな、断ろうかとも思ってたくらいだ……だが今日は運の小鳥たちがお前の耳元でさえずってるってわけだ。俺たちの基準に見合う働きを見せりゃ、 とあるとびきり重要な人物にお前を推薦してやるぜ。で、その玉袋に十分な鉛玉は入ってるか？\n";
			link.l1 = "ぶどう弾をたっぷり積んでるぜ、キニッペル旦那。";
			link.l1.go = "Knippel_task";
		break;
		
		case "Knippel_task"://первое задание
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Lucas"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "ははっ！船長、気合いが入ってるな！すぐに火蓋が切られるぜ！よく聞け。オランダ西インド会社の銀船団が一、 二日前にキュラソーのウィレムスタッドを出航した。今はフィリップスブルフへ向かってる。今回は船団の数が少ねえ。 銀を積んだガレオン一隻と、護衛が二隻だけだ。銀船団を捕まえて、 銀積みのイーストガレオンを拿捕してアンティグアまで連れてこい。護衛は沈めても構わねえ、どうせ使い捨てだ。 チェーンショットで肝をぶち抜いてやれ、やー！";
			link.l1 = "奴らの命運ももう尽きるさ。";
			link.l1.go = "Knippel_task_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_task_1":
			dialog.text = "助言だぜ、船長。キュラソーからシント・マールテンへの交易航路は、セント・クリストファーの海岸近くを通ってる。 あそこで待ち伏せするのがいいだろう。しっかり準備して、船も万全にしておけよ。 ウェスト・インディア会社とやり合うのは、可愛い女の子と散歩するような甘いもんじゃねえからな。";
			link.l1 = "自分が何に巻き込まれるかは承知していますが、率直に話してくれて感謝します、キニッペルさん。 オランダの銀を持って戻ってきます。";
			link.l1.go = "Knippel_task_2";			
		break;
		
		case "Knippel_task_2":
			DialogExit();
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Eng = "true";//признак, что английка уже бралась
			HWICSilverConvoyInWorld();
			AddQuestRecord("Holl_Gambit", "2-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила ,чтобы вышел из архива. 																				   
			pchar.questTemp.HWIC.Eng = "begin";
			SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;
		
		case "HollConvoy_Check"://начинаем проверять
			int iHal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_GALEON_L) iHal++;
				}
			}//признак наличия ТГ в компаньонах
			if (iHal > 0)
			{
				amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
				if (amount <= 0)
				{
					dialog.text = "何があったかなんて言わなくていいぜ、船長。お前の船を税関役人が調べてる間に、全部聞かされてたんだよ……よくやったな、船長。まったく見事だ！楽な仕事には聞こえなかったぜ、鎖弾だとよ、冗談じゃねえ！";
					link.l1 = "評価されるのは嬉しいものだ。";
					link.l1.go = "HollConvoy_complete";
				}
				else
				{
					dialog.text = "何があったか言う必要はない。税関職員が貴様の船を調べている間に、すべて報告を受けていた……銀を全部持ち帰らなかったな、チェーンショットだと？笑わせるな！あの東インド船にどれだけ銀が積まれていたか、 ペソ単位で把握している。この任務の目的は、貴様の戦闘力だけでなく、誠実さも試すことだった。後者は見事に落第だ。 俺の屋敷から出て行け、この下っ端が！";
					link.l1 = "じゃあくたばれ、この間抜け野郎！";
					link.l1.go = "HollConvoy_fail";
				}
			}
			else
			{
				dialog.text = "止まれ、相棒。お前の艦隊にオランダ東インド会社の船が見当たらねえな。 あれを拿捕してここに連れて来いって言っただろうが。売り払って、その金を自分のものにしようとしたんじゃねえか？";
				link.l1 = "待って、俺が船まで持ってくるべきだったのか？銀だけでいいと思ってたぜ。";
				link.l1.go = "HollConvoy_noShip";
			}
		break;
		
		case "HollConvoy_noShip":
			dialog.text = "チャーリー・ニッペルを馬鹿にする奴なんざいねえ！俺が何を言って、何を言ってねえか、はっきり覚えてるぜ。 お前は俺たちの取引の条件を破ったんだ、まともなイギリス野郎はもうお前なんかと組まねえ。 ここに悪党の居場所はねえ。さっさと俺の家から出ていけ、この雑用野郎！";
			link.l1 = "じゃあくたばれ、この間抜け野郎！";
			link.l1.go = "HollConvoy_fail";
		break;
		
		case "HollConvoy_fail":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-3");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Eng");//зачищаем для возможности отката к голландскому варианту
			pchar.questTemp.HWIC.Fail2 = "true";
		break;
		
		case "HollConvoy_complete":
			dialog.text = "明日私のところに来てくれれば、私の後援者を紹介しよう。君の腕前にふさわしい仕事をさらに用意してくれるはずだ。 それに、君の……金銭的な報酬も手配してくれるだろう。出航だ！";
			link.l1 = "承知しました、クニッペルさん。私は明日ここにおります。";
			link.l1.go = "exit";
			npchar.greeting = "knippel_2";
			AddDialogExitQuestFunction("HollConvoy_Remove");
			AddQuestRecord("Holl_Gambit", "2-4");
			SetTimerFunction("EnglandGambit_2_ZadanieStart", 0, 0, 1);
			pchar.questTemp.HWIC.Eng = "Wait";
			AddSimpleRumourCity("They say that you captured a Dutch ship filled with silver. Well done! You are a valiant sailor, captain! Godspeed!", "SentJons", 10, 3, "");
		break;
		
		case "Fleetwood_house":
			dialog.text = "俺も同じことを考えてたぜ……誰かがフリートウッド船長の目に胡椒を投げつけて、リチャードが剣を抜く間もなく胸を刺しやがった。 犯人は一撃で船長を仕留めるつもりだったんだろうが、時間がなくて二撃目は無理だった。でも失敗した。 フリートウッド船長はいつもコートの下に胸甲を着てるからな\nあの汚ねえ野郎、肝臓にチェーンショットをぶち込んで逃げやがった。どうやら町に仲間がいるらしい。 船長が覚えている唯一の特徴は、暗殺者が片目しかないってことだ。ただ、それじゃあまり役に立たねえな。 最近はああいうサイクロプス野郎が波止場にうようよしてるからよ\nリチャードは大量に血を流したし、胡椒のせいで目がひどくやられて、今じゃほとんど見えねえんだ……";
			link.l1 = "胡椒か？そりゃ、目潰しにしちゃ高くつくな。フリートウッドはよっぽど誰かの怒りを買ったんだろう。 おたくの船長には気の毒だ。\n襲撃者の捜索で何かわかったのか？";
			link.l1.go = "Fleetwood_house_1";
		break;
		
		case "Fleetwood_house_1":
			dialog.text = "フリートウッド船長の海兵たちは町中と近くの湾をくまなく捜索したが、何も見つからなかったんだ、くそったれ！ 襲撃の直後に見つけられなかったなら、今さらあの野郎を見つける望みなんてねえよ。 フリートウッド船長には敵が多いからな……だが船長、事件があったにもかかわらず、俺の上官があんたに会いたがってる。今は自宅で休んでるから、案内するぜ。 ついてきな！\n";
			link.l1 = "案内してくれ、クニッペルさん。";
			link.l1.go = "Fleetwood_house_2";
		break;
		
		case "Fleetwood_house_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			bDisableFastReload = true;//закроем быстрый переход
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
			pchar.quest.Knippel_Outside.win_condition.l1 = "location";
			pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
			pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			sld = characterFromId("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			AddLandQuestMark(sld, "questmarkmain");
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;
		
		case "InFleetwoodHouse":
			dialog.text = "フリートウッド船長は二階の自室にいるぜ。あんたに会うのを待ってるんだ。俺はここに残る。";
			link.l1 = "承知しました、クニッペルさん。すぐに向かいます。";
			link.l1.go = "exit";	
		break;
		
		case "Knippel_ToOfficer":
			dialog.text = "聞いてくれ、船長……フリートウッド船長は今は無事で、ちゃんとした人たちに守られてる。あんたがあの野郎に復讐するのを手伝いたいんだ。 砲術士官として俺の腕を貸すぜ。剣術はあまり得意じゃねえし、もう歳だからな。でも、 商船のトップガラントなら千歩先からでもぶっ飛ばしてやれるぜ。\n";
			link.l1 = "それはぜひ見てみたいな。乗船を歓迎するぜ、キニッペル旦那！";
			link.l1.go = "Knippel_ToOfficer_1";	
		break;
		
		case "Knippel_ToOfficer_1":
			ForceHeroAutolevel(npchar);
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);//откроем локаторы
			//Книппеля - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 20;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false);//на все дела - 1 месяц
			AddSimpleRumourCity("They say that Sir Richard Fleetwood himself is indebted in you. You are a very important man in our town, sir", "SentJons", 10, 3, "");
		break;
		
		case "hired":
			dialog.text = "おう、船長！何か用か？";
			link.l1 = "いいえ、何もありません。";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			if (pchar.questTemp.HWIC.Eng == "MirageFail")
			{
				dialog.text = "お前はまったくの大馬鹿者だ、チェーンショットだと？基本的な任務すら果たせなかったじゃねえか――「ミラージュ」を拿捕し、「ヴァルキリー」を失わずに済ませるだけだったのによ\nもう俺たちはお前の下で働かねえ。フリートウッド旦那も俺たちと同じくらい馬鹿が嫌いだから、 きっとこの決断を認めてくれるさ。";
				link.l1 = "てめえもてめえのご主人もくたばっちまえ！";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
			{
				dialog.text = "お前はまったくの馬鹿だな、鎖弾だと？てめえの個人的な問題に付き合って、もう十分に時間を無駄にしたぜ\nこれ以上お前の下で働く気はねえ。フリートウッド旦那も俺たちと同じくらい馬鹿が嫌いだから、 俺たちの決断をきっと認めてくれるさ。";
				link.l1 = "「てめえもてめえの主人もくたばっちまえ！」";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
			{
				dialog.text = "お前はまったくの大馬鹿者だ、チェーンショットなんてクソくらえだぜ！「ヴァルキリー」 で孤立した商人を演じろと命じられてただろうが、何をやった？自分の艦隊で海賊を追い払っちまったじゃねえか！\nフリートウッド旦那も俺たちと同じくらい馬鹿が嫌いだから、俺たちの決定をきっと認めてくれるさ。";
				link.l1 = "貴様も貴様のご主人もくたばっちまえ！";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake")
			{
				dialog.text = "お前はまったくの間抜けだな、チェーンショットだと？「ミラージュ」 を拿捕してアンティグアへ向かう以外のことで時間を無駄にするつもりか？\n俺たちの乗組員はもうお前には仕えねえ。フリートウッド旦那も俺たちと同じくらい馬鹿が嫌いだから、 この決断をきっと認めてくれるさ。";
			link.l1 = "てめえもてめえのご主人もくたばっちまえ！";
			link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)//если сам на Валькирии
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
						{
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "OnCuracao":
			pchar.quest.HWICEng_toBarbadosOver.over = "yes";//снять прерывание
			dialog.text = "ごきげんよう、船長。お会いできて嬉しいです！";
			link.l1 = "ごきげんよう、クニッペルさん。金は持ってきたか？渡してくれ、 それからウィレムスタッドへアビゲイルを迎えに行こう。君も一緒に来るか？";
			link.l1.go = "OnCuracao_1";	
		break;
		
		case "OnCuracao_1":
			dialog.text = "船長、聞いてくれ……もうどこにも行く必要はねえんだ。";
			link.l1 = "何を言ってるんだ？こんなの馬鹿げてるじゃねえか！";
			link.l1.go = "OnCuracao_2";	
		break;
		
		case "OnCuracao_2":
			dialog.text = "フリートウッド船長からの手紙を預かってきたぜ。あと金もな。だが、この金はアビゲイルの親父のためじゃなくて、 お前のためのもんだ。二十万ペソだ。手紙を読んで、あまりきつく責めないでやってくれよ…";
			link.l1 = "最近は一体どうなってるんだ！？また嫌な知らせか？手紙をよこせ！";
			link.l1.go = "OnCuracao_3";	
		break;
		
		case "OnCuracao_3":
			DialogExit();
			NextDiag.CurrentNode = "OnCuracao_4";
			AddMoneyToCharacter(pchar, 200000);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 1;//ещё денек пусть погуляет по пляжу
			pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
			pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol";//патруль в прибрежных водах
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//открыть подземелье
			pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
			AddQuestRecordInfo("LetterFromFleetwood", "1");
			AddQuestRecord("Holl_Gambit", "2-23");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "OnCuracao_4":
			dialog.text = "読んだかい、船長？はっきり言うぜ。俺はフリートウッド船長のやったことが恥ずかしいよ、チェーンショットで……ああ、くそったれ。ローデンブルクはアビゲイルとリチャードの恋愛を知って激怒したんだ。 歩哨がキュラソー中を捜索してるし、会社の軍艦もこの海域を巡回してる。ここからとっとと逃げなきゃならねえ。\n船長、砲手が必要かい？贅沢なんていらねえ――普通の船の飯が定期的にありゃ十分さ。剣術はあまり得意じゃねえし、もう歳だが、 商船のトップガラントなら千歩先からでもぶっ飛ばせるぜ。";
			link.l1 = "くそっ、ぜひとも見せてほしいもんだな、キニッペルさん。乗組員へようこそ！";
			link.l1.go = "Knippel_hire";
			link.l2 = "最初からお前らイギリスのろくでなしどもを助けたことを後悔してるんだ。\n今さらどうやってこの泥沼から抜け出せばいいかわからねえ。\n自分の道は自分で歩け、もうこれ以上驚きはごめんだぜ。";
			link.l2.go = "Knippel_exit";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*200;
			npchar.OfficerWantToGo.DontGo = true;
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 120, 120);
			LAi_SetOfficerType(npchar);
			npchar.greeting = "knippel_hire";
			NextDiag.CurrentNode = "Knippel_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			ForceHeroAutolevel(npchar);
			
			//Sinistra - через 2 месяца стартует личный квест Чарли Книппеля "Длинные тени старых грехов"
			SetTimerCondition("DTSG_Start", 0, 0, 60, false);
		break;
		
		case "Knippel_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;
		
//------------------------------------------------против всех-----------------------------------------------
		case "Knippel_abordage":
			dialog.text = "止まれ、このクズ野郎！なぜこの平和なオランダ船を襲ったんだ？俺は貴重な品も金も持っちゃいねえ、 鎖弾なんざクソくらえだ！";
			link.l1 = "オランダ船だと？ははっ！笑わせるなよ、“オランダ野郎”。俺がお前のブリガンティンを襲ったのは、お前を捕まえるためさ、可愛いチャーリー。俺の船倉へようこそ。 どこへ向かってたのか、そしてその理由について、じっくり話してもらうぜ…";
			link.l1.go = "Knippel_abordage_1";	
		break;
		
		case "Knippel_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-20");
            pchar.quest.Knippel_DieHard.over = "yes";
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "KnippelPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Knippel_prisoner":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			dialog.text = "お前は悪魔だ、海賊め……その罪のすべてで地獄の業火に焼かれるぞ！ぎゃっ…";
			link.l1 = "落ち着けよ、説教好き。お前の説教はピューリタンみてえだな。まずは自分の魂の心配でもしたらどうだ。";
			link.l1.go = "Knippel_prisoner_1";
		break;
		
		case "Knippel_prisoner_1":
			dialog.text = "何を企んでいるんだ、このろくでなしめ？俺の司令官とあの哀れなオランダ娘に何の用だ？";
			link.l1 = "チャーリー、お前の知ったことじゃない。もうお前は必要ない。立て。";
			link.l1.go = "Knippel_prisoner_2";	
		break;
		
		case "Knippel_prisoner_2":
			dialog.text = "俺を殺すつもりか？お前みたいなろくでなしにはお似合いだな。\nぺっ……くたばれ！";
			link.l1 = "起きろ、チャーリー。最後の祈りを捧げな。";
			link.l1.go = "Knippel_prisoner_3";	
		break;
		
		case "Knippel_prisoner_3":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
			pchar.quest.RemoveKnippelOver.over = "yes";//снять таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Knippel_officer":
			dialog.text = "おい、船長、チェーンショットで尻を撃たれたぜ！";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "俺の肝臓に大砲玉を食らわせてくれ、キャプテン。もう陸には二度と足を踏み入れねぇ。酒場でサイコロを振ってた最後の時、ろくでなしにポケットの中身を根こそぎ盗られちまったぜ。";
				Link.l1 = "ハハ、ギャンブルで全部失ったんじゃないのか、"+npchar.name+"？まあ、それはそれとして…話がしたかったんだ。俺はヨーロッパへ航海することにした — 他人の船の乗客としてな。いつ戻るかなんて分からねぇ。ここで俺を待つようには頼まねぇし、お前を無理に連れて行くつもりもねぇ。";
				Link.l1.go = "SharlieEpilog_Knippel_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "キニッペルさん、私は古代インディオの失われた都市タイアサルへ向かいます。はっきり言っておきますが、 これは非常に危険で、しかも普通じゃない旅です――この……魔法の偶像を通って行く必要があります。あなたも一緒に来てくれますか？";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "キニッペルさん、船について詳しい報告をしてくれ。";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "毎回寄港するたびに、特定の商品を購入してほしい。";
				Link.l12.go = "QMASTER_2";
			}
			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "ご命令どおり到着いたしました、船長。";
				Link.l2 = "あなたにいくつか命令を出さなければならない。";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Knippel_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "俺の命令を聞け！";
            Link.l1.go = "stay_follow";
			link.l2 = "たいしたことじゃない。解散！";
			link.l2.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "沈めてくれよ……大砲は問題ねえ、爆発したやつは交換して、火薬もちゃんと乾燥して安全に保管してるぜ。船長、 どんな報告を期待してたんだ？俺は年季の入った砲術士であって、会計係じゃねえんだ。チェーンショットだと？ 冗談じゃねえ、カリブ一の砲術士は俺だぜ、覚えときな！";
			Link.l1 = "ここで言い争うつもりはないよ、キニッペルさん、君が自分の仕事に長けているのは分かっている。\n会計係は自分で探すから、心配しないでくれ。";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "おい、チャーリーに砲甲板を捨てて艦橋に立てってのか？船長、俺は船を沈めるのが仕事で、 ペソ一枚ごとに値切るような真似はしねえ。しかも最初の植民地で絶対にカモられるに決まってるぜ。";
			link.l1 = "もちろんです、クニッペルさん。ちゃんとした会計士を探し始めるべきですね。";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "お話を伺いましょう。";
			Link.l1 = "これは拿捕の話だ。";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "これはあなたの船のことだ。";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "しばらく俺の艦隊から離れて、自分の力で運を試してきてほしい。";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "今のところ何もない。";
			Link.l8.go = "exit";
			break;

		case "Companion_TaskBoarding":
			dialog.Text = "それで、ご希望は何ですか？";
			Link.l1 = "敵船には乗り込むな。自分と乗組員の身を守れ。";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "敵船に乗り込んでほしい。";
			Link.l2.go = "Companion_TaskBoardingYes";
			break;

		case "Companion_TaskChange":
			dialog.Text = "それで、あなたの望みは何ですか？";
			Link.l1 = "できれば、乗船後に他の船と交換しないでほしい。君の船はあまりにも貴重だからな。";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "敵船に乗り込んだとき、もしまともな船なら自分のものにできるぜ。";
			Link.l2.go = "Companion_TaskChangeYes";
			break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "了解だぜ！";
			Link.l1 = "楽にしろ。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
			break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "承知いたしました。";
			Link.l1 = "楽にしろ。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
			break;

		case "Companion_TaskChangeNo":
			dialog.Text = "あいよ！";
			Link.l1 = "承知いたしました。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
			break;

		case "Companion_TaskChangeYes":
			dialog.Text = "承知いたしました。";
			Link.l1 = "楽にしろ。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
			break;
			//	<========////////////////////////////////////////

		case "stay_follow":
            dialog.Text = "ご命令は？";
            Link.l1 = "ここに立て！";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "俺について来い、遅れるなよ！";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "火器の弾薬の種類を変更する。";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "弾薬の種類を選択：";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
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
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "気配が変わったぞ！";
            Link.l1 = "下がれ。";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "態度が変わったぞ！";
            Link.l1 = "下がってよい。";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "「仕えている間に、私は本当にあなたに愛着が湧きました」 "+pchar.name+"、それに俺は船長を見捨てたりしねえ。地獄の底まででもついていくぜ。俺はあんたの味方だ！";
			link.l1 = "ありがとう、クニッペルさん！私の見立てが正しかったことを嬉しく思います。";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "いつ始めるんだ、ちくしょうめ？";
			link.l1 = "少し後だ。俺たちはそのための準備をしなきゃならねえ。";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "22");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Эпилог
		case "SharlieEpilog_Knippel_1":
			dialog.text = "さて、それは残念だな…装備に大砲玉を喰らわせちまうとはな。正直言って、ヨーロッパを見るのも悪くねぇと思ってるんだ。";
			link.l1 = "そんなことをお前から聞くとは思わなかったぜ。さて、『"+GetShipName("Ulysse")+"』のピナス船へようこそ。よければ、俺たちの昔の知り合い、リチャード・フリートウッドのところに顔を出してみるか？きっと言いたいことがあるだろうよ。";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "いや、閣下。リチャードなんて地獄へ落ちろだ。名前を聞くのも、ましてやその顔を見るのも御免だ。";
			link.l1 = "好きにしろ、"+npchar.name+"、好きにしろ。俺たちは2週間後に出航する。ちゃんとした別れの宴を開くつもりだ。お前も是非参加してくれ。";
			link.l1.go = "SharlieEpilog_Knippel_3";
		break;

		case "SharlieEpilog_Knippel_3":
			dialog.text = "いや、断るなら首が大砲玉で折れちまうぜ、キャプテン！";
			link.l1 = "いいだろう。じゃあ、他のことを片付けたら酒場で会おう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Knippel = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("あなたは "+GetSexPhrase("泥棒だ、旦那！衛兵、そいつを捕まえろ","泥棒だ、あの娘だ！衛兵ども、あいつを捕まえろ！")+"!!!","見てよ、これ！俺がちょっと目を離した隙に、君は俺の胸を漁ったな！泥棒を捕まえてくれ！！！","衛兵！強盗だ！泥棒を捕まえろ！！！");
			link.l1 = "くそっ！";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
