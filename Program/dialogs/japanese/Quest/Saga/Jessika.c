// Джессика Роуз - нежить и супербосс
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何か用か？";
			link.l1 = "いいえ、なんでもありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// бой на рифе
		case "reef":
			PlaySound("Voice\English\saga\Jessica Rose-06.wav");
			dialog.text = "お前だ！お前があの娘をここに連れてきたんだ！あの娘はあいつの血を引いている！あの女の血も引いている！ 娼婦の娘が母親の墓に来たんだ！あの娘は死ぬ！お前には止められないぞ！\nジェシカの邪魔をするな！復讐は私のものだ！";
			link.l1 = "...";
			link.l1.go = "reef_1";
		break;
		
		case "reef_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "stage_1":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "ははっ！俺には傷ひとつつけられねえぞ！\n風よ、水よ、大地よ、炎よ――我が命に従い、力を貸せ！\n死者よ蘇れ、炎よ燃え盛れ、水よ橋を守れ、そして風よ、その翼で奴を空へと舞い上げ、大地に叩きつけろ！\n楽しめよ！！！";
			link.l1 = "...";
			link.l1.go = "stage_1_exit";
		break;
		
		case "stage_1_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaFirstKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_2":
			PlaySound("Voice\English\saga\Jessica Rose-08.wav");
			dialog.text = "ははっ！俺には傷ひとつ付けられねえぞ！\nもっと死者どもを蘇らせて襲わせろ、炎で石を焼き尽くせ、風でお前を吹き上げて叩き落とせ、 大地がお前の力を吸い取るがいい！\n存分に味わえ！！！";
			link.l1 = "...";
			link.l1.go = "stage_2_exit";
		break;
		
		case "stage_2_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.BladePenalty = 30;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaSecondKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_3":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "はっ！俺には傷ひとつつけられねえぜ！\n毒よ、俺の炎の刃の剣を包め。風よ、お前を抱きしめろ。水よ、お前の俊敏さを洗い流せ！\n死ね！はははは！";
			link.l1 = "...";
			link.l1.go = "stage_3_exit";
		break;
		
		case "stage_3_exit":
			DialogExit();
			npchar.viper = true;
			TakeNItems(npchar, "potion2", 3);
			LAi_SetActorType(pchar);
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.EnergyPenalty = 2;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "quest", "bridge2");
			LAi_ActorTurnToLocator(pchar, "quest", "bridge1");
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaThirdKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_4":
			PlayStereoOGG("music_shore");
			sld = characterFromId("Svenson");
			dialog.text = "もう十分だ……私は疲れた。負けた……不運なジェシカの運命を哀れんでくれ！";
			link.l1 = "そうか……この死体の重荷からお前の哀れな魂を解放してやろう！";
			link.l1.go = "exit_battle";
			if (CheckAttribute(sld, "quest.jessika_peace")) // выслушал историю Джессики
			{
				link.l2 = "ジェシカ、お前の話は知ってるよ。お前の人生がそんなに悲しくて、あんな終わり方をしたこと、本当に気の毒に思うぜ。 \n俺と話したいんだろ？まあ、最近お前に殺されかけたことは忘れるように努力するさ。簡単じゃねえが、 話を聞いてやるよ……";
				link.l2.go = "exit_talk";
			}
		break;
		
		case "exit_battle":
			DialogExit();
			SetMusic("music_teleport");
			DeleteAttribute(npchar, "viper");
			LAi_SetImmortal(npchar, false);
			npchar.chr_ai.hp = stf(npchar.chr_ai.hp)+100;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_JessikaDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.JessSeekTreatment = 0;
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
		break;
		
		case "exit_talk":
			dialog.text = "ありがとう……あなたはもうベアトリス・シャープとローレンス……私のローレンスのことを知っているわね。私は彼女をためらわずに殺したけれど、彼を殺すことはできなかった。 私にはできなかった、でも彼にはできた。ジェシカは死んだ……";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef");
			NextDiag.TempNode = "exit_talk_0";
		break;
		
		case "exit_talk_0":
			dialog.text = "…だが、恐ろしい誓いで結ばれた血の誓約は、いまだ果たされていない。その誓約の力はインディアンの呪術に由来する。 それが死体を墓から蘇らせたのだ。\n憎しみが私の魂を砂漠に変えた。この礁に来た者は皆、私の手で殺され、その死体は私の傀儡となった。 私が助けを求められるのは、私を打ち倒した者だけだ…";
			link.l1 = "「それで、俺に何をしてほしいんだ？俺にできるのは、お前を苦しみから解放してやることだけだ…」";
			link.l1.go = "exit_talk_1";
		break;
		
		case "exit_talk_1":
			PlaySound("Voice\English\saga\Jessica Rose-03.wav");
			dialog.text = "助けて……彼のところへ連れて行って。";
			link.l1 = "ローレンス・ベルトロープのところへ？それをどうやってやれって言うんだ？ 俺の船員たちはあんたの顔を見た途端に逃げ出すか、何のためらいもなくあんたを焼き殺すだろうよ。\nそれに、あんたはまだ俺の部下を殺して“支配”できるんだろう……";
			link.l1.go = "exit_talk_2";
		break;
		
		case "exit_talk_2":
			dialog.text = "奴らには俺の姿は見えねえ。だが、お前には見える。もう気づいているだろうが、俺は生者にはない力を持っている。 だが、お前の許しがなければお前の船に乗り込むことはできねえ。あいつの所へ連れて行け。\n長くお前のそばにはいないし、お前の仲間にも危害は加えねえ。ジャマイカのポートランド湾に真夜中に俺を上陸させろ。 翌晩また会おう。その時、お前が探しているものを渡してやる。";
			link.l1 = "俺がここに来た理由をどうして知ってるんだ？";
			link.l1.go = "exit_talk_3";
		break;
		
		case "exit_talk_3":
			PlaySound("Voice\English\saga\Jessica Rose-01.wav");
			dialog.text = "俺は色々知ってるぜ。生きてる奴らよりもな。あいつを見た……あいつには書類が必要だろう、それなら手に入るさ。もっと手に入るぞ；おまけもやる。 俺をあいつのところへ連れて行け……";
			link.l1 = "ふむ。お前のヘレンへの血に飢えた企みは気に入らねえ。絶対に彼女に手を出すんじゃねえぞ。結局のところ、 彼女は母親の行いに責任なんてねえんだからな。";
			link.l1.go = "exit_talk_4";
		break;
		
		case "exit_talk_4":
			dialog.text = "俺の負けだ。彼女には手を出さねえ……約束する。";
			link.l1 = "まだ終わっちゃいないぜ。俺にかけた数々の呪いを解いてくれるつもりか？正直、 ずっと呪われたまま生きるのはごめんだな……";
			link.l1.go = "exit_talk_5";
		break;
		
		case "exit_talk_5":
			dialog.text = "そんなに簡単なことじゃない……私がポートランド・コーブで君と会ったときに……自分を癒す方法を教えてあげるよ。";
			link.l1 = "お前の後に何を？…どういう意味だ？";
			link.l1.go = "exit_talk_6";
		break;
		
		case "exit_talk_6":
			dialog.text = "「彼と会った後で。」";
			link.l1 = "ああ、あいつは喜ばねえだろうな。想像できるぜ。よし、まとめよう。まず第一に、お前は誰にも見られねえと約束しろ。 第二に、俺の仲間には手を出すな。第三に、ヘレンのことは考えもしねえ。第四に、俺が探してるものを渡せ。 そして第五に、お前の呪いを俺から解いてくれ。合ってるか？";
			link.l1.go = "exit_talk_7";
		break;
		
		case "exit_talk_7":
			dialog.text = "ほとんど正解だ。俺はお前を治してやらねえが、治し方は教えてやる。自分でやるしかねえぞ。";
			link.l1 = "よし。取引成立だな。俺の船に乗るのを許してやる。";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef2");
			NextDiag.TempNode = "exit_talk_8";
		break;
		
		case "exit_talk_8":
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			dialog.text = "";
			link.l1 = "おい！どこにいるんだ？急にいなくなっちまって……";
			link.l1.go = "exit_talk_9";
		break;
		
		case "exit_talk_9":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			pchar.quest.Saga_JessFire.over = "yes"; 
			pchar.quest.Saga_JessFire1.over = "yes"; 
			pchar.quest.Saga_JessFire2.over = "yes";
			ref chr = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(chr, "hell_fire_1");
			DeleteAttribute(chr, "hell_fire_2");
			DeleteAttribute(chr, "hell_fire_3");
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Shadows", "9");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.Saga.JessOnShip = "true"; // атрибут на отрицательные последствия
			pchar.quest.Saga_Jessika_Travel.win_condition.l1 = "Hour";
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.start.hour = 0.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.finish.hour = 2.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l2 = "location";
			pchar.quest.Saga_Jessika_Travel.win_condition.l2.location = "shore36";
			pchar.quest.Saga_Jessika_Travel.function = "Saga_JessikaOnJamaica";
			NextDiag.CurrentNode = "shore";
			npchar.greeting = "jessika_2";
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
			LAi_LocationDisableOfficersGen("shore36", true);//офицеров не пускать в бухту Портленд
		break;
		
		case "shore":
			dialog.text = "約束を守ってくれたな――俺たちはジャマイカに着いた。\n明日の夜、ここに来い。そしたら約束を果たしてやる。さらばだ。";
			link.l1 = "さらば……";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Saga.JessOnShip");
			DeleteAttribute(npchar, "SaveItemsForDead");
			DeleteAttribute(npchar, "DontClearDead");
			LAi_SetActorType(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Shadows", "10");
			SetFunctionTimerCondition("Saga_JessikaShoreWait", 0, 0, 1, false);
			NextDiag.CurrentNode = "shore_2";
			npchar.greeting = "jessika_3";
		break;
		
		case "shore_2":
			dialog.text = "終わりだ "+pchar.name+"...";
			link.l1 = "どういう意味だ？";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "終わった……ほら、持っていけ、これがお前の探していたものだ。これは私のライバルの手紙で、彼女と一緒に埋められていたんだ。 状態は良好だ。私は彼女を許した、もう私の心に憎しみはない。";
			link.l1 = "……会ったの？ローレンスと一緒に？";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			GiveItem2Character(pchar, "letter_beatriss"); // дать письмо
			AddQuestRecordInfo("Letter_beatriss", "1");
			dialog.text = "ああ。奴が人生で最後に感じたのは恐怖だった。俺は同情なんかしねえよ。";
			link.l1 = "神が彼の罪深い魂をお許しくださいますように……もう二度と彼に会うことはなさそうだ。";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "お前は何も大切なものを失っていない。あいつは本当に悪い男だった。さて、そろそろお別れだな。 ここで私の役目は終わった。誓いは果たされたし、魔法も力を失った。約束した贈り物をやろう。ほら、 これが私のフランベルジュだ。もう私には必要ない。この剣は唯一無二だ、 世界中どこを探してもこれ以上のものは見つからないぞ。";
			link.l1 = "ありがとう……";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			RemoveAllCharacterItems(npchar, true);
			GiveItem2Character(pchar, "blade_25");
			PlaySound("interface\important_item.wav");
			dialog.text = "さて、次はお前のことだ。ブリッジタウンの現地教会へ行き、俺の呪いを解くために動け。そこに神父がいるはずだ。 あいつは俺と面識がある。その神父に話しかければ、何をすべきか教えてくれるだろう。ろうそくを二十本用意しろ、 必要になるぞ。\n";
			link.l1 = "本当に彼は私を治してくれるのか？";
			link.l1.go = "shore_7";
		break;
		
		case "shore_7":
			dialog.text = "お前が自分でやるんだ。神が導いてくださる。安心しろ。すべてうまくいくさ。";
			link.l1 = "よし、すぐにバルバドスへ向けて出航しよう。で、次はどうするんだ？";
			link.l1.go = "shore_8";
		break;
		
		case "shore_8":
			PlaySound("Voice\English\saga\Jessica Rose-04.wav");
			dialog.text = "そして、最後にもう一つだけ願いがあるわ。この入り江の海辺に私の遺体を埋めてほしいの。それが私の願いよ。いつか、 あなたが哀れなジェシカの墓を訪れてくれるかもしれないわね。さようなら、\n "+pchar.name+"……そして私のためにも祈ってくれ……";
			link.l1 = "ジェス？…";
			link.l1.go = "shore_9";
		break;
		
		case "shore_9":
			DialogExit();
			LAi_KillCharacter(npchar);
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("shore36", false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("Shadows", "11");
			pchar.questTemp.Saga.JessTreatment = "true";
			// вытираем Белтропа
			sld = characterFromId("Beltrop");
			sld.lifeday = 0;
			pchar.questTemp.Saga.Beltrop_die = "true"; // Белтроп убит
			sld = ItemsFromID("letter_jess");
			sld.price = 1; // страницу можно выкладывать 270912 
		break;
		
		case "soul":
			dialog.text = "俺のことがわかるか、船長？";
			link.l1 = "あなた…あなたなのか？でも、どうして？";
			link.l1.go = "soul_1";
		break;
		
		case "soul_1":
			dialog.text = "「はい。」 "+pchar.name+"「私よ、私、ジェシカよ！少なくとも二十年前の私はそんな姿だったの。」";
			link.l1 = "それで…俺は死んじまったのか？でも、いつ？どうやって？";
			link.l1.go = "soul_2";
		break;
		
		case "soul_2":
			dialog.text = "「死んでいないな」 "+pchar.name+"。今はブリッジタウンの教会にいるんだ。ただ……眠っているだけさ。";
			link.l1 = "これはただの夢か？すべてが現実すぎる……";
			link.l1.go = "soul_3";
		break;
		
		case "soul_3":
			dialog.text = "時々そういうこともあるさ。 "+pchar.name+"。神はあなたの声をお聞きになりました。あなたの祈りはあなた自身を癒しただけでなく、私の魂まで清めてくれました。 誠にありがとうございます、 "+pchar.name+"！それから、リーフで起きたことを許してほしいんだ。あれは……とにかく、許してくれ。君の許しを得ずに立ち去ることはできなかったんだ。";
			link.l1 = "許してあげるよ、ジェシカ。俺は本当に生きているのか？";
			link.l1.go = "soul_4";
		break;
		
		case "soul_4":
			dialog.text = "あなたは……心配しないで。すぐに目を覚ますよ。\nただ、さよならを言いたかっただけなんだ。";
			link.l1 = "あなたは本当に……美しい！";
			link.l1.go = "soul_5";
		break;
		
		case "soul_5":
			dialog.text = "私のことが好き？そうね、かつては小アンティル諸島の一流の求婚者たちが私に言い寄ってきて、 イスラ・テソロの海賊の三人に一人は私のために決闘する覚悟だったのよ。";
			link.l1 = "だが、お前はいつも一つだけで十分だったじゃねえか…ええい、生姜のお守りめ！で、どうしてこんなことになっちまったんだ？";
			link.l1.go = "soul_6";
		break;
		
		case "soul_6":
			dialog.text = "私の怒りのせいで。私の憎しみのせいで。理解し、許し、忘れることができなかったせいで。\n新しい人生を始めることもできたのに、私は愚かで無意味な復讐に身を捧げる道を選んでしまった。\nあなたが私を解放してくれた。ありがとう。 "+pchar.name+"...";
			link.l1 = "本当にあなたの人生が哀れに思える……";
			link.l1.go = "soul_7";
		break;
		
		// здесь проверяем Мэри
		case "soul_7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{ // Мэри-офицер
				dialog.text = "やめて……まだショウガのお守りがあるじゃないか……";
				link.l1 = "私の何だって？";
				link.l1.go = "mary_1";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CheckAttribute(pchar, "questTemp.LSC.marywait"))
			{ // Мэри осталась на острове
				dialog.text = "やめて……まだ生姜のお守りがあるじゃないか……";
				link.l1 = "私の何だって？";
				link.l1.go = "mary_3";
				break;
			}
			dialog.text = "……やめてくれ……私の悲しい経験を考えて、同じ過ちを繰り返さないでくれ。そして、大切な人たちにも同じ過ちをさせないでくれ。";
			link.l1 = "それを考慮して、もう二度と同じ過ちは犯さないようにする……";
			link.l1.go = "soul_8";
		break;
		
		case "mary_1":
			dialog.text = "少し考えてみろ。彼女はお前の船にいるんだぞ。";
			link.l1 = "メアリー！？";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "ああ。彼女はお前の人生で出会う中で最高の女だ。忘れるなよ。彼女の愛は純粋で、献身は無限だ。勇敢で若いが、 必死で未熟でもある。あまり多くを理解していない。彼女を大切にし、守ってやれ。 誰にもお前たちの間に割り込ませるな。彼女はお前のお守りだ……";
			link.l1 = "俺は……俺は絶対に彼女を見捨てないし、どんな危険からも彼女を守るんだ。";
			link.l1.go = "soul_8";
		break;
		
		case "mary_3":
			dialog.text = "あの死んだ船でできた奇妙な島に彼女はいる……彼女は一人きりじゃないが、孤独だ。毎朝、君のことを思いながら目覚め、毎日、君のために祈り、毎晩、 船室には灯りがともり、枕は彼女の涙で濡れている……";
			link.l1 = "「メアリー……」";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "あなたたち二人の間には娘がいる。かつてローレンスと私の間に立っていた女の娘だ。 お前の護符の運命はお前自身の手にある。彼らは共存できない――ベアトリスと私ができなかったように。\n";
			link.l1 = "「どうしてそれを知っているんだ？」";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "もう一つの側面……多くのことを明かしてくれる……選ぶのはお前だが、忘れるな。メアリーはお前の人生で得られる最高の女だ。彼女の愛は純粋で、献身は限りない。 勇敢で若く、それでいて必死で未熟だ。多くのことを理解していない。彼女にはお前の守りと、気遣いと、愛が必要だ。 彼女はお前のお守りなんだ。\n";
			link.l1 = "考えておくよ。必ずやるつもりだ……";
			link.l1.go = "soul_8";
		break;
		
		case "soul_8":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) sTemp = "";
			else sTemp = "And about the daughter of Beatrice, know that your noble actions on her behalf will be left unvalued. Soon you will see that for yourself. Be careful with her. Well...\n";
			dialog.text = ""+sTemp+"俺は行かなくちゃならねえ。今度こそ本当にお別れの時だ……。ジェシカのことを忘れないでくれ、たまには墓にも顔を出してやってくれよ……。墓の場所を知ってるのはお前だけだからな。\n";
			link.l1 = "もちろんだ、ジェス。私がそこに行って、あなたのために祈るよ。";
			link.l1.go = "soul_9";
		break;
		
		case "soul_9":
			dialog.text = "ありがとうございます。さようなら。 "+pchar.name+"「！さようなら！」";
			link.l1 = "さようなら、ジェシカ…";
			link.l1.go = "soul_10";
		break;
		
		case "soul_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_JessikaSoul_4", -1);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
