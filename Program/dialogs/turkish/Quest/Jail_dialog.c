void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Jail_officer_take":
		//--> Сомнительное предложение
		if (CheckAttribute(pchar, "GenQuest.Contraoffer.Jail"))
		{
			dialog.text = "Kaçak mal transferi ve satışı girişiminden dolayı gözaltına alındınız. Yetkililere yaptığınız yardım ve konumunuz göz önünde bulundurularak, hapiste sadece "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+". Üstelik, kaçakçılıkla kazandığın tüm o para da -"+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+"   alınacak ve kasabanın hazinesine konulacak. İyi eğlenceler, kaptan!";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Jail");
			NextDiag.currentnode = "Jail_officer_free";
			break;
		}
		//<-- Сомнительное предложение
			dialog.text = "Bir suç işlediğiniz için tutuklandınız ve   hapiste tutulacaksınız "+FindRussianDaysString(sti(pchar.questTemp.JailTemp2))+". Ayrıca, bunun için ceza ödeyeceksiniz "+FindRussianMoneyString(sti(pchar.questTemp.JailTemp1))+" . Keyifli vakitler geçirin, kaptan!";
			link.l1 = "";
			link.l1.go = "Jail_officer_take_1";
			NextDiag.currentnode = "Jail_officer_free";
		break;
		
		case "Jail_officer_take_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10);
			DialogExit();
			DoQuestFunctionDelay("InPrison", 10.0);
		break;
		
		case "Jail_officer_free":
			dialog.text = "Eh, hapisliğin sona erdi. Umarım bundan bir şeyler öğrenmişsindir. Artık özgürsün. Eşyalarını subayın yanındaki sandıktan al. Ve sakın bir daha elime düşme!";
			link.l1 = "";
			link.l1.go = "Jail_officer_free_1";
		break;
		
		case "Jail_officer_free_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5);
			DialogExit();
			DoQuestFunctionDelay("GoFromPrison", 5.0);
		break;
	}
} 
