
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
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
			
			dialog.text = "대화 파일을 여는 데 오류가 발생했습니다.";
			if(CheckAttribute(CharacterRef, "Dialog.Filename"))
			{
				dialog.text = "대화 파일을 열 수 없습니다 "+CharacterRef.Dialog.Filename+" 이 캐릭터에게 할당됨.";
			}
			link.l1 = "알겠어";
			link.l1.go = "Exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
