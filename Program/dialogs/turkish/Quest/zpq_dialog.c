void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Konuşmak istemiyorum.";
			link.l1 = "Hm, anladım.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "Bir dakika, señor, siz "+GetFullName(pchar)+"?";
			link.l1 = "Evet... Size nasıl yardımcı olabilirim?";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "Sana ihtiyacımız var. Ya da daha doğrusu, parana. Ve inat etmeye kalkma, çünkü bugün hiç keyfim yok. Sinirlenebilirim.";
			link.l1 = "Ah, lütfen, hangi paradan bahsediyorsun? Hazineyi yanımda taşıyacağımı gerçekten mi sandın?";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "Beni kandırmaya çalışma. Sadece parayı ver - "+FindRussianMoneyString(sti(pchar.questTemp.zpq.sum))+" ve yoluna devam edebilirsin. Yoksa zorla alırız.";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "O kalenin sıçanı için çalışmıyor musun? O zaman sana iyi bir haberim var, onu cehenneme yolladım.";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "O kalenin sıçanına çalışmıyor musun? Ona söyle, para güvenilir ellere teslim edildi, artık unutsun gitsin.";
			link.l1.go = "zpq_sld2_3";
			}
			if(makeint(Pchar.money) >= sti(pchar.questTemp.zpq.sum))
			{
				link.l2 = "Pekâlâ, al şu pis paranı, alçak!";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "Onlar bende yok...";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "Demek kaderin bu - açgözlülüğün yüzünden genç yaşta ölmek. Seni yaşatmak çok tehlikeli.";
			link.l1 = "Böylesine bir özgüven.";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "Heh, kaderin açgözlülüğün yüzünden ölmekmiş demek. Bize uyar, paylaşmak istemiyoruz.";
			link.l1 = "Seni öldürecek olan şey açgözlülüğün...";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "Hey, çocuklar! Kafasına bir çuval geçirin!";
			link.l1 = "Pekâlâ, bu senin seçimin...";
			link.l1.go = "zpq_sld2_5";
		break;
		case "zpq_sld2_5":
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(PChar, true);

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("zpq", "7");

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = "Cumana";
			pchar.quest.zpq_seaBattle.function = "zpq_seaBattle";
		break;
		case "zpq_sld2_6":
			dialog.text = "Güzel. Onları ver ve defol, kaptan!";
			link.l1 = "...";
			link.l1.go = "zpq_sld2_7";
			AddMoneyToCharacter(Pchar, -makeint(pchar.questTemp.zpq.sum));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("zpq", "8");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
		break;
		case "zpq_sld2_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for(int i = 1; i <= 3; i++)

			{

				sld = CharacterFromID("qp2_" +i);
				LAi_SetImmortal(sld, true);
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 6.0);
			}
		break;
	}
}
