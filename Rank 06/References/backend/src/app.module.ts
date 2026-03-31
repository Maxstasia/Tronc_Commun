import { Module } from '@nestjs/common';
import { UnoModule } from './modules/uno/uno.module';

@Module({
  imports: [UnoModule],
})
export class AppModule {}
