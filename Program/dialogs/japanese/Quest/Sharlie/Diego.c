// Диего де Монтойя
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

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
		
		case "patrol":
			dialog.text = TimeGreeting()+", "+GetFullName(npchar)+"、サンホセ巡回隊の隊長だ。この町の外れで不審な行動があったとの報せを受けている。あなたがどなたで、 何をしているのか説明していただけますかな？";
			link.l1 = "Captain "+GetFullName(pchar)+"「旦那士官。私は異端審問官ヴィンチェント神父の権限と直接の指示によりここに来ました。 こちらが私の許可を証明する書類です。」";
			link.l1.go = "patrol_1";
		break;
		
		case "patrol_1":
			dialog.text = "よし……すべて問題ないな。異端審問官の署名もあって、きちんと記入されている。疑ってしまって申し訳ない。 灯台で何をしているんだ？";
			link.l1 = "そのような質問にお答えする権限はありません。本当に異端審問官のための私の任務の目的にご興味があるのでしたら、 サンティアゴにいるご本人に直接お尋ねになることをお勧めします。\nあなたは士官でしょうから、軍や勤務上の機密についてご存知のはずです。\n私がお伝えできるのは、スペイン船の難破の事情を調査しているということだけです。";
			link.l1.go = "patrol_2";
		break;
		
		case "patrol_2":
			dialog.text = "再度お詫び申し上げます、旦那。これ以上お引き止めはいたしません……あっ、ちょっとお待ちを！今、冷たい鋼の刃が見えたような気がしましたが、気のせいでしょうか？ なんて興味深い短剣なんでしょう！見せていただけますか？";
			link.l1 = "必ず返すのを忘れないでくれ。私にとってとても大事なものなんだ。";
			link.l1.go = "patrol_3";
		break;
		
		case "patrol_3":
			dialog.text = "ディオス・ミオ！この短剣は知っている、図書館の本の挿絵で見たことがある！これはコルテス本人の短剣だ！ ここに刻印がある……旦那、どうか断らないでください。この短剣を私に譲ってほしいのです！私は古代や特注の武器を集めていて、 これは本当に素晴らしい逸品です。高く買い取りますよ。";
			link.l1 = "旦那、この短剣は売り物じゃありません。贈り物としていただいたもので、誰にも売る気はありません。返してください。 ";
			link.l1.go = "patrol_4";
		break;
		
		case "patrol_4":
			dialog.text = "五百枚の金ドゥブロンでも満足しねえのか？そりゃあ大金だぜ。その金があれば船だって買えるんだぞ！";
			link.l1 = "いいや。俺にはすでに船があるし、この短剣は唯一無二だ。売るつもりはない。";
			link.l1.go = "patrol_5";
		break;
		
		case "patrol_5":
			dialog.text = "ええ、そりゃ残念だな……よし、貴重品を持っていけ。これ以上邪魔はしねえよ。幸運を祈るぜ！";
			link.l1 = "ごきげんよう、士官殿。";
			link.l1.go = "patrol_6";
		break;
		
		case "patrol_6":
			DialogExit();
			AddQuestRecord("Guardoftruth", "42");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "GuardOT_ClearMayakPatrol", 12.0);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("GOT_spamayaksold_"+i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 10.0);
			}
		break;
		
		case "shore":
			PlaySound("Voice\English\Sharlie\Diego De Montoya.wav");
			dialog.text = "もういい！あいつと話がしたいんだ……";
			link.l1 = "なるほど、目の前にいるのはディエゴ・デ・モントヤ本人か…\nだが失礼、旦那。以前どこかで会ったことがあるんじゃないか？\nああ、そうだ。トリニダードの灯台で会ったな。\nだが、あの時は別の名を名乗っていたはずだ…";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			dialog.text = "記憶力はさすがだな、旦那。まあ、陰で陰謀を巡らせたり戦を仕掛けたりできるのはあんただけじゃねえぜ。 あんたが俺に会いたくてたまらないって話もちゃんと聞いてるさ。どうやら、その願いは叶ったみたいだな。";
			link.l1 = "これは俺が期待してたような出会いじゃねえな、旦那。";
			link.l1.go = "shore_2";
		break;
		
		case "shore_2":
			dialog.text = "まあ、仕方ねえな。だが、お前の短剣を渡せば、生きてここを出るチャンスをやるぜ。";
			link.l1 = "珍品集めの情熱がそこまでお前を堕落させたのか、旦那。俺のためにこんな手の込んだ罠まで用意するとはな？\nいや、そうは思えねえな。真実の守護者が気を抜かせないのか、それとも俺の勘違いか？";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "何を言っているのか全く分からない。短剣は元の場所に戻さねばならん、それだけ知っていればいい。 金のために渡さなかったなら、今度は自分の命と引き換えに渡してもらうぞ。";
			link.l1 = "「本気で信じると思ってるのかい、旦那？今言ったことをさ。どうせ俺がこの湾から出られねえって、 もう決めつけてるんだろう？」";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			dialog.text = "「もし俺が約束したらどうする？」";
			link.l1 = "「カエル食い」という言葉か？ふむ……";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "旦那、これが最後のチャンスだ。俺が狙っている短剣を渡すか、それとも数分後にお前の死体から奪うか、どっちか選べ。 抵抗しても無駄だぜ、こっちは圧倒的に数で勝ってるんだからな。";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio")) link.l1 = "驚いたぜ、旦那、まったくだ。俺がそんな頑固な馬鹿で、銛も持たずにサメの口に頭を突っ込むと思ってるのか？\n野郎ども、こいつらを殺せ！";
			else link.l1 = "本当の力は数じゃなくて、腕前にあるんだぜ、旦那！";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto5", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio"))
			{
				PlaySound("interface\abordage_wining.wav");
				PlaySound("interface\abordage_wining.wav");
				for(i=1; i<=10; i++)
				{
					sld = characterFromId("GuardOT_Oursoldier_"+i);
					LAi_SetWarriorType(sld);
					ChangeCharacterAddressGroup(sld, "Shore15", "reload", "reload1_back");
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			sld = CharacterFromID("spa_baseprisoner");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=1; i<=13; i++)
			{
				sld = characterFromId("GOT_spashore_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_DiegoShoreGuardDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
