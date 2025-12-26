//Jason общий диалог индейцев на улицах
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
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","Beyaz kadın")+" konuşmak mı istiyor?","Yine sen, "+GetSexPhrase("solgun surat","beyaz kadın")+".",""+GetSexPhrase("Solgun yüzlü konuşmayı çok seviyor. Bir kadın gibi.","Beyaz kadın konuşmayı seviyor.")+"","Büyük Ruh soluk tenliyi getirdi"+GetSexPhrase("kardeşim","kız kardeş")+" bana.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Evet.","Evet, yine ben.","Çok şiirsel.","Seni görmekten ben de memnun oldum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Merhaba, beyaz kardeş. Kızılla konuşmak mı istiyorsun?";
				link.l1 = "Ormanın oğlu, selamlar. Seni gördüğüme sevindim, ama gitmem gerek.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ruhları kızdırma, soluk yüz! Uzun bıçağını yerine koy!","Canını hiçe sayma, solgun surat! Uzun bıçağını yerine koy!");
			link.l1 = LinkRandPhrase("Pekala.","Dediğiniz gibi.","Dediğiniz gibi.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
