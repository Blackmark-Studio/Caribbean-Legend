// Эркюль Тонзаг, он же Плешивый Гастон
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
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
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "「やあ、こんにちは」 "+pchar.name+"。生きていてくれて嬉しいよ。";
				link.l1 = "「ガストン！お前か？」";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "「ごきげんよう」 "+pchar.name+"……もう君のやり取りについては知っている――ジョンが全部話してくれたよ。何と言えばいいのかわからない。君には感心するよ！";
				link.l1 = "あなたからそんな称賛の言葉を聞けて嬉しいよ、エルキュール！";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "こんにちは。何か私に頼みたい仕事でもございますか？";
			link.l1 = "いいえ。私の勘違いでした。すみません。さようなら。";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "その名前で俺を知ってたな。だが本当の名はエルキュールだ。エルキュール・トンザグだ。";
			link.l1 = "おお、聖なる主よ！私もお会いできて嬉しいです……戦いの最中であなたに気づきませんでした。ちょうど助けが必要な時に来てくださったのですね。";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "君が出発した直後、フリートウッドが自分の屋敷の警備を強化したという知らせを受け取ったんだ。\nそこに罠があるかもしれないと俺は考えた。すぐに自分の船『トワイライト』でアンティグアへ向けて出航した――そして今こうしているのも、理由があったというわけさ。";
			link.l1 = "そうだ。屋敷の中の護衛たちにはなんとか対処できたが、通りで戦い続けるにはあまりにも疲れ果てていたんだ……";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "この戦いの後、フリートウッドはオランダのスパイを指名手配リストに載せた。 奴らはお前をオランダのスパイだと思っていたんだ。彼は奴らと根深い確執がある。最悪だったのは、 屋敷にいた兵士が生き残って、お前の顔を覚えていたことだ。だが、もう問題じゃねえ。 お前が始めたことは俺が終わらせた。その兵士はもう誰の顔も見分けられねえし、誰も奴を見分けることはできねえ……";
			link.l1 = "殺したのか？そうか……";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "ああ。お前がジョンの家で気を失っている間に、俺はフリートウッドを傷つけてやったが、あの野郎は生き延びやがった。 奴の目に胡椒を投げつけて失明させてから、剣を抜く暇も与えずに殴りつけたんだ。だが、 あのクズは制服の下に鎖帷子を着てやがって――それで命拾いしたってわけだ。頭が回る奴だよ。今は家で警備を増やして寝込んでる。生き残ったのは本当に残念だぜ。";
			link.l1 = "それで、アンティグアでのお前の主な任務はフリートウッドを始末することだったのか？";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "概ねその通りだ。しかし今は無理そうだな。屋敷は常に施錠されていて、選りすぐりの衛兵が四六時中見張っているし、 彼に会えるのは唯一の側近だけ――昔からの砲手で「クニッペル」と呼ばれるチャーリーだけだ。\n";
			link.l1 = "それだけでも十分だな……";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "ちょっと待て……この件に首を突っ込むつもりか？";
			link.l1 = "なぜ駄目なんだ？手伝いはいらないのか？君が俺を助けてくれたんだ、だから俺も力になりたい。それに、 まだ金が必要なんだよ。";
			link.l1.go = "SJ_talk_6";
			// belamour legendary edition -->
			link.l2 = "なぜだ？あんたたちは真面目な連中だろう。\nそれに、真面目な連中は気前よく払うもんだ。\n俺はただ仕事を探してるだけさ。";
			link.l2.go = "SJ_talk_6a";
		break;
		
		case "SJ_talk_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			dialog.text = "信じてくれ、友よ、それは無理だ。お前はいい奴だし、本当に才能もある。 持ってきてくれた航海日誌のおかげでフリートウッド暗殺の計画も立てられた。衛兵の処理も見事だったぜ――だが、今となってはフリートウッドに近づくことは絶対にできねえ。俺でさえ、その方法がまったく分からねえんだ。";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "考えてみるよ。まだ時間はあるしな。船を奪われて、乗組員もいないのが残念だ。";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "そのことは考えておこう。時間も船もあるからな。";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_6":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "信じてくれ、友よ、それは無理だ。お前はいい奴で、本当に才能がある。 持ってきてくれた航海日誌のおかげでフリートウッド暗殺の計画も立てられた。衛兵の始末も見事だった――だが、今となってはフリートウッドに辿り着くことは絶対にできねえ。俺でさえ、 どうやればいいのか全く見当もつかないんだ。";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "考えてみるよ。まだ時間はあるしな。残念だが、俺の船は奪われて、乗組員もいねえんだ。";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "そのことは考えておこう。俺には時間も船もあるからな。";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "そのことは心配するな。お前のオンボロ船が拿捕されたとき、俺はお前の士官たちと何人かの水夫を自分の『 トワイライト号』に乗せておいた。連中はお前が生きていると知っていて、引き続き仕えることに同意してるぜ。\nそれに、航海日誌のお礼として、俺の船『トワイライト号』をお前に譲る。";
			link.l1 = "ありがとう！それは忘れないぞ！";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "はい、その日誌の代金をお支払いしたいです。1万5千ペソ――残念ながら今はこれ以上持ち合わせがありません。\n必ず一日以内に精算いたします。 ";
			link.l1 = "必要ない。これで十分だ。もし君が間に合わずに来なかったら、金なんて必要なかっただろうさ。";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "「よし、」 "+pchar.name+"、俺は行かなくちゃならねえ。まだブリッジタウンには戻らないぜ。もし俺が必要になったらジョンに頼め。幸運を祈る！ ";
			link.l1 = "幸運を祈るぜ、エルキュール！";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			DialogExit();
			AddDialogExitQuestFunction("HollandGambit_NewShipTwilight");
		break;
		
		case "SJ_talk_11":
			dialog.text = "フリートウッドを始末してくれた礼として、この鎧を贈りたい。今後の戦いでお前を守ってくれるだろう。\nさあ、今ジョンに会いに行こう。彼はお前に話があるし……面白い提案を持っているらしいぞ。";
			link.l1 = "贈り物をありがとう。よし、行こう…";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");//дать вещь
			sld = characterFromId("Merdok");
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "俺もあんたと話したいんだ、船長。俺が自分の技を教えようと思ってたが、 今じゃ逆にあんたから学ぶべきだと分かったぜ。俺をあんたの船の士官として雇ってくれ――絶対に後悔はさせねえよ。";
			link.l1 = "喜んでだぜ、エルキュール！乗組員へようこそ！";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "エルキュール、私があなたの上司になるなんて想像できません。\nご提案はありがたいですが、どうしてもあなたを部下として見ることはできません。";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1":
			ForceHeroAutolevel(npchar);//Тонзага - в офицеры
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			LAi_SetImmortal(npchar, false);
		
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "かしこまりました "+pchar.name+"。では、また会おう。再びお目にかかることもあるかもしれないな。君と一緒に仕事ができて楽しかったよ。";
			link.l1 = "幸運を祈るぜ、友よ！";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "tonzag_officer":
			dialog.text = "お話を伺いますよ、船長。何かご用ですか？";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "Hai un’aria piuttosto cupa, capitano. È successo qualcosa?";
				Link.l1 = "Devo lasciare l’arcipelago. Tra due settimane. Su una nave altrui, come passeggero.";
				Link.l1.go = "SharlieEpilog_Tonzag_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "エルキュール、俺はこれから古代インディオの都市タイアサルへ行くんだ。しかも、もっと珍しいことに、 道中には転送の像を通ることになる。お前も一緒に来るか？";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "エルキュール、船について詳しく報告してくれ。";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "私たちが寄港するたびに、特定の商品を必ず購入してほしい。";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "ご命令どおりに参りました、船長。";
				Link.l2 = "あなたにいくつか命令を出さなければならない。";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "tonzag_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "俺の命令を聞け！";
            Link.l1.go = "stay_follow";
			link.l2 = "今は何もない。楽にしていろ！";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "船長、申し訳ありませんが、私は数字や計算には関わっておりません。 そういうことならファン・メルデンに聞いてください――あいつはそういうのが得意ですが、自分の巣から出る気はないでしょうね。";
			Link.l1 = "お前の言う通りだな、エルキュール。ふう、俺も会計係でも探さねえとな…";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "船長、俺がバルバドスで宿屋をやってた時は、ラム酒と食料しか仕入れてなかったんだ。食料ってのは、 ちゃんとした飯のことだぜ、乾パンやコンビーフだけじゃなくてな。悪いが、それは俺の担当じゃねえんだ。";
			link.l1 = "もしかして俺の船を酒場にでもするか……冗談だよ、エルキュール。まあいい、自分でやるさ。";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "お話を伺いましょう。";
			Link.l1 = "これは拿捕の話だ。";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "これはあなたの船のことだ。";
			Link.l2.go = "Companion_TaskChange";
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
			Link.l1 = "乗船後に他の船と交換するのはやめてほしい。あの船は貴重すぎるんだ。";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "敵船に乗り込んだ時、もしまともな船なら自分のものにできるぜ。";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "アイアイ。";
			Link.l1 = "楽にしてくれ。";
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
			dialog.Text = "アイアイ。";
			Link.l1 = "承知いたしました。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "承知いたしました。";
			Link.l1 = "楽にしてくれ。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		
		case "stay_follow":
            dialog.Text = "ご命令は何でしょうか？";
            Link.l1 = "ここにいろ！";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "俺について来い、遅れるんじゃねえぞ！";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "弾薬の種類を変更しろ。";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "弾薬の種類の選択：";
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
            dialog.Text = "おう！";
            Link.l1 = "楽にしていいぞ。";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "ああ！";
            Link.l1 = "楽にしろ。";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "お前は運のいい野郎だな、船長。俺がお前とジョンと一緒に働いてた頃に仲間になれてよかったぜ。今回の仕事、 俺が応援しなかったらサメに食われてもいいぜ！";
			link.l1 = "ありがとう、エルキュール！君のことを信じて正解だったよ。";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "それで、いつ出発するんだ？";
			link.l1 = "少し後だ。今は旅の準備をしよう。";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "ほとんど何もわからねえな、船長。もしこれが俺たちの仕事に関係してたら、とっくに拷問台に乗せられてたはずだぜ。\nすぐに尋問に連れていかれなかったってことは、どうやら急ぎの用事じゃねえらしい。\n罠か、ゆすりかのどっちかだろうな。\n何の説明もなく、ここで何日か放置されるだろうさ。それから向こうが条件を持ってくる――俺たちはそれを呑むしかねえってわけだ。";
			link.l1 = "個人的な経験か？";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "さて、今すぐそんな申し出で彼らを呼び寄せる方法はあるのか？";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-14.82, 0.92, 2.74, true, -60.00, -5.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "もちろんだ。グルオーはかつて、死んだ男の親族から金をもらい、トリニダードの死刑執行人の「別れの抱擁」 から救ったことがある。\n彼女は留置房を歩く権利を得るために司令官に金を払った。よくあることさ――多くの者が、反撃できない囚人を証人なしで痛めつける機会を兵士に金で買っているのさ。\nその男は静かに、苦しまずに死んだ。清潔でまともな仕事だったよ。";
			link.l1 = "グルオ？それは誰だ？";
			link.l1.go = "tonzag_jailed_1_1";
		break;
		
		case "tonzag_jailed_1_1":
			dialog.text = "悪いな、船長。場所もタイミングも最悪だったぜ。";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "やってみようか。餌の時間まで待って、見張りとちょっと話をしてみるよ。あいつら、 まだちゃんと捜索するやり方を覚えてねえんだ。ええ…";
			link.l1 = "「どうした？」";
			link.l1.go = "tonzag_jailed_2_1";
		break;
		
		case "tonzag_jailed_2_1":
			dialog.text = "妙な感じだな、船長。予感とでも言うべきか。すまねえ、また後で話そう。";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_killed_hunters":
			dialog.text = "「何か見逃しましたか、船長？」";
			link.l1 = "ああ、特に変わったことはないさ、ただの海の一日だ。\nおいおい、見ろよ、この悪党め！お前のおかげでここはすっかりめちゃくちゃじゃねえか。";
			link.l1.go = "tonzag_killed_hunters_1";
		break;
		
		case "tonzag_killed_hunters_1":
			dialog.text = "血は冷たい水で落ちますよ、船長。話が必要です。";
			link.l1 = "そう思うか？まずは今日を生き延びてみるのも悪くないだろう。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_Victory");
		break;
		
		case "tonzag_after_victory_helena":
			dialog.text = "俺も会えて嬉しいぜ、ルンバ。船長、今は邪魔しねえよ、また後で話そう。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog1");
		break;
		
		case "tonzag_after_victory_mary":
			dialog.text = "「よう、ジンジャー。船長、邪魔はしねえよ、また後で話そう。」";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog1");
		break;
		
		case "tonzag_after_victory_alonso":
			dialog.text = "船長、お邪魔はしません、また後で話しましょう。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_drink":
			dialog.text = "俺の話を聞く準備はできたか、船長？";
			link.l1 = "そろそろ話をしようじゃないか、エルキュール。今さら気づいたんだが、俺はお前のことをほとんど何も知らないんだ。";
			link.l1.go = "tonzag_drink_1";
		break;
		
		case "tonzag_drink_1":
			dialog.text = "さて、そろそろ自己紹介といこうか。幼少期の話は飛ばそう。どうせ語ることなんてないからな――勝った兵士、負けた兵士、脱走兵、略奪者……まあ、よくある話だろう。";
			link.l1 = "実はそうでもないけど、今のところ特に変わった話には聞こえないな。";
			link.l1.go = "tonzag_drink_2";
		break;
		
		case "tonzag_drink_2":
			dialog.text = "このような軍歴を経た俺に残された出世の道は少なかった――盗賊、絞首刑の死刑囚、あるいはオランダ西インド会社にふさわしい用心棒くらいなもんだ。\nわかるだろうが、俺は最後の道を選んだのさ。";
			link.l1 = "「そこからも脱走したのか？」";
			link.l1.go = "tonzag_drink_3";
		break;
		
		case "tonzag_drink_3":
			dialog.text = "逆に、そこで出世したんだ。会社の諜報部戦闘班に入るよう誘われて、そこで将来の妻と出会ったんだ。";
			link.l1 = "さて、今のところ物語はかなり穏やかだな……特にオランダ人のやり方についてあまり深く考えなければ、だけどな。";
			link.l1.go = "tonzag_drink_4";
		break;
		
		case "tonzag_drink_4":
			dialog.text = "正直にやっても大した金にはならねえし、競争相手の扱い方はいろいろある。ああ、 俺たちは特別なやり方で動いてたんだ……";
			link.l1 = "おっしゃりたいことは、なんとなく分かります……";
			link.l1.go = "tonzag_drink_5";
		break;
		
		case "tonzag_drink_5":
			dialog.text = "ああ、何でもありだったさ。海賊行為から商品でいっぱいの倉庫に火をつけることまでな。結局、計画はバレて、 俺たちは解散させられた……まあ、書類の上だけの話だがな。そうしてリーグが生まれたんだ。会社の上層部の選ばれた指導者だけが知り、 支配する組織さ。カリブの一人前の無法者にとっては、選択肢は二つしかなかった――海賊かリーグか。そしてたいていの場合、リーグの方が稼げたぜ\n大体は今でもリーグはオランダ人のために働いてるが、時には横の仕事も引き受けることがあるんだ…";
			link.l1 = "物事がだんだんはっきりしてきたな……";
			link.l1.go = "tonzag_drink_6";
		break;
		
		case "tonzag_drink_6":
			dialog.text = "あのトルトゥーガでの茶番劇の黒幕はリーグだったんだ。\nそれに、あの上陸部隊も……";
			link.l1 = "そうだと思ったよ。でも、なぜだ？";
			link.l1.go = "tonzag_drink_7";
		break;
		
		case "tonzag_drink_7":
			dialog.text = "誰もリーグから生きては出られないし、俺たちがあそこでやったことを無傷で逃げ切れるわけがねえんだ、船長。 俺は引退したかったから、無理だと分かってても試してみた。見ての通り、あまりうまくはいかなかったがな。";
			link.l1 = "「お前の元同僚たちが莫大な金を使い、百人近くを捨て、火船まで燃やし、軍艦まで危険にさらしてまで……脱走したお前を殺すためだけにやったって言うのか？」";
			link.l1.go = "tonzag_drink_8";
		break;
		
		case "tonzag_drink_8":
			dialog.text = "俺はリーグじゃただの小物じゃなかったんだ、船長。あそこについては知りすぎてる。 やつらは俺を簡単に逃がしちゃくれねえし、それを他の連中にも見せつけて、 誰も抜けようなんて思わないようにしなきゃならねえ……前にも俺を狙ってきたことがある、ずいぶん昔にな……あいつらは俺の妻を殺し、俺の顔を潰した。自分たちも大きな代償を払ったのにな。それでも、 この話にハッピーエンドなんてねえんだよ、船長。命令してくれりゃ、俺は船を降りて、 最後にもう一度あいつらと向き合うぜ。";
			link.l1 = "馬鹿なことを言うな、エルキュール……それで、この一件にルーカス・ローデンブルクはどんな役割を果たしたんだ？奴も絶対に関わっていたはずだ！お前……いや、奴の“組織”、リーグのことだ……";
			link.l1.go = "tonzag_drink_9";
		break;
		
		case "tonzag_drink_9":
			dialog.text = "別々の組織だよ、船長。ただ、確かに彼らはしばしば同じ人物に従い、密接に協力していた。 でもローデンブルクの特務員たちは正確で効果的な一撃を加え、リーグは大規模な作戦を実行していたんだ。そして今、 リーグはどうなった？ご覧の通り、もう組織は存在しない。俺はここにいて、ジョン・マードックは去り、 ロンウェイは逃げ出し、ヴァン・ベルクは海の底、ローデンブルクは処刑された……それでも、あの死んだ悪党には借りがあった。リーグ時代に俺を見出してくれて、 抜けようとした時に大きなトラブルから救い出し、副官にしてくれたんだ。当然、他の連中は気に入らなかったが、 誰も彼に逆らう勇気はなかった……そして、例の事情で、彼はマードックと俺を始末しようと決めたが、あんたが介入して俺を自分の部下にした\nそれで俺は思ったんだ――『これが過去と決別する二度目のチャンスだ』って……あんたはローデンブルクを出し抜き、リーグは後ろ盾を失い、もう危険はない……だが、もちろん俺は間違っていた……年寄りの愚かさだよ……まあ、その話はもういい、船長。次にどうするか考えようじゃないか。もちろん、 最初の港で俺を放り出すつもりが本当にないなら、だが。";
			link.l1 = "私にはありません。あなたに何か策があるのですか？";
			link.l1.go = "tonzag_drink_10";
		break;
		
		case "tonzag_drink_10":
			dialog.text = "別に特別なことじゃないさ。奴らを完全に殲滅することは無理だが、こっちが大損害を与えれば、もう俺……いや、俺たちを追い続ける価値なんてなくなるだろう。\n";
			link.l1 = "「それで、どうやってやるんだ？あいつらの野営地でもあるのか？」";
			link.l1.go = "tonzag_drink_11";
		break;
		
		case "tonzag_drink_11":
			dialog.text = "大きな要塞？まさか。そんなものは同盟にとって目立ちすぎて危険だ。\nそれに、俺が言う「損失」は人間の損失じゃねえ――あいつらは人命なんて気にしちゃいないが、金を失うのは面白くないだろう。\n会社からの金はもう入ってこないんだろ？同盟が新しい後ろ盾を見つけたとも思えねえし、 どこか別のところから無理やり金をかき集めてるに違いねえ。";
			link.l1 = "「それはどこだ？」";
			link.l1.go = "tonzag_drink_12";
		break;
		
		case "tonzag_drink_12":
			dialog.text = "わかりません、船長。";
			link.l1 = "エルキュール、お前はさっき、自分が追われているのは知りすぎているからだと言ったじゃねえか！";
			link.l1.go = "tonzag_drink_13";
		break;
		
		case "tonzag_drink_13":
			dialog.text = "考えさせてくれ……今はリーグがスペイン人相手に動いているかもしれねえな。奴らは一発かましてやるのにうってつけの連中だ。\nそういえば、ローデンブルクはカスティーリャの金持ちどもといつも仲が良かったんだ。時々 リーグの連中をそっちの仕事に回したりして、絶対に手出しするなって命じてた。ちなみに、 それが気に入らねえ奴も多かったぜ……";
			link.l1 = "「良好な関係だと？じゃあ、あんたのために俺が酒場まで引きずってきた、あのイダルゴとその指はどうなるんだ？」";
			link.l1.go = "tonzag_drink_14";
		break;
		
		case "tonzag_drink_14":
			dialog.text = "あれは特別な案件、いわば追加注文だった。罪悪感があるなら安心しな、船長――あのドンは自業自得さ……だが俺が言いたいのは別のことだ。雇い主が消えた後、 リーグの連中は欲望のままにスペインの取り分をがっつり奪いに行くこともできたはずだ。 ローデンブルクの下でスペイン人と組んだおかげで、どこで何を奪えばいいか、やつらはよく知ってるんだ。";
			link.l1 = "ふむ……お前の言うことも一理あるな。だが、俺の知る限り、スペインの銀行に本気で押し入る奴なんていねえし、 海でスペイン人相手にやるのは運任せだ……。\nスペインの事業でも探してみるか？工場とかよ。";
			link.l1.go = "tonzag_drink_15";
		break;
		
		case "tonzag_drink_15":
			dialog.text = "もっともな推測ですね、船長…。他に手がかりはありますか？";
			link.l1 = "ふむ……今日俺たちを襲った船は南へ向かったな……";
			link.l1.go = "tonzag_drink_16";
		break;
		
		case "tonzag_drink_16":
			dialog.text = "あの船長がもう一度俺たちにちょっかいを出してくることはなさそうだが、 計画通りにいかなかったことを仲間に伝えたり、乗組員を別の場所に移すかもしれねえ。\n他に何かあるか？";
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.KnowMain")) {
				link.l1 = "ああ、トルトゥーガの監獄司令と親しく話したよ…本土について何か言っていたな。";
				link.l1.go = "tonzag_drink_know";
			} else {
				link.l1 = "いいえ、他には何もありません。";
				link.l1.go = "tonzag_drink_notknow";
			}
		break;
		
		case "tonzag_drink_know":
			dialog.text = "素晴らしいですね、船長！南、本土、スペイン人――つまり、すぐに見つかるはずだ。出航しますか？それと、俺の話を聞いてくれてありがとう。";
			link.l1 = "ああ、君と俺でずいぶん腹を割って話したもんだな……さあ、出航しようぜ！";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_drink_notknow":
			dialog.text = "手がかりはあまりないな。だが、俺たちみたいな連中にはそれで十分だろう。南へ向かうか？ スペインの交易会社でも探してみるか？俺の話を聞いてくれて、ありがとうよ。";
			link.l1 = "ああ、俺たち、ずいぶん腹を割って話しちまったな……さあ、出航しようぜ！";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_dead":
			dialog.text = "見てください、船長。あいつらはこうやって動くんです。";
			link.l1 = "「お前もそんなふうに働いてたのか？」";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "行こう、中に何があるか見てみよう。";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_AfterDead");
		break;
		
		case "tonzag_afterminefight":
			dialog.text = "汚らしい事件だな、船長。この巣窟は片付けたが、これが最後ってわけじゃねえ……";
			link.l1 = "鉱山はどうしたんだ、エルキュール！？外にいた人たちは！？あいつらも“片付けられた”のか！？それに、あのろくでなしは何を言いたかったんだ？\n";
			link.l1.go = "tonzag_afterminefight_1";
		break;
		
		case "tonzag_afterminefight_1":
			dialog.text = "この話は後にしましょう、船長。敵の指揮官は生き残っています、尋問が必要です。";
			link.l1 = "「もし彼が何も知らなかったらどうする？」";
			link.l1.go = "tonzag_afterminefight_2";
		break;
		
		case "tonzag_afterminefight_2":
			dialog.text = "あいつは何か知ってる。考えてみろ――奴らは俺たちを待ち構えていて、金を全部運び出し、証人も消した。つまり計画的だったってことだ。 俺はここを少し調べてみたいし、後で自分であの悪党を船に連れていくつもりだ。お前も周囲に気を配っておけ。 もしかしたら、奴らは急ぎすぎて何か見落としているかもしれない。\n";
			link.l1 = "わかった、でも船に戻ったら、ちゃんと話し合わなきゃならないぞ！";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			locations[FindLocation("LosTeques_town")].locators_radius.reload.gate_back = 1.0;
			DeleteAttribute(&locations[FindLocation("LosTeques_town")], "locators_radius.reload.reload1_back");
			AddDialogExitQuestFunction("Tonzag_PrepareJournal");
		break;
		
		case "tonzag_in_hold":
			dialog.text = "「良い知らせです、船長。」";
			link.l1 = "俺たちの状況にいいことなんて何も見えねえな、エルキュール。\n行こう、二人きりで話す必要がある。";
			link.l1.go = "tonzag_in_hold_1";
		break;
		
		case "tonzag_in_hold_1":
			dialog.text = "そういうことか、あんた。ああ、船長。";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_EnterAlonso");
		break;
		
		case "tonzag_drink_again":
			dialog.text = "これは本気の話になりそうですね、船長。";
			link.l1 = "ああ、そうだ、話すのは俺だ。まず最初に、何か傾向が見えてきてると思わねえか？ どこへ行っても死体の山が俺たちの後をついてきてるじゃねえか！最初はお前がぶどう弾を腹に食らい、 その翌日には百人以上――善人も悪人も――が死んだ…あれは海戦なんて呼べるもんじゃねえ！数日前には入植地が消し飛ばされ、そして今日は俺たちが鉱山で大勢ぶっ殺して、 その山にまた死体を積み上げたってわけだ。";
			link.l1.go = "tonzag_drink_again_1_1";
		break;
		
		case "tonzag_drink_again_1_1":
			dialog.text = "";
			link.l1 = "もちろん、明日にはこの山がさらに大きくなるかと思うと不安だが、何よりも恐ろしいのは、 これだけの血がたった一人のせいで流されているという事実だ。 そしてその人物は俺の船の中で重要な地位についているんだ！";
			link.l1.go = "tonzag_drink_again_1";
		break;
		
		case "tonzag_drink_again_1":
			dialog.text = "";
			link.l1 = "二つ目だが、お前は俺に嘘をついたな、エルキュール。脱走兵一人のために、 お前の元同僚たちがそこまで必死になるわけがねえ。鉱山で囚人が叫んでたのは何だ？裏切り者？ポルトベロ？ グルオッホ？お前、何かやったんだろう、エルキュール。今度こそ本当のことを聞かせてもらうぞ。";
			link.l1.go = "tonzag_drink_again_2";
		break;
		
		case "tonzag_drink_again_2":
			dialog.text = "真実か？真実を言うとだな、船長、俺は妻のグルオーと一緒に脱走したんだ。トンザグ夫人はリーグを離れたくなかった――あの暮らしを愛していたが、俺のことはそれ以上に愛してくれた。俺たちはスペインのイダルゴを始末する役目だったが、 あいつがもっといい条件を出してきたんだ。それがチャンスだったから、二人でその男に仕えることに決めた。当然、 リーグは俺たちが任務中に死んだと思い込んで、復讐と仕事の仕上げのために第二の部隊をポルトベロへ送り込んだのさ。 ";
			link.l1 = "「それで、全部殺したのか？」";
			link.l1.go = "tonzag_drink_again_3";
		break;
		
		case "tonzag_drink_again_3":
			dialog.text = "まず、奴らはグルオを殺し、俺の顔を潰した。\nそれで、あのイダルゴはもう俺に関わりたくないと言って、俺を追い出したんだ。\nその時にローデンブルクが俺を見つけてくれた……";
			link.l1 = "「それで、今さらどうやってお前を信用しろって言うんだ？軍隊を捨て、同盟を捨て、仲間まで殺したじゃねえか！ いざという時には、俺のことも裏切るつもりなんじゃないのか？」\n";
			link.l1.go = "tonzag_drink_again_4";
		break;
		
		case "tonzag_drink_again_4":
			dialog.text = "ああ、俺は脱走したし、契約も破ったし、リーグの連中を二十人ほど殺した。だが、その教訓はもう身に染みてるぜ、 船長。それに、死人は誰も裏切れねえしな。俺はもうずっと前、ポルトベロ以来、死んだも同然なんだ。 だから今の俺を殺すのが、こんなにも難しいのかもしれねえな。";
			link.l1 = "今日はもう十分だ。まだ何か隠している気がするぞ。";
			link.l1.go = "tonzag_drink_again_5";
		break;
		
		case "tonzag_drink_again_5":
			dialog.text = "囚人のことは俺が自分で片付けるぜ、あるいはお前も一緒にやりたいのか？";
			link.l1 = "行こう。俺が自分で尋問する。";
			link.l1.go = "tonzag_drink_again_hold";
			link.l2 = "いや、そういうことは俺の役目じゃねえ。三十分後に俺の船室で会おう！";
			link.l2.go = "tonzag_drink_again_cabin";
		break;
		
		case "tonzag_drink_again_hold":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToHold");
		break;
		
		case "tonzag_drink_again_cabin":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin");
		break;
		
		case "tonzag_hold":
			dialog.text = "今は誰が仕切ってるんだ？アルノか？";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog1");
		break;
		
		case "tonzag_hold_1":
			dialog.text = "あのクズが権力を握ったのか？お前たちもすぐにただの盗賊団に成り下がったじゃねえか……";
			link.l1 = "「オースティンって誰だ？」";
			link.l1.go = "tonzag_hold_2";
		break;
		
		case "tonzag_hold_2":
			dialog.text = "オースティンの一味は、自由船長たちを森の奥へと誘い込み、 バラバラにして死体から金や小物をきれいに奪い取ることで有名だった。いい稼ぎだったし、 冒険好きは後を絶たなかったから誰も気にしなかった。だが、ある船長でしくじってしまい、 そいつは仲間ごと会社の庇護下に入る羽目になった。俺たちはそいつに首輪をつけ、 手早く簡単に問題を片付けたいときだけ解き放っていたんだ。";
			link.l1 = "あんな人物と取引の交渉ができるとは思えません。";
			link.l1.go = "tonzag_hold_3";
		break;
		
		case "tonzag_hold_3":
			dialog.text = "間違いないな。あいつとその仲間が今仕切ってるなら、リーグもすぐにただのならず者集団になるだろう。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog3");
		break;
		
		case "tonzag_after_hold":
			dialog.text = "面白い会話だったな。";
			link.l1 = "それがどこまで本当なのか知りたいんだが……ポルトベロでの虐殺はどうなんだ？もしあいつが嘘をついていなかったなら、前回お前と話したときも、 またしてもお前の輝かしい経歴からいくつか重要な事実を省いていたことになるな。";
			link.l1.go = "tonzag_after_hold_1";
		break;
		
		case "tonzag_after_hold_1":
			dialog.text = "ポルトベロは暑かったんだ、船長。俺は自分の命のため、雇い主の命のため、妻の命のために戦った。 死者の数なんて数えてる暇もなけりゃ、たまたま通りにいた農民一人一人を悼んでる余裕もなかったぜ。";
			link.l1 = "その優先順位で？";
			link.l1.go = "tonzag_after_hold_2";
		break;
		
		case "tonzag_after_hold_2":
			dialog.text = "いや、もちろん違う。彼女のが先だ。いつだってそうさ。";
			link.l1 = "どう思う？カラカスへ行くべきか？";
			link.l1.go = "tonzag_after_hold_3";
		break;
		
		case "tonzag_after_hold_3":
			dialog.text = "私なら絶対に行きませんよ、船長。それに、あなたにもやめておいた方がいいと忠告します。リーグにとって、 あなたはもはや敵ではありませんし、私も少なくとも今はあなたの配下である限り、彼らにとって興味の対象外です。 それに、どうも胸騒ぎがして仕方ありません\nあそこへ行けば、ひどいことになります。本当に、ひどいことに。この話にハッピーエンドはありません。でも、 最後までお供しますよ、船長。";
			link.l1 = "考えておく。";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_hold_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_hold_4":
			dialog.text = "";
			link.l1 = "ところで、お前の言った通りだ――鉱山の掃除がちゃんとできてなかったぜ。見てみろ。";
			link.l1.go = "tonzag_after_hold_5";
		break;
		
		case "tonzag_after_hold_5":
			dialog.text = "士官の日誌か……暗号化されているが、古い暗号だ、俺は知ってるぞ\nどうやら面白いことは書いてないな。囚人のやつの日誌だったみたいだ。なぜあいつがあんなにあっさり口を割ったのか、 これで分かったぜ。見ろよ――隠された財宝の手がかりがある！あの野郎、引退するつもりで、いつでも逃げ出せるように準備してやがったんだな！";
			link.l1 = "「それで、その隠された場所はどこなんだ？」";
			link.l1.go = "tonzag_after_hold_6";
		break;
		
		case "tonzag_after_hold_6":
			dialog.text = "あの島のことは知っているだろう、船長。その海域でお前はヴァン・バードを仕留めたんだ。";
			link.l1 = "よし、そんなに遠くないから、ちょっと見に行こう。\nカラカスについてはまだ決めてないけど、たぶん一ヶ月は余裕があると思う。";
			link.l1.go = "tonzag_after_hold_7";
		break;
		
		case "tonzag_after_hold_7":
			dialog.text = "かしこまりました、船長。最後までお供いたします。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_after_drink":
			dialog.text = "終わりました、船長。オースティンは今カラカスにいます。おそらく一ヶ月は猶予があるでしょう。";
			link.l1 = "まずは順番だ。囚人は何と言った？このオースティンって誰だ？それに、なぜカラカスへ行かなきゃならないんだ？";
			link.l1.go = "tonzag_after_drink_1";
		break;
		
		case "tonzag_after_drink_1":
			dialog.text = "オースティンの一味は、自由船長たちを荒野に誘い込み、切り刻んで死体から金や小物を根こそぎ奪うことで有名だった。 いい稼ぎだったし、冒険好きは後を絶たなかったから、誰も気にしなかった。\nだが、ある船長で手こずったせいで、奴は仲間ごと会社の庇護下に入る羽目になった。俺たちは奴に首輪をつけ、 手っ取り早く問題を片付けたい時だけ解き放つことにしたのさ。";
			link.l1 = "あんな人物と取引の交渉ができるとは思えません。";
			link.l1.go = "tonzag_after_drink_2";
		break;
		
		case "tonzag_after_drink_2":
			dialog.text = "それは間違いないな。あいつとその手下どもが仕切るようになったら、リーグもすぐにただのならず者集団になるだろう。 でも、カラカスには行かない方がいいぜ、船長。";
			link.l1 = "本気か？怖いのか？";
			link.l1.go = "tonzag_after_drink_3";
		break;
		
		case "tonzag_after_drink_3":
			dialog.text = "そうじゃねえんだ、船長。囚人は死ぬ前に、あんたがもうリーグの敵じゃねえって言ったんだ。俺のことも、 少なくとも今はあんたの下で働いてる間は興味ねえらしい。リーグには新しい有力な後ろ盾ができて、 俺たちに手を出すなって命令したみたいだ。\nそれとカラカス……胸の奥がざわつくんだよ……あそこに行ったらヤバいことになる。とんでもなく悪いことが起きる。この話にハッピーエンドなんてねえ。でも、 最後まであんたと一緒にいるぜ、船長。";
			link.l1 = "考えておこう。もちろん、この件を一度で解決したいところだが、君の言う通りかもしれない。先週の出来事の後で、 やつらがもう一度近づいてくるとは思えないな。";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_drink_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_drink_4":
			dialog.text = "";
			link.l1 = "ところで、お前の言った通りだったぜ――鉱山の掃除がちゃんとできてなかった。見てみろ。";
			link.l1.go = "tonzag_after_drink_5";
		break;
		
		case "tonzag_after_drink_5":
			dialog.text = "士官の日誌か……暗号化されているが、古い暗号だ、俺は知ってるぞ\nどうやら面白いことは書いてないな。これはあの囚人の日誌だったんだ。ここを見ろ――隠された財宝の手がかりがある！あのろくでなし、引退するつもりで、 いつでも逃げ出せるように準備してやがったんだな！";
			link.l1 = "「で、その隠し場所はどこだ？」";
			link.l1.go = "tonzag_after_drink_6";
		break;
		
		case "tonzag_after_drink_6":
			dialog.text = "あの島のことは知っているだろう、船長。あの海域でヴァン・バードを仕留めたじゃないか。";
			link.l1 = "よし、そんなに遠くないし、ちょっと見に行こう。カラカスについてはまだ決めてないけど、 ひと月くらい余裕があると思う。";
			link.l1.go = "tonzag_after_drink_7";
		break;
		
		case "tonzag_after_drink_7":
			dialog.text = "かしこまりました、船長。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_church":
			dialog.text = "待ってくれ、船長。俺が一人で行く。";
			link.l1 = "それはなぜだ？今さら英雄気取りか？もう遅いぜ、お前がこの厄介ごとを起こしたんだが、 俺たちで一緒に片付けるしかねえんだ。";
			link.l1.go = "tonzag_church_1";
		break;
		
		case "tonzag_church_1":
			dialog.text = "俺の失敗の尻拭いをしてもらう必要はねえよ、船長。あんたの言う通りだ――俺が行く先々で人が死に、罪もねえ血が流れるんだ。\nもし一緒にあの教会に入れば、またポルトベロの二の舞になる。そんなことはごめんだぜ。";
			link.l1 = "「そこで本当は何が起きたんだ？」";
			link.l1.go = "tonzag_church_2";
		break;
		
		case "tonzag_church_2":
			dialog.text = "虐殺だった。俺は引退したかったんだ、船長。金と妻を連れてカルカソンヌの故郷に帰りたかった。 リーグが俺の仕事を片付けるためにさらに人を送り込むのは分かっていたから、 新しい後ろ盾からたっぷり前金をもらったんだ。あとは街の衛兵を昔の仲間と新しい雇い主にけしかけるだけだった。 その混乱に紛れて金と共に姿を消すつもりだったし、 もし時間があればポルトベロの太った連中を何人かくすねてやろうとも思っていた。";
			link.l1 = "いい考えだが、俺なら別のやり方をしたぜ。うまくいかねえことが多すぎるからな。";
			link.l1.go = "tonzag_church_2a";
			link.l2 = "俺も聖人じゃねえが、お前のやり口にはさすがの俺もゾッとするぜ。リーグやイダルゴ、 果ては自分の女房まで裏切ったくせに、まだ俺を裏切ってねえのが不思議なくらいだ。";
			link.l2.go = "tonzag_church_2a";
		break;
		
		case "tonzag_church_2a":
			dialog.text = "考えうる限りのことがすべて悪い方へ転がったんだ。三ポンド砲を総督の宮殿に向けて撃ったのは間違いだった。 総督本人にはかすり傷程度だったが、噂によれば、あの美しい娘は命を救うために両脚を膝下から切断されたそうだ。 報復は凄惨だった――まさに血の海、多くの人々が死んだんだ、船長。今こうしてあんたが見ているのは、その出来事の最後の生き証人だ。 そしてつい最近、あんた自身がもう一人を斬り捨てたんだぞ。";
			link.l1 = "説明しろ。";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_2b":
			dialog.text = "もしトンザグ夫人がまだ生きていたら、俺はためらわずにあんたを裏切っていただろう、船長。 俺はもう死んだも同然の人間で、この世に居場所がないからあんたについてきてるだけだ。\n今、あんたはその出来事の最後の生き証人を見ているんだ。そしてつい最近、 もう一人の証人をあんた自身の手で斬り捨てたばかりじゃないか。";
			link.l1 = "説明しろ。";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_3":
			dialog.text = "申し訳ありません、船長、道中ですべてをお話ししなかったことをお許しください。最初にお会いしたとき、 あなたも私と同じただの悪党だと思っていました。そして、私が最初にしたことが何かご存じですか？ 私はあなたに自分の尻拭いをさせたのです――最初は殺したくなかったスペインのドンを殺すように命じ、その後で裏切ることにしたのです。あのイダルゴ、 ロドリゲスのことですよ……";
			link.l1 = "「それで、あいつの指が何のために必要だったんだ？」";
			link.l1.go = "tonzag_church_4";
		break;
		
		case "tonzag_church_4":
			dialog.text = "ここに裏はない。ただの試験だ、船長。俺たちは毎年お前みたいな若いならず者を何十人も雇うが、 基本的な誠実さの審査を通るのはほんの一握りだし、そいつらも最初の作戦で死ぬんだ。 フリートウッドの航海日誌を持ち帰る作戦で、お前が生き残るとは思ってなかった。俺はただ屋敷に入って、 生き残りを始末し、航海日誌を奪うつもりだったんだ。";
			link.l1 = "私の記憶が正しければ、話は少し違う展開になったはずだ。";
			link.l1.go = "tonzag_church_5";
		break;
		
		case "tonzag_church_5":
			dialog.text = "そうだ、その通りだ、船長。なぜお前を助けようと思ったのか自分でも分からねえが、 お前がフォックスどもと命懸けで戦う姿を見て、俺まで一時的にその熱に当てられちまったんだ。結局のところ、 お前は知らず知らずのうちに俺を救ってくれた。お前は俺に何の借りもねえ、船長。だからここから先は通さねえ。 これは俺の問題、俺自身の贖罪だ。";
			link.l1 = "お前の望み通りだ、エルキュール。こんな戦士を失うのは痛いが、お前はもうずっと前に自分を失っていたし、 これ以上血を流す価値もない。俺にももう借りはないし、あの小さな教会で贖いを見つけられることを願っているぜ。";
			link.l1.go = "tonzag_church_bad";
			link.l2 = "いい演説だな、エルキュール。地獄に落ちろ！気づいてないかもしれないが、 お前の問題は最近俺の問題にもなってるんだ。お前は俺の部下だ、許すかどうか決めるのは俺だけだぜ。 だからもう少し俺たちと一緒にいて、俺の船の一員として武勇で償いを果たしてもらうぞ！";
			link.l2.go = "tonzag_church_good";
		break;
		
		case "tonzag_church_bad":
			dialog.text = "いろいろとありがとうございました、船長。さようなら！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchBad");
		break;
		
		case "tonzag_church_good":
			dialog.text = "了解だぜ、船長！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchGood");
		break;
		
		case "tonzag_afterchurchfight":
			dialog.text = "俺は今までにたくさんの悪党を見てきたが、船長、初めて心の底からぞっとしたぜ。どう思う？ 小さな怪物が大きな怪物を殺したら、それは贖罪になるのか？";
			link.l1 = "ラムを水で薄めてるのか？分かったら教えてくれ。行くぞ、ここはもう終わりだ。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ResetTonzag");
		break;
		
		// Эпилог
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "はは！そんなことをお前から聞くとは思わなかったぞ。それで？次は修道院にでも行く気か？";
			link.l1 = "本気だ、"+npchar.name+"。父さんの具合が日に日に悪くなっているんだ。手遅れになる前に会いに行きたい。";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "俺たちの船のどこが気に入らないんだ？それとも本気で大西洋が相手じゃ無理だと思ってるのか？";
			link.l1 = "陸に上がって落ち着くことについて考えているんだ。まだ海のない生活なんて想像できないけど。でももしそんな日が来るなら、ちゃんと準備しておきたい。自分の内側で何と戦わなきゃいけないかを理解したいんだ。";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "この会話で二度も俺を言葉に詰まらせるとはな。本気で帆の風を暖炉と暖かい粥に変えるつもりか？";
			link.l1 = "父さんの病気が悪化したのを見て、誰も永遠じゃないってことを思い出したんだ。次に何があるかはまだ決めてない。今は――ただ帰路だけだ。そして…お前にも一緒に来てほしいと思っている。友としてな。だが、もし断るなら――理解する。無理強いはしない。";
			link.l1.go = "SharlieEpilog_Tonzag_4";
		break;

		case "SharlieEpilog_Tonzag_4":
			dialog.text = "断る？お前を一人で行かせたら、一生錨磨きでもしてろってことだな！俺のことを何も知らないな、キャプテン。";
			link.l1 = "それこそ俺が期待していた答えだ。昔のフランスはもう違う。空っぽで、退屈で、よそよそしい…友と呼べる者が残っているとは思えない。二週間後に出航だ。時間を無駄にしたくない。出発を祝ってタヴァーンで宴を開とう。どうだ？";
			link.l1.go = "SharlieEpilog_Tonzag_5";
		break;

		case "SharlieEpilog_Tonzag_5":
			dialog.text = "はは！俺が断ると思っているなら――ずいぶん待たされるぞ！";
			link.l1 = "じゃあ決まりだ――用事を片付けたらタヴァーンで会おう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tonzag_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Tonzag = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;

	}
}