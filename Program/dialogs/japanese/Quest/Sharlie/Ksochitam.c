// диалоги НПС по квесту Коварный остров Ксочитэм
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何か用か？";
			link.l1 = "いいえ、何もありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// капитан-нежить Санта-Квитерии
		case "SQC_skeletcap":
			PlaySound("Types\skel.wav");
			dialog.text = "お前は……それでも……死なねばならん……あいつが来る……そしてお前を殺す……俺たち全員を殺したように……ここにいる者すべてを殺したように……";
			link.l1 = "何だ？お前は誰だ？誰のことを言っているんだ？";
			link.l1.go = "SQC_skeletcap_1";
		break;
		
		case "SQC_skeletcap_1":
			PlaySound("Types\skel.wav");
			dialog.text = "あいつは巨大だ……無敵だ……殺す……お前も殺される。俺がお前を殺さなきゃ……俺が殺せば、お前は俺たちみたいにはならない……わかってないんだ……あいつの剣で死ぬぞ……そうなればお前も俺たちと同じに……サンタ・キテリア号の皆と同じに……\n";
			link.l1 = "ありえねえ！";
			link.l1.go = "SQC_skeletcap_2";
		break;
		
		case "SQC_skeletcap_2":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=2; i<=3; i++)
			{
				sld = characterFromId("SQI_skelet_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_SQCskeletcapdie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Страж маски Кукулькана
		case "guardmask":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "ずっとあなたを待っていたんだ！..";
			link.l1 = "えっ！…驚いた！…なんて立派な骸骨だ！";
			link.l1.go = "guardmask_1";
		break;
		
		case "guardmask_1":
			dialog.text = "見える……感じる……お前が……俺に……自由をもたらしてくれた……";
			link.l1 = "何を言ってるんだ？お前は何者だ！？";
			link.l1.go = "guardmask_2";
		break;
		
		case "guardmask_2":
			dialog.text = "私はクソチェアテムの守護者、ククルカンの仮面の番人……そしてお前の差し迫った死そのものだ！..";
			link.l1 = "...";
			link.l1.go = "guardmask_3";
		break;
		
		case "guardmask_3":
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "KSOCHITAM_MONSTERS");
			LAi_group_FightGroups("KSOCHITAM_MONSTERS", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
			n = Findlocation("Shore_mask");
			locations[n].type = "seashore";
			pchar.questTemp.Ksochitam.GuardMaskFight = "true";
			for (i=1; i<=4; i++)
			{
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 1, 0, 0, "fortfire");
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 2.5, 0, 0, "fortfire");
			}
		break;
		
		case "guardmask_4":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "やめろ……";
			link.l1 = "「なんで俺がそんなことしなきゃなんねえんだよ、あ？息切れでもしてんのか、骨野郎？」";
			link.l1.go = "guardmask_5";
		break;
		
		case "guardmask_5":
			dialog.text = "いいや。お前には俺を殺すことなど絶対にできねえ。あの魔法の短剣を使ってもな。俺たちの決闘は、 果てしなく長く続くかもしれねえぞ。お前が完全に力尽きて死ぬまでな。";
			link.l1 = "そうかい？それで、どうして俺を殴れねえんだ？";
			link.l1.go = "guardmask_6";
		break;
		
		case "guardmask_6":
			dialog.text = "お前は勇敢で強き戦士、しかも族長の爪を手にしている。この短剣を持ち、俺に戦いを挑む者には、 生かしておく義理がある。望むものを手に入れるがいい。";
			link.l1 = "お前は誰だ？本当は何者なんだ、守護者よ？";
			link.l1.go = "guardmask_7";
		break;
		
		case "guardmask_7":
			dialog.text = "かつて俺はアルベルト・カスコと呼ばれていた。アロンソ・デ・マルドナード隊の兵士だったんだ。 俺たちは古代のタヤサルを発見したが、捕まって生贄にされた。俺の背の高さと力のせいで、 異教徒カネクは俺をクソチェアテムの守護者、ククルカンの仮面の番人に変えた。クソチェアテムに足を踏み入れた者は、 みんな俺に見つかり、俺の手で殺され、不死者にされたのさ。\n酋長の爪の短剣で、この場所の地図を俺の肉体に刻まれた。俺は永遠に仮面の安全を見張り続ける。そして、 その短剣をこの手に取り戻すまで、俺の魂は決して安らぐことはない。";
			link.l1 = "酋長の爪が必要か？";
			link.l1.go = "guardmask_8";
		break;
		
		case "guardmask_8":
			dialog.text = "ああ。お前が仮面を必要としているなら、短剣を渡してくれ。俺はようやく待ち望んだ安らぎを得るし、 お前は仮面を手に入れることができる。誓って言うが、お前はそれを持ってクソチェアテムから生きて出られるぞ。";
			link.l1 = "申し出を受けよう、守護者よ。洗礼堂の泉の奥、あの台座の上にあった仮面を見たが、あれがそれか？";
			link.l1.go = "guardmask_9";
		break;
		
		case "guardmask_9":
			dialog.text = "そうだ。これはククルカン――空飛ぶ蛇――そのものの偉大なる秘宝だ。この話が終わったら、あそこへ行って手に取るがいい。";
			link.l1 = "さて、約束を守ってくれるといいがな、ガーディアン……";
			link.l1.go = "guardmask_10";
		break;
		
		case "guardmask_10":
			dialog.text = "誓ったんだ……";
			link.l1 = "では、酋長の爪を受け取ってくれ。これがあなたの魂に安らぎをもたらすことを願っている。";
			link.l1.go = "guardmask_11";
		break;
		
		case "guardmask_11":
			RemoveItems(pchar, "knife_01", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the Chief's Claw");
			RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "ああ、この瞬間をどれほど待ち望んだことか！ついに私はここを去ることができる……。だが、別れの印として、私の力の一片をお前に授けたい。これがアルベルト・カスコが贈る最後の贈り物となるだろう。 ";
			link.l1 = "...";
			link.l1.go = "guardmask_12";
		break;
		
		case "guardmask_12":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Ksochitam_GuardMaskGift", 1.5);
		break;
		
		case "guardmask_13":
			dialog.text = "さて、もう行かねばならない。時間を無駄にするな。守護者とククルカンの仮面がなければ、 この島はすぐに永遠に消えてしまうぞ。";
			link.l1 = "それについては後悔することなんてないさ。世界から地獄の穴が一つ減っただけだ……だが待て、守護者！お前はテヤサルに行ったことがあるんだろう！頼む、その場所がどんな所だったか教えてくれ。";
			link.l1.go = "guardmask_14";
		break;
		
		case "guardmask_14":
			dialog.text = "それは古代マヤの都市だ。人々がまだそこに住んでいた時代の姿がそのまま残っている。壮麗な神殿、 そびえ立つピラミッド……。今はイツァ族がそこに住み、マヤの直系の子孫だと主張している。彼らは宗教、文化、 生活様式のすべてでマヤを真似しようとしている。";
			link.l1 = "どうやってそこへ行けばいいんだ？";
			link.l1.go = "guardmask_15";
		break;
		
		case "guardmask_15":
			dialog.text = "俺たちの指揮官は道を知ってた、アロンソ・デ・マルドナードだ。俺たちはただ奴についてジャングルを進んだだけさ。 覚えてるのは、ペルラス岬の北にあるモスキート湾に上陸して、そこから西の奥深くのセルバへ進んだことだけだ。";
			link.l1 = "テヤサルで注目すべきことは何だ？";
			link.l1.go = "guardmask_16";
		break;
		
		case "guardmask_16":
			dialog.text = "あそこは何もかもが注目に値する。まさに全てだ。だが、俺たちが興味を持ったのはマヤの財宝だけだった。そして、 それを見つけた。だが、その代償は大きかった――特に俺にとってはな。\nだが今、ようやく俺は自由になったんだ！";
			link.l1 = "テヤサルへ向かう前に知っておくべきことは何だ？";
			link.l1.go = "guardmask_17";
		break;
		
		case "guardmask_17":
			dialog.text = "イッツァ族は非常に強く、知恵もある。彼らは国籍に関係なく白人を憎み、 自分たちの領土に侵入するよそ者は容赦なく滅ぼす。普通のイッツァ戦士は一切会話しようとしないが、 カネクやその息子ウラカンなら……もし仮面を見せれば、話すかもしれない。もし生きてタヤサルにたどり着けたら、自分の目で確かめるといい。だが、 そこから無事に出られるかな……";
			link.l1 = "「カネクはタイアサルに来た白人を全員生贄に捧げるのか？」";
			link.l1.go = "guardmask_18";
		break;
		
		case "guardmask_18":
			dialog.text = "そうだと思う。しかし、それにはククルカンの仮面をかぶった男は含まれないかもしれない。";
			link.l1 = "わかった。それを頼りにしているぞ。";
			link.l1.go = "guardmask_19";
		break;
		
		case "guardmask_19":
			dialog.text = "さらばだ、兵士よ。仮面の力を正しい目的のために使ってくれることを願っている。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_GuardMaskGoAway");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
