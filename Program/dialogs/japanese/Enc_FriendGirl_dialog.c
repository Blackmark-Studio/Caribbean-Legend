void ProcessDialogEvent()
{	
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iRank, iMassive;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{		
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = LinkRandPhrase("ああ、旦那様、お会いできて本当に嬉しいですわ！","やっと誰か来た！","なんてことだ、あなたに会えて本当に嬉しいよ！");
			Link.l1 = LinkRandPhrase("どうしたんだい、あんた？","何か問題でも、ダーリン？","そんなに興奮しないでください――若いお嬢さんの健康によくありませんわ。さあ、落ち着いて、何があったのか教えてくださいます？");
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("俺の友達……あいつは本当に勇敢なんだ……捨てられた井戸の中に降りていったんだ！","俺の友達が廃井戸に降りていったんだが、まだ戻ってこないんだ！もう何時間もそこにいるんだよ！","俺の友達が廃井戸で突然消えちまったんだ！");
			Link.l1 = "「それで一体なんであいつはあそこに入ったんだよ！？」";
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = "ああ、知ってるだろう、あいつは何でもかんでも怖がるんだ！金でいっぱいの地下牢があるって聞いて、 そこに降りていったんだよ……でも俺は馬鹿じゃねえ、そんなこと考えもしねえさ！";
			Link.l1 = "そうだ、このような場所でお前がやることなんて何もねえよ。";
			Link.l1.go = "Step_3";
		break;		
		case "Step_3":
			dialog.text = "「でも、俺はこれからどうすればいいんだ？頼む、お願いだから、彼女を助けてくれ、頼むよ！」";
			Link.l1 = "わかった、俺がなんとかする。お前は家に帰ったほうがいい、ここでやることは何もねえぞ。";
			Link.l1.go = "Step_agree";
			Link.l2 = "それはお前の問題だ、俺の時間を無駄にしたくねえ。じゃあな……";
			Link.l2.go = "Step_disAgree";
		break;

		case "Step_agree":
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			if (rand(1))
			{ //бандюганы
				LAi_LocationDisableMonGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //монстров не генерить 1 день
				LAi_LocationDisableOffGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //офицеров не пускать 1 день
				LocatorReloadEnterDisable(pchar.GenQuest.EncGirlF.locationId, "reload2", true);
				pchar.GenQuest.OpenTheRopeExit = pchar.GenQuest.EncGirlF.locationId; //флаг для открытия релоада
				string model[10];
				model[0] = "citiz_41";
				model[1] = "citiz_42";
				model[2] = "citiz_43";
				model[3] = "citiz_44";
				model[4] = "citiz_45";
				model[5] = "citiz_46";
				model[6] = "citiz_47";
				model[7] = "citiz_48";
				model[8] = "citiz_49";
				model[9] = "citiz_50";
				i = 0;
				while(i < 3)
				{
					iMassive = rand(9);
					if (model[iMassive] != "")
					{
						iRank = sti(pchar.rank) - rand(5) + rand(5);
						if (iRank < 1) iRank = 1; 
						sld = GetCharacter(NPC_GenerateCharacter("CaveGandMan" + i, model[iMassive], "man", "man", iRank, PIRATE, 1, true, "marginal"));
						SetFantomParamFromRank(sld, iRank, true);
						sld.SaveItemsForDead = true;
						sld.DontClearDead = true; 
						sld.money = iRank*200+1000+rand(500);
						LAi_SetWarriorType(sld);
						LAi_warrior_SetStay(sld, true);
						//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
						LAi_group_MoveCharacter(sld, LAI_GROUP_ENEMY);// лесник изменил группу чтобы ядом таино травить можно было
						LAi_group_Attack(sld, Pchar);// лесник добавил атаку на пчара а то у некоторых баг что они не нападают.
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirlF.locationId, "quest", "quest" + i);
						i++;
						model[iMassive] = "";	
					}
				}
			}
			else
			{ //и правда девка 
				sld = GetCharacter(NPC_GenerateCharacter("UndergroundGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, PIRATE, 1, false, "citizen"));
				sld.dialog.filename = "Enc_FriendGirl_dialog.c";
				int iTemp = rand(1);
				sld.dialog.currentnode = "Underground"+ iTemp; //здесь рендом поведения девки: 0-помогите, 1-сама крутая// лесник - раскоментил itemp
				sld.greeting = "Enc_RapersGirl_" + (iTemp+1); //соотв. озвучка
			   // LAi_SetStayType(sld);
				LAi_SetCitizenType(sld);// чтоб ходила по пещере. лесник
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				GetCharacterPos(pchar, &locx, &locy, &locz); // и ниже - ищем ближейший локатор лесник.
	            ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirlF.locationId, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			}
			LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_disAgree":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			LAi_SetCitizenTypeNoGroup(npchar);
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			NextDiag.CurrentNode = "FackYou";
			DialogExit();
		break;			
		case "FackYou":
            NextDiag.TempNode = "FackYou";
            dialog.text = "そんな冷たい奴とは話したくねえ "+GetSexPhrase("血の塊","あばずれ")+"。消え失せろ！";
			Link.l1 = "へっ、なんて嫌な女だ……";
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = "ああ、神よ、あなたに会えて本当に嬉しい！";
			Link.l1 = "「どうしたんだい、美人さん？」";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = "ここで迷っちまった！ああ神様、俺は本当に怖くてたまらねえ！！！";
			Link.l1 = "さて、もう大丈夫だ。俺について来い、道を教えてやる。地上に出たら家に走って帰れ、 そして二度とここで俺に会わないように祈るんだな！";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = "おっしゃる通りです "+GetAddress_Form(NPChar)+".";
			Link.l1 = "「いいだろう。」";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
		break;

		case "Underground1": //крутая мочалка
            dialog.text = "ちくしょう、このダンジョンに興味を持った奴が他にもいるみてえだな！";
			Link.l1 = "「お嬢ちゃん、こんなところで何してるんだ？」";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = "お前には関係ねえだろう！";
			Link.l1 = "おったまげたぜ、そいつは百万ペソの価値がある答えだな……";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = "二百万のためにか。お前は勝手にしろよ。俺はお前なんかどうでもいいんだ。";
			Link.l1 = "そうかい、俺も同じ気持ちだぜ。でも、上の階にいるあんたの仲間が心配でたまらなかったみたいだぞ…";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = "なんて馬鹿な奴だ！あいつは恐怖で漏らすくせに、自分と俺が同じだと思ってやがる。";
			Link.l1 = "おいおい、驚いたぜ、あんたはあの女が本当に気に入らねえんだな。スカートをはいた悪魔――それがあんただ。";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = "おい、言葉に気をつけろ！それより、さっさと消えな。";
			Link.l1 = "さて、俺の助けがいらねえなら……";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = "いや、俺は違うぜ！";
			Link.l1 = "それではお別れだ、幸運を祈る。";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
            dialog.text = "またお前か？消えろ、もう二度と顔を見たくねえんだ…";
			Link.l1 = "ふむ……";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}
