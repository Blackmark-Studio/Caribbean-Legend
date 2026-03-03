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
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("Kardeşler, Engizisyon'un saflarında bir düşman var!","Alarmı kaldırın, kardeşler!");
					link.l1 = "Gerçekten de Engizisyon'un düşmanları tetikte...";
					link.l1.go = "fight";			
			}
			else
			{	
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Merhaba, "+GetSexPhrase("oğlum","kızım")+" . Seni buraya ne getirdi?.. ","Seni yuvamızda gördüğüme sevindim, "+GetSexPhrase("oğlum","kızım")+". . Seni buraya ne getirdi?"),""+GetSexPhrase("Oğlum","Kızım")+", bugün zaten konuştuk. Başka bir şeye ihtiyacın var mı?",""+GetSexPhrase("Oğlum","Kızım")+", tarikatımızın müritleri sonsuz sabırlarıyla bilinmezler. O yüzden, sana bir kez daha sorayım: ihtiyacın olan bir şey var mı?",RandPhraseSimple("Başka insanların görevlerine odaklanmasını engelliyorsun. Seninle daha fazla konuşmayacağım.",""+GetSexPhrase("Oğlum","Kızım")+",   anlamsız ve boş konuşmalardan hoşlanmam. Seninle artık konuşmayacağım."),"block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sadece uğradım...","Tamamen iş dolu..."),"Ah, hayır, Baba......","Hayır, padre, sadece konuşmak istemiştim...",RandPhraseSimple("Hmm...","Peki, nasıl istersen Baba..."),npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "Silaha sarılın! Casus var! Yakalayın onu!";
					link.l1 = "Caramba!";
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = LinkRandPhrase("Burası korunan bir hücre, ve kesinlikle yasaktır.","İçeri girmeyi aklından bile geçirme, cezası ölümdür.","Bu hücreye bir adım atarsan işin biter.");
					link.l1 = RandPhraseSimple("Anladım, asker.","Anladım...");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //заключенные
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("Ho-ho, şu 'azizlerin' doğrudan cehenneme gidişini izlemek komik değil mi?!","Aman Tanrım, gerçekten birileri onlara meydan okumaya cesaret etti mi?!","Beni neredeyse öldüresiye işkence ettiler, yakında öleceğim ama hayatımda son kez beni mutlu ettin...");
					link.l1 = RandPhraseSimple("Heh!","Rica ederim...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Bu ikiyüzlüler tamamen insanlıktan çıkmış. Bize yaptıkları her şeyin hesabını cehennemde verecekler...","Her gün bana işkence edip eziyet ettiler! Ama Rabbimizin gözünde suçlu değilim!","Koğuş arkadaşım dün öldü... Onu iki gündür işkence tezgahında tutuyorlardı... Ve kim bilir, ben daha ne kadar dayanacağım ...");
					link.l1 = RandPhraseSimple("Hmm... Bilemiyorum...","Anladım...");
					link.l1.go = "exit";
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
	}
}
