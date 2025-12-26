// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsun? Sor bakalım.","Dinliyorum, sorun nedir?"),"Bu, ikinci kez sormaya çalıştığınız...","Bu, üçüncü kez sormaya çalışmanız...","Bu ne zaman bitecek?! Ben koloni işleriyle meşgul bir adamım ve sen hâlâ beni rahatsız ediyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim, üzgünüm.","Şimdi değil. Yeri ve zamanı değil."),"Doğru, şu anda söyleyecek bir şeyim yok, üzgünüm.","Daha sonra soracağım.","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "huber")
			{
				link.l1 = "Vali Bey, size çok kötü bir haberim var. Kısaca söyleyeyim: eşiniz sizi soymak istiyor. Beni, dolap sandıklarınızdan birinin kilidini açmam için ikna etmeye çalıştı. Bunu bilmeniz gerektiğini düşündüm.";
                link.l1.go = "FMQT";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+", Mösyö. Ben, Genel Vali Chevalier de Poincy'nin emriyle buradayım. Görevim, anavatanımızdan kolonileri denetlemek üzere gelen Baron Noel Forget'yi Tortuga'ya götürmek. Asıl amacı Fransız Batı Hint Ticaret Şirketi'ni kurmak. Size onu takdim etmeme izin verin... Tüm ayrıntıları kendisi açıklayacaktır.";
                link.l1.go = "patria_tortuga";
			}
		break;
		
		case "FMQT":
			dialog.text = "Ne-e? Yine mi? O kaltak! Buna pişman olacak, yemin ederim! Kampacho ona gününü gösterecek. Sen hâlâ burada ne yapıyorsun? Defol git buradan!";
			link.l1 = "Ben düşündüm ki...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25) link.l1.go = "FMQT_2";
			else link.l1.go = "FMQT_1";
		break;
		
		case "FMQT_1":
			Notification_Skill(false, 26, SKILL_LEADERSHIP);
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Her zaman aynı şey! Al, işte bu! Masada ne varsa hepsi bu! Şimdi defol!";
			link.l1 = "Teşekkür ederim, Ekselansları. Müsaadenizle çıkıyorum.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_2":
			AddMoneyToCharacter(pchar, 1000);
			GiveItem2Character(pchar, "pistol6");
			GiveItem2Character(pchar, "purse1");
			Log_Info("You have received a double barreled pistol and a purse of doubloons");
			dialog.text = "Her zaman aynı şey! Al şunu! Masada ne varsa hepsi bu!.. Gerçi, tamam, sen benim adam dolu aptal ve zavallılara pek benzemiyorsun. Biraz fazlasını da al... Şimdi defol!";
			link.l1 = "Teşekkür ederim, Ekselansları. Müsaadenizle çıkıyorum.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_3":
			DialogExit();
			pchar.quest.FMQT_late1.over = "yes";
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.FMQT = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Tortuga", "7");
			CloseQuestHeader("FMQ_Tortuga");
			FMQT_ClearChest();
		break;
		
		// Jason НСО
		case "patria_tortuga":
			dialog.text = "Pekala, Kaptan Charles de Maure. Barona gereken şekilde davranılacak ve görevinde ona yardımcı olmak için elimden geleni yapacağım.";
			link.l1 = "";
			link.l1.go = "patria_tortuga_1";
		break;
		
		case "patria_tortuga_1":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
